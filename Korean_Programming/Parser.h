#pragma once
#include "_Lexer.h"
#include "Error.h"
#include <unordered_map>
extern unordered_map<wstring, int>string_map;
class Parser{
	vector<i_lexer>lex;
	string polish_stack;
	uchar to_opcode[200];
	const wchar* opcode_str[200],*opcstr[20];
	i_token t;
	shared_ptr<i_ident_node> nownode; //현재 노드
	short nowblock;
	short target_block;
	short loopblock;
	vector<int>block_pc;
	vector<vector<int>>break_stack;
	bool retable;
public:
	int errorcnt;
	Parser() {
		retable = 0;
		loopblock = 0;
		target_block = -1;
		nowblock = 0;
		opcstr[opc_plus] = L"plus";
		opcstr[opc_minus] = L"minus";
		opcstr[opc_min] = L"min";
		opcstr[opc_pow] = L"pow";
		opcstr[opc_mul] = L"multi";
		opcstr[opc_div] = L"divi";
		opcstr[opc_compare] = L"compare"; opcstr[opc_noteq] = L"noteq";

		to_opcode[_Plus] = opc_plus;
		to_opcode[_Minus] = opc_minus;
		to_opcode[_Multi] = opc_mul;
		to_opcode[_Divi] = opc_div;
		to_opcode[_Mod] = opc_mod;
		to_opcode[_Pow] = opc_pow;
		to_opcode[_Less] = opc_less; to_opcode[ _Lesseq] = opc_lesseq;
		to_opcode[_More] = opc_more; to_opcode[_Moreeq] = opc_moreeq;
		to_opcode[_Equal] = opc_compare; to_opcode[_Noteq] = opc_noteq;
		to_opcode[_And] = opc_land; to_opcode[_Or] = opc_lor;
		errorcnt = 0;
	}
	inline void Next() {
		t = lex.back().Next();
	}
	void print_error(const wchar*, uchar,const wchar*, int);
	uchar oprank(uchar t) {
		switch (t) {
		case opc_min:case opc_not:return 1;
		case opc_pow:
			return 2;
		case opc_mul:case opc_div:case opc_mod:
			return 3;
		case opc_plus:case opc_minus:
			return 4; 
		case opc_less:case opc_more:
			return 5;
		case opc_lesseq:case opc_moreeq:
			return 6;
		case opc_compare:case opc_noteq:
			return 7;
		case opc_land:
			return 8;
		case opc_lor:
			return 9;
		case 100:
			return 120;
		}
		return 0;
	}
	void polish_push(uchar);
	void polish_pop(int,bool);
	void polish_brackpop();
	void polish_clear();

	shared_ptr<i_ident_node> findident(const wstring& s);
	void express();
	void exp();
	void factor();
	void factor_access();
	void fac();
	void fac_ident(uchar);
	void block();
	void state();
	void state_put(bool);
	void state_func();
	void state_loop();
	void state_while();
	void state_for();
	void state_switch();
	void state_if();
	void state_return();
	void state_express();
	void state_var();
	void state_enum();
	void state_skip();
	void state_break();
	void state_pack();
	uchar ident_left();
	void ident_access(uchar&);
	

	void puterror(uchar c, wstring msg) {
		print_error(lex.back().file.c_str(), c, msg.c_str(), lex.back().line);
	}
	void getfile(const wchar* ,wstring&);
	void compile(const wchar* f);
	void parsing();
	~Parser() {}
};