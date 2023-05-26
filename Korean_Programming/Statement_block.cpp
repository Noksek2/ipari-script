#include "Parser.h"
void Parser::state_skip() {
	if (!loopblock)throw ErrorMsg(ce_badbreak, L"");
	int n = 0;
	Next();
	vm_opcode.push_back(op_jmp);
	if (t.type == _Colon) {
		Next();
		if (t.type != lit_int) { throw ErrorMsg(ce_badjump, L""); }
		n = loopblock - stoi(t.str);
		Next();
	}
	else n = loopblock - 1;
	if (n < 0)throw ErrorMsg(ce_badjump, L"");
	vm_opcode.push_back(block_pc[n]);
}
void Parser::state_break() {
	int n = 0;
	Next();
	vm_opcode.push_back(op_jmp);
	if (t.type == _Colon) {
		Next();
		if (t.type != lit_int) { throw ErrorMsg(ce_badjump,L""); }
		n = loopblock - stoi(t.str);
		Next();
	}
	else n = loopblock - 1;
	if (n < 0)throw ErrorMsg(ce_badjump,L"");
	break_stack[n].push_back(vm_opcode.size());
	vm_opcode.push_back(0);
}
void Parser::state_if() {
	int p = 0;
	vector<int>if_pc;
	Next();
	express();
	vm_opcode.push_back(op_ujmp);
	p = vm_opcode.size();
	vm_opcode.push_back(0);
	nowblock++;
	while (t.type != _elif && t.type != _else && t.type != _end && t.type != _eof) {
		state();
	}
	nowblock--;
	if (t.type != _end) {
		vm_opcode.push_back(op_jmp);
		if_pc.push_back(vm_opcode.size());
		vm_opcode.push_back(0);
	}
	vm_opcode[p] = vm_opcode.size();
	while (t.type == _elif) {
		Next();
		express();
		vm_opcode.push_back(op_ujmp);
		p = vm_opcode.size();
		vm_opcode.push_back(0);
		nowblock++;
		while (t.type != _elif && t.type != _else && t.type != _end && t.type != _eof) {
			state();
		}
		nowblock--;
		if (t.type != _end) {
			vm_opcode.push_back(op_jmp);
			if_pc.push_back(vm_opcode.size());
			vm_opcode.push_back(0);
		}
		vm_opcode[p] = vm_opcode.size();
	}
	if (t.type == _else) {
		Next();
		nowblock++;
		while (t.type != _end && t.type != _eof) {
			state();
		}
		nowblock--;
	}
	target_block = lex.back().tab;
	Next();
	for (auto i : if_pc) {
		vm_opcode[i] = vm_opcode.size();
	}
	if (target_block != -1) {
		if (target_block < nowblock)return;
		else target_block = -1;
	}
}
void Parser::state_for() {
	int mem=0;
	bool up=0;
	uchar type;
	shared_ptr<i_ident_node>n;
	vector<int>opvec;
	Next();
	if (nownode->able(t.str)) {
		n = nownode->find(t.str);
	}
	else {
		switch (nownode->Type()) {
		case i_ident_node::id_func:
		case i_ident_node::id_class:
		case i_ident_node::id_method:
			nownode->add(t.str, type = i_ident_node::id_lvar);
			break;
		case i_ident_node::id_global:
			nownode->add(t.str, type = i_ident_node::id_var);
			break;
		case i_ident_node::id_pack:
			nownode->add(t.str, type = i_ident_node::id_var);
			lex.back().node_main->frame++;
			break;
		}
	}
	n = nownode->find(t.str);
	switch (n->Type()) {
	case i_ident_node::id_lvar:
		type = op_lstore;
		mem = ((i_ident_lvar*)n.get())->mem;
		break;
	case i_ident_node::id_var:
		type = op_gstore;
		mem = ((i_ident_var*)n.get())->mem;
		break;
	case i_ident_node::id_member:
		type = op_mstore;
		mem = string_map[t.str];
		break;
	default:throw ErrorMsg(ce_badtype, t.str);
	}
	Next();
	if (t.type != _Equal) { throw ErrorMsg(ce_noequal, t.str); }
	Next();
	express();
	int st = vm_opcode.size() + 2;
	switch (type) {
	case op_gstore:
		vm_opcode.push_back(op_gstore);
		vm_opcode.push_back(mem);
		if (t.type == _Range || t.type == _Range2) {
			vm_opcode.push_back(op_gload);
			vm_opcode.push_back(mem);
		}
		break;
	case op_lstore:
		vm_opcode.push_back(op_lstore);
		vm_opcode.push_back(mem);
		if (t.type == _Range || t.type == _Range2) {
			vm_opcode.push_back(op_lload);
			vm_opcode.push_back(mem);
		}
		break;
	case op_mstore:
		vm_opcode.push_back(op_mstore);
		vm_opcode.push_back(mem);
		if (t.type == _Range || t.type == _Range2) {
			vm_opcode.push_back(op_mload);
			vm_opcode.push_back(mem);
		}
		break;
	}
	if (t.type == _Range) {
		Next();
		express();
		vm_opcode.push_back(op_calc);
		vm_opcode.push_back(opc_lesseq);
		up = 1;
	}
	else if (t.type == _Range2) {
		Next();
		express();
		vm_opcode.push_back(op_calc);
		vm_opcode.push_back(opc_moreeq);
		up = 0;
	}
	else vm_opcode.push_back(op_pusht);
	vm_opcode.push_back(op_ujmp);
	int pc = vm_opcode.size();
	vm_opcode.push_back(0);
	int sc = vm_opcode.size();
	if (t.type == _Colon) {
		Next();
		express();
		opvec.assign(vm_opcode.begin() + sc, vm_opcode.end());
		vm_opcode.resize(sc);
	}
	else {
		opvec.push_back(op_push);
		opvec.push_back(up ? 1 : -1);
	}
	loopblock++; nowblock++;
	break_stack.emplace_back();
	block_pc.push_back(st);
	block();
	block_pc.pop_back();
	loopblock--; nowblock--;
	vm_opcode.insert(vm_opcode.end(),opvec.begin(), opvec.end());
	switch (type) {
	case op_gstore:vm_opcode.push_back(op_gop); break;
	case op_lstore:vm_opcode.push_back(op_lop); break;
	case op_mstore:vm_opcode.push_back(op_mop); break;
	}
	vm_opcode.push_back(opc_plus);
	vm_opcode.push_back(mem);
	vm_opcode.push_back(op_jmp);
	vm_opcode.push_back(st);
	for (auto i : break_stack.back()) {
		vm_opcode[i] = vm_opcode.size();
	}
	vm_opcode[pc] = vm_opcode.size();
	break_stack.pop_back();
	if (target_block != -1) {
		if (target_block < nowblock)return;
		else target_block = -1;
	}
}
void Parser::state_loop() {
	int st = vm_opcode.size();
	Next();
	loopblock++;
	nowblock++;
	block_pc.push_back(st);
	break_stack.emplace_back();
	block();
	vm_opcode.push_back(op_jmp);
	vm_opcode.push_back(st);
	for (auto i : break_stack.back()) {
		vm_opcode[i] = vm_opcode.size();
	}
	break_stack.pop_back();
	block_pc.pop_back();
	loopblock--; nowblock--;
	if (target_block != -1) {
		if (target_block < nowblock)return;
		else target_block = -1;
	}
}
void Parser::state_while() {
	int pc;
	Next();
	block_pc.push_back(vm_opcode.size());
	express();
	vm_opcode.push_back(op_ujmp);
	pc = vm_opcode.size();
	vm_opcode.push_back(0);
	nowblock++;
	loopblock++;
	break_stack.emplace_back();
	block();
	nowblock--;
	loopblock--;
	vm_opcode.push_back(op_jmp);
	vm_opcode.push_back(block_pc.back());
	vm_opcode[pc] = vm_opcode.size();
	for (auto i : break_stack.back()) {
		vm_opcode[i] = vm_opcode.size();
	}
	break_stack.pop_back();
	block_pc.pop_back();
	if (target_block != -1) {
		if (target_block < nowblock)return;
		else target_block = -1;
	}
}

void Parser::block() {
	while (t.type != _end) {
		if (t.type == _eof) { target_block = 0; return; }
		state();
		if (target_block != -1)return;
	}
	target_block = lex.back().tab;
	Next();
}
