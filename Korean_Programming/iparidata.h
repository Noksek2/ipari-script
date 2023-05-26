#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
//#include <unordered_map>
#include <set>
#include <Windows.h>
#include <time.h>
using namespace std;
typedef unsigned char uchar;
typedef wchar_t wchar;
class i_data;
typedef shared_ptr<i_data>i_ptrdata;
class i_data {
public:
	enum :uchar {
		t_null,
		t_bool,
		t_int,
		t_num,
		t_str,
		t_array,
		t_dict,
		t_func,
		t_cfunc,
		t_object,
		t_member,
		t_error,
		t_range,
	};
	virtual wstring tostr() { return L""; }
	virtual uchar type() { return t_null; }
	virtual i_ptrdata Pow(const i_ptrdata&);
	virtual i_ptrdata Divi(const i_ptrdata&);
	virtual i_ptrdata Multi(const i_ptrdata&);
	virtual i_ptrdata Mod(const i_ptrdata&);
	virtual i_ptrdata Plus(const i_ptrdata&);
	virtual i_ptrdata Minus(const i_ptrdata&);
	virtual i_ptrdata Less(const i_ptrdata&);
	virtual i_ptrdata More(const i_ptrdata&);
	virtual i_ptrdata Lesseq(const i_ptrdata&);
	virtual i_ptrdata Moreeq(const i_ptrdata&);
	virtual i_ptrdata Compare(const i_ptrdata&);
	virtual i_ptrdata Notsame(const i_ptrdata&);
	virtual i_ptrdata And(const i_ptrdata&);
	virtual i_ptrdata Or(const i_ptrdata&);
	virtual i_ptrdata Not();
	virtual i_ptrdata Min();
};

class i_int :public i_data {
public:
	int i;
	i_int(int _i) :i(_i) {}
	virtual wstring tostr() { return to_wstring(i); }
	virtual uchar type() { return t_int; }
	virtual i_ptrdata Pow(const i_ptrdata&);
	virtual i_ptrdata Divi(const i_ptrdata&);
	virtual i_ptrdata Multi(const i_ptrdata&);
	virtual i_ptrdata Mod(const i_ptrdata&);
	virtual i_ptrdata Plus(const i_ptrdata&);
	virtual i_ptrdata Minus(const i_ptrdata&);
	virtual i_ptrdata Less(const i_ptrdata&);
	virtual i_ptrdata More(const i_ptrdata&);
	virtual i_ptrdata Lesseq(const i_ptrdata&);
	virtual i_ptrdata Moreeq(const i_ptrdata&);
	virtual i_ptrdata Compare(const i_ptrdata&);
	virtual i_ptrdata Notsame(const i_ptrdata&);
	virtual i_ptrdata And(const i_ptrdata&);
	virtual i_ptrdata Or(const i_ptrdata&);
	virtual i_ptrdata Not();
	virtual i_ptrdata Min();
};
class i_num :public i_data {
public:
	double n;
	i_num(double _n) :n(_n) {}
	virtual wstring tostr() { return to_wstring(n); }
	virtual uchar type() { return t_num; }
	virtual i_ptrdata Pow(const i_ptrdata&);
	virtual i_ptrdata Divi(const i_ptrdata&);
	virtual i_ptrdata Multi(const i_ptrdata&);
	virtual i_ptrdata Mod(const i_ptrdata&);
	virtual i_ptrdata Plus(const i_ptrdata&);
	virtual i_ptrdata Minus(const i_ptrdata&);
	virtual i_ptrdata Less(const i_ptrdata&);
	virtual i_ptrdata More(const i_ptrdata&);
	virtual i_ptrdata Lesseq(const i_ptrdata&);
	virtual i_ptrdata Moreeq(const i_ptrdata&);
	virtual i_ptrdata Compare(const i_ptrdata&);
	virtual i_ptrdata Notsame(const i_ptrdata&);
	virtual i_ptrdata And(const i_ptrdata&);
	virtual i_ptrdata Or(const i_ptrdata&);
	virtual i_ptrdata Not();
	virtual i_ptrdata Min();
};
class i_bool :public i_data {
public:
	bool b;
	i_bool(bool _b) :b(_b) {}
	virtual wstring tostr() { return b ? L"Âü" : L"°ÅÁþ"; }
	virtual uchar type() { return t_bool; }
	virtual i_ptrdata Less(const i_ptrdata&);
	virtual i_ptrdata More(const i_ptrdata&);
	virtual i_ptrdata Lesseq(const i_ptrdata&);
	virtual i_ptrdata Moreeq(const i_ptrdata&);
	virtual i_ptrdata Compare(const i_ptrdata&);
	virtual i_ptrdata Notsame(const i_ptrdata&);
	virtual i_ptrdata And(const i_ptrdata&);
	virtual i_ptrdata Or(const i_ptrdata&);
	virtual i_ptrdata Not();
};

class i_str :public i_data {
public:
	wstring s;
	i_str(wstring _s) :s(_s) {}
	virtual wstring tostr() { return s; }
	virtual uchar type() { return t_str; }
	virtual i_ptrdata Pow(const i_ptrdata&);
	virtual i_ptrdata Divi(const i_ptrdata&);
	virtual i_ptrdata Multi(const i_ptrdata&);
	virtual i_ptrdata Mod(const i_ptrdata&);
	virtual i_ptrdata Plus(const i_ptrdata&);
	virtual i_ptrdata Minus(const i_ptrdata&);
	virtual i_ptrdata Less(const i_ptrdata&);
	virtual i_ptrdata More(const i_ptrdata&);
	virtual i_ptrdata Lesseq(const i_ptrdata&);
	virtual i_ptrdata Moreeq(const i_ptrdata&);
	virtual i_ptrdata Compare(const i_ptrdata&);
	virtual i_ptrdata Notsame(const i_ptrdata&);
	virtual i_ptrdata And(const i_ptrdata&);
	virtual i_ptrdata Or(const i_ptrdata&);
};
class i_func :public i_data {
public:
	int frame, para, pc;
	i_func(int _pc) :pc(_pc) { frame = 0; para = 0; }
	//virtual wstring tostr() { return s; }
	virtual uchar type() { return t_func; }
};
class i_object :public i_data {
public:
	map<int, i_ptrdata>o;
	//virtual wstring tostr() { return s; }
	virtual uchar type() { return t_object; }
};
class i_cfunc :public i_data {
public:
	void* f;
	i_cfunc(void* ff) :f(ff) {}
	//virtual wstring tostr() { return s; }
	virtual uchar type() { return t_cfunc; }
};
class i_range :public i_data {
public:
	int start, end, now, step;
	i_range(int _start, int _end) {
		step = 1;
		start = _start;
		end = _end;
		now = 0;
	}
	i_range(int _start, int _end, int s) {
		start = _start;
		end = _end;
		step = s;
		now = 0;
	}
	//virtual wstring tostr() { return s; }
	virtual uchar type() { return t_range; }
};
class i_error :public i_data {
public:
	enum {
		e_member_notfound,
		e_range_notint,
	};
	wstring s;
	i_error(int,const wchar*);
	//virtual wstring tostr() { return s; }
	virtual uchar type() { return t_error; }
};
extern vector<i_ptrdata>vm_lit, vm_base;
extern vector<i_ptrdata>vm_opstack;
extern vector<wstring>vm_lit_mem;
extern const wchar* vm_lit_error[100];