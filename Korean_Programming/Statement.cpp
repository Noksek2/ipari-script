#include "Parser.h"
void Parser::state() {
	switch (t.type) {
	case _put:state_put(0); break;
	case _print:state_put(1); break;
	case _if: state_if(); break;
	case _switch:state_switch(); break;
	case _for:state_for(); break;
	case _loop:state_loop(); break;
	case _while:state_while(); break;
	case _enum:state_enum(); break;
	case _var:state_var(); break;
	case _func:state_func(); break;
	case _return:state_return(); break;
	case _skip:state_skip(); break;
	case _break:state_break(); break;
	case _pack:state_pack(); break;
	case lit_ident:case _Doll:case _Atsign: state_express(); break;
	default:throw ErrorMsg(ce_badexp, L""); break;
	}
}


void Parser::state_func() {
	int lit_no = vm_lit.size();
	vm_lit.emplace_back(make_shared<i_func>(vm_opcode.size()));
	vm_opcode.push_back(op_pushl);
	vm_opcode.push_back(lit_no);
	vm_opcode.push_back(op_gstore);
	vm_opcode.push_back(((i_ident_func*)nownode.get())->mem);
	Next();
	if (t.type != lit_ident)throw ErrorMsg(ce_badident, t.str);
	if (nownode->able(t.str))throw ErrorMsg(ce_overident, t.str);
	//등록
	switch (nownode->Type()) {
	case i_ident_node::id_class:
		break;
	case i_ident_node::id_pack:
		((i_ident_pack*)nownode.get())->addpack(t.str, i_ident_node::id_func,
			lex.back().node_main->frame++);
		break;
	case i_ident_node::id_global:
		nownode->add(t.str, i_ident_node::id_func);
		break;
	default:throw ErrorMsg(ce_badlocfunc, t.str);
	}
	nownode = nownode->find(t.str);
	lex.back().node_vec.emplace_back(nownode);
	Next();
	vm_opcode.push_back(op_jmp);
	int s = vm_opcode.size();
	vm_opcode.push_back(0);
	((i_func*)vm_lit[lit_no].get())->pc = vm_opcode.size();
	if (t.type != _Brack)throw ErrorMsg(ce_nobrack, L"");
	do {
		Next();
		if (t.type == _Brackend) {
			if (((i_ident_func*)nownode.get())->para == 0)break;
			else throw ErrorMsg(ce_badexp, L"");
		}
		if (t.type != lit_ident)throw ErrorMsg(ce_badident, t.str);
		if (nownode->able(t.str))throw ErrorMsg(ce_overident, t.str);
		nownode->add(t.str, i_ident_node::id_lvar);
		vm_opcode.push_back(op_lstore);
		vm_opcode.push_back(((i_ident_func*)nownode.get())->para++);
		Next();
	} while (t.type == _Comma);
	if(t.type!=_Brackend)throw ErrorMsg(ce_nobrack, L"");
	Next();
	if (t.type == _Equal) {
		Next();
		express();
		vm_opcode.push_back(op_ret);
		vm_opcode[s] = vm_opcode.size();
		((i_func*)vm_lit[lit_no].get())->frame = ((i_ident_func*)nownode.get())->frame;
		((i_func*)vm_lit[lit_no].get())->para = ((i_ident_func*)nownode.get())->para;
		lex.back().node_vec.pop_back();
		nownode = lex.back().node_vec.back();
		return;
	}
	nowblock++;
	vm_opcode.push_back(op_pop);
	block();
	nowblock--;
	vm_opcode.push_back(op_pushn);
	vm_opcode.push_back(op_ret);
	vm_opcode[s] = vm_opcode.size();
	lex.back().node_vec.pop_back();
	((i_func*)vm_lit[lit_no].get())->frame = ((i_ident_func*)nownode.get())->frame;
	((i_func*)vm_lit[lit_no].get())->para = ((i_ident_func*)nownode.get())->para;
	nownode = lex.back().node_vec.back();
	if (target_block != -1) {
		if (target_block < nowblock)return;
		else target_block = -1;
	}
}

void Parser::state_pack() {
	if (loopblock)throw ErrorMsg(ce_loopident, L"");
	Next();
	if (t.type != lit_ident) { throw ErrorMsg(ce_badident, t.str); }
	if (nownode->able(t.str))throw ErrorMsg(ce_overident, t.str);
	nownode->add(t.str, i_ident_node::id_pack);
	nownode = nownode->find(t.str);
	lex.back().node_vec.emplace_back(nownode);
	nowblock++;
	Next();
	block();
	lex.back().node_vec.pop_back();
	nownode = lex.back().node_vec.back();
	nowblock--;
	if (target_block != -1) {
		if (target_block < nowblock)return;
		else target_block = -1;
	}
}

