#include "Symbol.h"
void i_ident_global::add(const wstring& s, uchar type) {
	switch (type) {
	case id_func:
		node.emplace(s, make_shared<i_ident_func>(frame++));
		break;
	case id_class:
		node.emplace(s, make_shared<i_ident_class>(frame++));
		break;
	case id_pack:
		node.emplace(s, make_shared<i_ident_pack>());
		break;
	case id_var:
		node.emplace(s, make_shared<i_ident_var>(frame++));
		break;
	case id_enum:
		node.emplace(s, make_shared<i_ident_enum>());
		break;
	}
}
void i_ident_pack::addpack(const wstring& s, uchar type,int m) {
	switch (type) {
	case id_func:
		node.emplace(s, make_shared<i_ident_func>(m));
		break;
	case id_class:
		node.emplace(s, make_shared<i_ident_class>(m));
		break;
	case id_var:
		node.emplace(s, make_shared<i_ident_var>(m));
		break;
	}
}
void i_ident_pack::add(const wstring& s, uchar type) {
	switch (type) {
	case id_pack:
		node.emplace(s, make_shared<i_ident_pack>());
		break;
	case id_enum:
		node.emplace(s, make_shared<i_ident_enum>());
		break;
	}
}
void i_ident_func::add(const wstring& s, uchar type) {
	switch (type) {
	case id_lvar:
		node.emplace(s, make_shared<i_ident_lvar>(frame++));
		break;
	case id_enum:
		node.emplace(s, make_shared<i_ident_enum>());
		break;
	}
}
void i_ident_method::add(const wstring& s, uchar type) {
	switch (type) {
	case id_lvar:
		node.emplace(s, make_shared<i_ident_lvar>(frame++));
		break;
	}
	/*
	*/
}
void i_ident_enum::addenum(const wstring& s, int m) {
	name.emplace(s, m);
}
/*void i_ident_pack::add(const wstring& s, int m, uchar type) {
	switch (type) {
	case id_func:
		node.emplace(s, make_shared<i_ident_func>(m, 0));
		break;
	case id_class:
		node.emplace(s, make_shared<i_ident_class>(m));
		break;
	case id_pack:
		node.emplace(s, make_shared<i_ident_pack>());
		break;
	case id_var:
		node.emplace(s, make_shared<i_ident_node>(m));
		break;
	case id_enum:
		node.emplace(s, make_shared<i_ident_enum>());
		break;
	}
}*/
void i_ident_class::add(const wstring& s, uchar type) {
	switch (type) {
	case id_method:
		node.emplace(s, make_shared<i_ident_method>());
		break;
	case id_member:
		node.emplace(s, make_shared<i_ident_member>());
		break;
	case id_lvar:
		node.emplace(s, make_shared<i_ident_lvar>(para));
		para++;
		break;
	}
}