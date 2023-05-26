#pragma once
#include "Symbol.h"
enum i_token_type{
	_None,
	lit_int,
	lit_num,
	lit_str,
	lit_vstr,
	lit_strend,
	lit_ident,

	_put,//출력
	_print,//출력해
	_var,//변수
	_func,//함수
	_if,//만약
	_elif,//아니고
	_else,//아니면
	_switch,//판단

	_true,//참
	_false,//거짓
	_null,//공백

	_while,//되풀이
	_for,//반복
	_loop,//무한반복

	_break,//탈출
	_skip,//건너뛰기
	_return,//반환
	_class,//객체
	_enum,//상수
	_pack,//기능
	_end,//끝
	
	_import,//불러오기
	_using,//사용하기

	_Pow,// ^
	_Multi,//*
	_Divi,// /
	_Mod,// %
	_Plus,// +
	_Minus,// -
	_Less,//<
	_Lesseq,//<=
	_More,//>
	_Moreeq,//>=
	_Noteq,//!=
	_And,//그리고
	_Or,//또는
	_Not,//!

	_Poweq,// ^=
	_Multieq,//*=
	_Divieq,// /=
	_Modeq,// %=
	_Pluseq,// +=
	_Minuseq,// -=
	
	_Brack,//( 기호
	_Brackend,//) 기호
	_Square,//[ 기호
	_Squareend,//] 기호
	_Block,//{ 기호
	_Blockend,//} 기호
	_Range,//~ 기호
	_Range2,//.. 기호
	_Comma,//, 기호
	_Dot,//. 기호
	_Sharp,//# 주석
	_Comment,// ## 주석 ##
	_Quot,//' 기호
	_Quots,//" 기호
	_Equal,//= 기호
	_Semi,//; 기호
	_Colon,//: 기호
	_Atsign,//@ 기호
	_Doll,//$ 기호
	_Case,//->
	_eof//파일 끝
};
extern map<wstring, uchar>i_lex_keyword;
extern uchar* i_lex_char;
struct i_token {
	wstring str;
	uchar type;
	i_token() { str = L"", type = _None; }
	i_token(wstring s, uchar t) :str(s), type(t) {}
};
class i_lexer {
public:
	shared_ptr<i_ident_global>node_main;
	vector<shared_ptr<i_ident_node>>node_vec;
	wstring source;
	wstring file;
	int line;
	int x;
	short tab;
	wchar c;
	int linef;
	uchar strflag;
	bool errorflag;
	i_lexer() {
		node_main = make_shared<i_ident_global>();
		node_vec.emplace_back(node_main);
		strflag = 0;
		linef = 0;
		errorflag = 0;
		source = L"";
		x = 0;
		line = 0;
		c = L' ';
		file = L"";
		tab = 0;
	}
	void Init(const wchar* s, const wchar* file) {
		source = s;
		x = 0;
		line = 0;
		c = L' ';
		this->file = file;
	}
	wchar get() {
		if (source.size() == x)return '\0';
		else if (source[x] == '\n') { linef++; tab = 0; }
		else if (source[x] == '\t') { tab++; }
		return source[x++];
	}
	wchar look() {
		if (source.size() == x)return '\0';
		return source[x];
	}
	wchar ProcessEscape() {
		c = get();
		switch (c) {
		case 'a':return '\a';
		case 'b':return '\b';
		case 'n':return '\n';
		case 'r':return '\r';
		case 't':return '\t';
		case '\\':case '\'':
		case '[':case ']':
		case '(':case ')':
		case'{':case '}':
		case '\"':case '?':return c;
		}
		return '\\';
	}
	int FindWord(const wstring & s, bool sign = 0) {
		if (i_lex_keyword.find(s) != i_lex_keyword.end()) {
			return i_lex_keyword[s];
		}
		if (!sign)return lit_ident;
		return _None;
	}
	i_token Next() {
	re:
		int buf;
		wstring s = L"";
		if(errorflag){
			while (c != '\n'&&c!='\0') {
				c = get();
			}
			errorflag = 0;
		}
		if (strflag==1)goto _go;
		while (iswspace(c)) {
			c = get();
		}
		line += linef;
		linef = 0;
		if (c == '\0')return i_token(L"", _eof);
		switch (i_lex_char[c]) {
		case lit_int:
			for (; i_lex_char[c] == lit_int; c = get()) {
				s += c;
			}
			if (c != '.') {
				return i_token(s, lit_int);
			}
			else if (i_lex_char[look()] != lit_int) {
				return i_token(s, lit_int);
			}
			s += c;
			for (c = get(); i_lex_char[c]==lit_int; c = get()) {
				s += c;
			}
			return i_token(s, lit_num);
		case _Quot:
			for (c = get(); c != '\'' && c != '\0'; c = get()) {
				if (c == '\\') { s += ProcessEscape(); }
				else s += c;
			}
			c = get();
			return i_token(s, lit_str);
		case _Quots:
			if (strflag == 2) { c = get(); strflag = 0; return i_token(s, lit_strend); }
			c = get();
			_go:
			for (; c != '\0' && c != '['; c = get()) {
				if (c == '\\') { s += ProcessEscape(); }
				else if (c == '"') { c = get(); 
				buf = strflag; strflag = 0;
					return i_token(s, buf?lit_strend:lit_str);
				}
				else s += c;
			}
			c = get();
			return i_token(s, lit_vstr);
		case lit_str:
			for (; i_lex_char[c]==lit_str|| i_lex_char[c] == lit_int; c = get()) {
				s += c;
			}
			return i_token(s, FindWord(s));
		case _Sharp:
			c = get();
			if (c == '#') {
				c = get();
				for (;c!='\0';) {
					if (c == '#') {
						c = get();
						if (c == '#')break;
					}
					else c = get();
				}
				c = get();
				goto re;
			}
			else { errorflag = true; goto re; }
			break;
		default:
			s += c;
			c = get();
			s += c;
			buf = FindWord(s, 1);
			if (buf != _None) {
				c = get();
				return i_token(s, buf);
			}
			s.pop_back();
			return i_token(s, FindWord(s, 1));
		}
		return i_token(L"", _None);
	}
};