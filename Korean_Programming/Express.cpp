#include "Parser.h"
shared_ptr<i_ident_node> Parser::findident(const wstring& s) {
	auto node = lex.back().node_vec;
	for (int i = node.size() - 1; i >= 0;i--) {
		if (node[i]->able(s)) {
			return node[i]->find(s);
		}
	}
	return 0;
}
void Parser::express() {
	exp();
	polish_clear();
}
void Parser::exp() {
	while (true) {
		factor();
		if (!oprank(to_opcode[t.type])) { return; }
		polish_push(to_opcode[t.type]);
		Next();
	}
}
void Parser::factor_access() {
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
				arg++;
				if (t.type != _Squareend)throw ErrorMsg(ce_nosquare, L"");
				Next();
			}
			vm_opcode.push_back(op_at);
			vm_opcode.push_back(arg);
		}
		else break;
		arg = 0;
	}
}
void Parser::factor() {
	fac();
	factor_access();
	while (t.type == _Dot) {
		Next();
		if(t.type!=lit_ident)throw ErrorMsg(ce_baddot, L"");
		vm_opcode.push_back(op_atm);
		if (string_map.find(t.str) == string_map.end())
			string_map.emplace(t.str, string_map.size());
		vm_opcode.push_back(string_map[t.str]);
		Next();
		factor_access();
	}
	//[][] (,,)
	//.ident [] (,,)
}
uchar Parser::ident_left() {
	shared_ptr<i_ident_node>n;
	wstring s;
	int arg = 0;
	uchar type = 0;
	switch (t.type) {
	case _Doll://global
		Next();
		n = lex.back().node_main;
		if (n->able(t.str)) {
			n=n->find(t.str);
		}
		else{
			n->add(t.str, i_ident_node::id_var);
			n=n->find(t.str);
		}
		Next();
		break;
	case _Atsign://member
		break;
	case lit_ident://all
		if (!nownode->able(t.str)) {
			s = t.str;
			Next();
			if (t.type != _Dot) {
				switch (nownode->Type()) {
				case i_ident_node::id_func:case i_ident_node::id_method:case i_ident_node::id_class:
					nownode->add(s, i_ident_node::id_lvar);
					break;
				case i_ident_node::id_global:
					nownode->add(s, i_ident_node::id_var);
					break;
				}
				n = nownode->find(s);
			}
			else {
				n = findident(s);
				if (!n)throw ErrorMsg(ce_noident, s);
			}
		}
		else { n = nownode->find(t.str); Next(); }
		break;
	}
	while (t.type == _Dot) {
		Next();
		if (t.type != lit_ident)throw ErrorMsg(ce_badexp, L"");
		if (n->able(t.str)) { n = n->find(t.str); }
		else { goto getmember; }
	}
	switch (n->Type()) {
	case i_ident_node::id_var:
		type = op_gload;
		vm_opcode.push_back(op_gload);
		vm_opcode.push_back(((i_ident_var*)n.get())->mem);
		break;
	case i_ident_node::id_func:case i_ident_node::id_class:
		type = op_gload;
		vm_opcode.push_back(op_gload);
		vm_opcode.push_back(((i_ident_func*)n.get())->mem);
		break;
	case i_ident_node::id_lvar:
		type = op_lload;
		vm_opcode.push_back(op_lload);
		vm_opcode.push_back(((i_ident_lvar*)n.get())->mem);
		break;
	default:throw ErrorMsg(ce_badtype, t.str);
	}
	return type;
getmember:
	while (true) {
		if (t.type != lit_ident)throw ErrorMsg(ce_baddot, L"");
		vm_opcode.push_back(op_atm);
		if (string_map.find(t.str) == string_map.end())
			string_map.emplace(t.str, string_map.size());
		vm_opcode.push_back(string_map[t.str]);
		Next();
		type = op_atm;
		if (t.type != _Dot)break;
	}
	return type;
}
void Parser::fac_ident(uchar type) {
	shared_ptr<i_ident_node> s;
	wstring str;
	switch (type) {
	case 0:
		s = findident(t.str);
		if (!s) {
			throw ErrorMsg(ce_noident, t.str);
		}
		break;
	case 1:
		Next();
		if (t.type != lit_ident)throw ErrorMsg(ce_baddollat, t.str);
		if (nownode->Type() != i_ident_node::id_method && nownode->Type() != i_ident_node::id_class) {
			//throw ErrorMsg(ce_nomember, t.str);
		}
		break;
	case 2:
		Next();
		if (t.type != lit_ident)throw ErrorMsg(ce_baddollat, t.str);
		if (!lex.back().node_main->able(t.str))throw ErrorMsg(ce_noident, t.str);
		s = lex.back().node_main->find(t.str);
		break;
	}
	Next();
	while (t.type == _Dot) {
		Next();
		if (t.type != lit_ident)throw ErrorMsg(ce_badmember, t.str);
		str = t.str.c_str();
		if (s->able(t.str)) {
			s = s->find(t.str);
		}
		else {//.멤버변수
			switch (nownode->Type()) {
			case i_ident_node::id_global:case i_ident_node::id_pack:
				switch (s->Type()) {
				case i_ident_node::id_var:
					vm_opcode.push_back(op_gload);
					vm_opcode.push_back(((i_ident_var*)s.get())->mem);
					break;
				case i_ident_node::id_enum:
					if (!s->able(t.str)) {
						//throw enum 접근 불가;
					}
					vm_opcode.push_back(op_push);
					vm_opcode.push_back(((i_ident_enum*)s.get())->name[t.str]);
					return;
				default:
					//접근 불가;
					break;
				}
				break;
			case i_ident_node::id_class:
				switch (s->Type()) {
				case i_ident_node::id_var:
				case i_ident_node::id_enum:
					if (!s->able(t.str)) {
						//throw enum 접근 불가;
					}
					vm_opcode.push_back(((i_ident_enum*)s.get())->name[t.str]);
					return;
				case i_ident_node::id_lvar:
					if(nownode->able(str)){}
					else {} //오류 처리
					break;
				case i_ident_node::id_member:
					break;
				default:
					//접근 불가;
					break;
				}
				break;
			case i_ident_node::id_func:
			case i_ident_node::id_method:
				break;
			}
			goto getmember;
		}
		Next();
	}
	switch (s->Type()) {
	case i_ident_node::id_var:case i_ident_node::id_func:
		vm_opcode.push_back(op_gload);
		vm_opcode.push_back(((i_ident_var*)s.get())->mem);
		break;
	case i_ident_node::id_lvar:
		vm_opcode.push_back(op_lload);
		vm_opcode.push_back(((i_ident_lvar*)s.get())->mem);
		break;
	}
	return;
getmember:
	while(true){
		if (t.type != lit_ident)throw ErrorMsg(ce_baddot, L"");
		vm_opcode.push_back(op_atm);
		if(string_map.find(t.str)==string_map.end())
			string_map.emplace(t.str, string_map.size());
		vm_opcode.push_back(string_map[t.str]);
		Next();
		if (t.type != _Dot)break;
		Next();
	}
}
void Parser::fac() {
	int arg=0;
re:
	switch (t.type) {
	case _Plus:Next(); goto re;
	case _Minus:polish_push(opc_min); Next(); goto re;
	case _Not:polish_push(opc_not); Next(); goto re;
	case _Brack:
		Next();
		if (t.type == _Brackend)throw ErrorMsg(ce_badexp, L"");
		polish_push(100);
		exp();
		if (t.type != _Brackend)throw ErrorMsg(ce_nobrack, L"");
		polish_brackpop();
		break;
	case lit_int:
		vm_opcode.push_back(op_push);
		vm_opcode.push_back(stoi(t.str));
		break;
	case lit_num:
		vm_opcode.push_back(op_pushl);
		vm_opcode.push_back(vm_lit.size());
		vm_lit.emplace_back(make_shared<i_num>(stod(t.str)));
		break;
	case lit_str:
		vm_opcode.push_back(op_pushl);
		vm_opcode.push_back(vm_lit.size());
		vm_lit.emplace_back(make_shared<i_str>(t.str));
		break;
	case _true:vm_opcode.push_back(op_pusht); break;
	case _false:vm_opcode.push_back(op_pushf); break;
	case _null:vm_opcode.push_back(op_pushn); break;
	case lit_vstr:
		arg = 1;
		for (bool b = 0;; b = true) {
			if (t.type != lit_vstr && t.type != lit_strend) {
				lex.back().strflag = 0; throw ErrorMsg(ce_badstr, L"");
			}
			if (t.type != lit_strend) {
				vm_opcode.push_back(op_pushl);
				vm_opcode.push_back(vm_lit.size());
				vm_lit.emplace_back(make_shared<i_str>(t.str));
			}
			else {
				if (t.str != L"") { arg++;
				vm_opcode.push_back(op_pushl);
				vm_opcode.push_back(vm_lit.size());
				vm_lit.emplace_back(make_shared<i_str>(t.str));
				}
				break;
			}
			if (b) {
				arg++;
			}
			lex.back().strflag = 2;
			Next();
			polish_push(100);
			exp();
			if (t.type != _Squareend) {
				throw ErrorMsg(ce_badstr, L"");
			}
			polish_brackpop();
			arg++;
			lex.back().strflag = 1;
			Next();
		}
		if (arg > 1) {
			vm_opcode.push_back(op_makes);
			vm_opcode.push_back(arg);
		}
		break;
	case _Square:
		do {
			Next();
			if (t.type == _Squareend) {
				if (arg == 0)break;
				else throw ErrorMsg(ce_badexp, L"");
			}
			polish_push(100);
			exp();
			polish_brackpop();
			arg++;
		} while (t.type == _Comma);
		if (t.type != _Squareend)throw ErrorMsg(ce_nosquare, L"");
		vm_opcode.push_back(op_makea);
		vm_opcode.push_back(arg);
		break;
	case lit_ident:
		fac_ident(0);
		return;
	case _Atsign://멤버 변수
		fac_ident(1);
		return;
	case _Doll://글로벌 변수
		fac_ident(2);
		return;
	default:
		throw ErrorMsg(ce_badexp, L"");
	}
	Next();
}