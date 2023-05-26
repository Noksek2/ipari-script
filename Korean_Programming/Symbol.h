#pragma once
#include "Def.h"
#include "opcode.h"
class i_ident_node {
public:
	enum {
		id_var = 0,
		id_lvar,
		id_enum,
		id_func,
		id_class,
		id_member,
		id_method,
		id_pack,
		id_global,
	};
	i_ident_node(){}
	virtual uchar Type() {return id_var;}
	virtual void add(const wstring& s, uchar type) {}
	virtual shared_ptr<i_ident_node> find(const wstring& s) { return nullptr; }
	virtual bool able(const wstring& s) { return false; }
};
class i_ident_var :public i_ident_node {
public:
	int mem;
	i_ident_var(int _mem) { mem = _mem; }
	virtual uchar Type() {
		return id_var;
	}
};
class i_ident_lvar :public i_ident_node {
public:
	int mem;
	i_ident_lvar(int _mem) { mem = _mem; }
	virtual uchar Type() {
		return id_lvar;
	}
};
class i_ident_member:public i_ident_node {
public:
	i_ident_member() {}
	virtual uchar Type() {
		return id_member;
	}
};
class i_ident_global :public i_ident_node {
public:
	int frame;
	map<wstring, shared_ptr<i_ident_node>>node;
	i_ident_global() { frame = 0; }
	virtual uchar Type() {
		return id_global;
	}
	virtual void add(const wstring& s,uchar type);
	virtual shared_ptr<i_ident_node> find(const wstring& s) {
		return node[s];
	}
	virtual bool able(const wstring& s) {
		return node.find(s) != node.end();
	}
};
class i_ident_func :public i_ident_node {
public:
	int mem; int para; int frame;
	map<wstring, shared_ptr<i_ident_node>>node;
	i_ident_func() { mem = 0; para = 0; frame = 0; }
	i_ident_func(int _mem) { mem = _mem; para = 0; frame = 0; }
	virtual uchar Type() {
		return id_func;
	}
	virtual void add(const wstring& s, uchar type);
	virtual shared_ptr<i_ident_node> find(const wstring& s) {
		return node[s];
	}
	virtual bool able(const wstring& s) {
		return node.find(s) != node.end();
	}
};
class i_ident_method :public i_ident_node {
public:
	int frame; int para;
	map<wstring, shared_ptr<i_ident_node>>node;
	i_ident_method() { para = 0; frame = 0; }
	virtual uchar Type() {
		return id_method;
	}
	virtual void add(const wstring& s, uchar type);
	virtual shared_ptr<i_ident_node> find(const wstring& s) {
		return node[s];
	}
	virtual bool able(const wstring& s) {
		return node.find(s) != node.end();
	}
};
class i_ident_enum :public i_ident_node {
public:
	map<wstring, int>name;
	i_ident_enum() {}
	virtual uchar Type() {
		return id_enum;
	}
	void addenum(const wstring& s, int m);
	/*virtual bool able(const wstring& s) {
		return name.find(s) != name.end();
	}*/
};
class i_ident_pack :public i_ident_node {
public:
	map<wstring, shared_ptr<i_ident_node>>node;
	i_ident_pack() {
	}
	virtual uchar Type() {
		return id_pack;
	}
	virtual void add(const wstring& s, uchar type);
	virtual void addpack(const wstring& s, uchar type,int m);
	virtual shared_ptr<i_ident_node> find(const wstring& s) {
		return node[s];
	}
	virtual bool able(const wstring& s) {
		return node.find(s) != node.end();
	}
};
class i_ident_class :public i_ident_node {
public:
	int mem; int para;
	map<wstring, shared_ptr<i_ident_node>>node;
	i_ident_class(int _mem) { mem = _mem; para = 0; }
	virtual uchar Type() {
		return id_class;
	}
	void add(const wstring& s,uchar type);
	virtual shared_ptr<i_ident_node> find(const wstring& s) {
		return node[s];
	}
	virtual bool able(const wstring& s) {
		return node.find(s) != node.end();
	}
};