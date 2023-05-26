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

	_put,//���
	_print,//�����
	_var,//����
	_func,//�Լ�
	_if,//����
	_elif,//�ƴϰ�
	_else,//�ƴϸ�
	_switch,//�Ǵ�

	_true,//��
	_false,//����
	_null,//����

	_while,//��Ǯ��
	_for,//�ݺ�
	_loop,//���ѹݺ�

	_break,//Ż��
	_skip,//�ǳʶٱ�
	_return,//��ȯ
	_class,//��ü
	_enum,//���
	_pack,//���
	_end,//��
	
	_import,//�ҷ�����
	_using,//����ϱ�

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
	_And,//�׸���
	_Or,//�Ǵ�
	_Not,//!

	_Poweq,// ^=
	_Multieq,//*=
	_Divieq,// /=
	_Modeq,// %=
	_Pluseq,// +=
	_Minuseq,// -=
	
	_Brack,//( ��ȣ
	_Brackend,//) ��ȣ
	_Square,//[ ��ȣ
	_Squareend,//] ��ȣ
	_Block,//{ ��ȣ
	_Blockend,//} ��ȣ
	_Range,//~ ��ȣ
	_Range2,//.. ��ȣ
	_Comma,//, ��ȣ
	_Dot,//. ��ȣ
	_Sharp,//# �ּ�
	_Comment,// ## �ּ� ##
	_Quot,//' ��ȣ
	_Quots,//" ��ȣ
	_Equal,//= ��ȣ
	_Semi,//; ��ȣ
	_Colon,//: ��ȣ
	_Atsign,//@ ��ȣ
	_Doll,//$ ��ȣ
	_Case,//->
	_eof//���� ��
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