void Parser::state_return() {
	switch (nownode->Type()) {
	case i_ident_node::id_func:
	case i_ident_node::id_method:
		break;
	default:
		break;
	}
	Next();
	express();
	vm_opcode.push_back(op_ret);
}
void Parser::state_enum() {
	Next();
	if (t.type != lit_ident) { throw ErrorMsg(ce_badident, t.str); }
	if (nownode->able(t.str))throw ErrorMsg(ce_overident, t.str);
	nownode->add(t.str, i_ident_node::id_enum);
	i_ident_enum* e = ((i_ident_enum*)(nownode->find(t.str)).get());
	wstring s;
	int n = 0;
	do {
		Next();
		if (t.type != lit_ident) { throw ErrorMsg(ce_badident, t.str); }
		s = t.str;
		Next();
		if (t.type == _Equal) {
			Next();
			//express_enum();
			n = stoi(t.str);
			e->addenum(s, n++);
			Next();
		}
		else e->addenum(s, n++);
	} while (t.type == _Comma);
}
void Parser::state_var() {
	wstring str;
	int n;
	/*클래스 -> 멤버 변수
	함수, 메소드 -> 지역 변수
	패키지, 글로벌 -> 글로벌 변수
	*/
	do {
		Next();
		str = t.str;
		if (t.type != lit_ident)throw ErrorMsg(ce_badident, t.str);
		if (nownode->able(t.str))throw ErrorMsg(ce_overident, t.str);
		Next();
		if (t.type == _Equal) {
			Next(); express();
		}
		else vm_opcode.push_back(op_pushn);
		switch (nownode->Type()) {
		case i_ident_node::id_global:
			nownode->add(str, i_ident_node::id_var);
			vm_opcode.push_back(op_gstore);
			vm_opcode.push_back(lex.back().node_main->frame - 1);
			break;
		case i_ident_node::id_pack:
			((i_ident_pack*)nownode.get())->addpack(str, i_ident_node::id_var, lex.back().node_main->frame);
			vm_opcode.push_back(op_gstore);
			vm_opcode.push_back(lex.back().node_main->frame);
			lex.back().node_main->frame++;
			break;
		case i_ident_node::id_class:
			nownode->add(str, i_ident_node::id_lvar);
			break;
		case i_ident_node::id_method:
			break;
		case i_ident_node::id_func:
			nownode->add(str, i_ident_node::id_lvar);
			vm_opcode.push_back(op_lstore);
			vm_opcode.push_back(((i_ident_func*)nownode.get())->frame - 1);
			break;
		}
	} while (t.type == _Comma);
}
void Parser::ident_access(uchar& type) {
	int arg = 0;
	while (true) {
		if (t.type == _Brack) {
			do {
				Next();
				if (t.type == _Brackend) {
					if (arg == 0)break;
					else throw ErrorMsg(ce_badexp, L"");
				}
				polish_push(100);
				exp();
				polish_brackpop();
				arg++;
			} while (t.type == _Comma);
			if (t.type != _Brackend)throw ErrorMsg(ce_nobrack, L"");
			type = op_call;
			vm_opcode.push_back(op_call);
			vm_opcode.push_back(arg);
			Next();
		}
		else if (t.type == _Square) {
			while (t.type == _Square) {
				Next();
				polish_push(100);
				exp();
				polish_brackpop();
				vm_opcode.push_back(op_at1);
				if (t.type != _Squareend)throw ErrorMsg(ce_nosquare, L"");
				Next();
			}
			type = op_at1;
		}
		else return;
		arg = 0;
	}
}
void Parser::state_express() {

	uchar type=ident_left();
	ident_access(type);
	//a.sdf()[].a
	while (t.type == _Dot) {
		Next();
		if (t.type != lit_ident)throw ErrorMsg(ce_baddot, L"");
		vm_opcode.push_back(op_atm);
		if (string_map.find(t.str) == string_map.end())
			string_map.emplace(t.str, string_map.size());
		vm_opcode.push_back(string_map[t.str]);
		type = op_atm;
		Next();
		ident_access(type);
	}
	uchar optype = t.type,tp=0;
	int m=0;
	switch (optype) {
	case _Equal:case _Pluseq:case _Minuseq:case _Poweq:case _Multieq:case _Divieq:
		switch (type) {
		case op_mload:case op_lload:case op_gload:
			if (type == op_mload)type = op_mstore;
			else if (type == op_lload)type = op_lstore;
			else type = op_gstore;
			m = vm_opcode.back(); vm_opcode.pop_back(); vm_opcode.pop_back();
			break;
		case op_call:type = op_set;  break;
		case op_at1:vm_opcode.pop_back(); type = op_set;  break;
		case op_atm:
			*(vm_opcode.end() - 1) = op_pushs;
			type = op_set;
			break;
		}
		Next();
		express();
		//gop
		break;
	default:
		if (type != op_call)throw ErrorMsg(ce_badexp, L"");
		vm_opcode.push_back(op_pop);
		return;
	}
	switch (optype) {
	case _Equal:
		vm_opcode.push_back(type);
		if (type != op_set)vm_opcode.push_back(m);
		break;
	default:
		if (optype == _Pluseq)tp = opc_plus;
		else if (optype == _Minuseq)tp = opc_minus;
		else if (optype == _Poweq)tp = opc_pow;
		else if (optype == _Multieq)tp = opc_mul;
		else if (optype == _Divieq)tp = opc_div;
		if (type == op_set) {
			vm_opcode.push_back(op_opset);
			vm_opcode.push_back(tp);
		}
		else {
			if (type == op_mstore)type = op_mop;
			else if (type == op_lstore)type = op_lop;
			else type = op_gop;
			vm_opcode.push_back(type);
			vm_opcode.push_back(tp);
			vm_opcode.push_back(m);
		}
		break;
	}
}
void Parser::state_put(bool line) {
	int argc = 0;
	do {
		Next();
		express();
		argc++;
	} while (t.type == _Comma);
	vm_opcode.push_back((line ? op_print : op_put));
	vm_opcode.push_back(argc);
}


void Parser::state_switch() {
}
