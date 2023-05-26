#pragma once
#include "iparidata.h"
i_ptrdata i_str::Plus(const i_ptrdata& right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_str>(s + to_wstring(((i_int*)right.get())->i));
	case t_num:
		return make_shared<i_str>(s + to_wstring(((i_num*)right.get())->n));
	case t_str:
		return make_shared < i_str >(s+ ((i_str*)right.get())->s);
	}
	return vm_lit[0];
}
i_ptrdata i_str::Minus(const i_ptrdata & right) {
	return vm_lit[0];
}
i_ptrdata i_str::Multi(const i_ptrdata & right) {
	//switch (right->type()) {
	//case t_int:
		//return make_shared<i_num>(n * ((i_int*)right.get())->i);
	//}
	return vm_lit[0];
}
i_ptrdata i_str::Divi(const i_ptrdata & right) {
	return vm_lit[0];
}
i_ptrdata i_str::Pow(const i_ptrdata & right) {
	return vm_lit[0];
}
i_ptrdata i_str::Mod(const i_ptrdata & right) {
	return vm_lit[0];
}
i_ptrdata i_str::And(const i_ptrdata & right) {
	return vm_lit[2];//false
}
i_ptrdata i_str::Or(const i_ptrdata & right) {
	return vm_lit[2];//false
}
i_ptrdata i_str::Compare(const i_ptrdata & right) {
	switch (right->type()) {
	case t_str:
		return s == ((i_str*)right.get())->s ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_str::Notsame(const i_ptrdata & right) {
	switch (right->type()) {
	case t_str:
		return s != ((i_str*)right.get())->s ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_str::Less(const i_ptrdata & right) {
	switch (right->type()) {
	case t_str:
		return s < ((i_str*)right.get())->s ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_str::Lesseq(const i_ptrdata & right) {
	switch (right->type()) {
	case t_str:
		return s <= ((i_str*)right.get())->s ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_str::More(const i_ptrdata & right) {
	switch (right->type()) {
	case t_str:
		return s > ((i_str*)right.get())->s ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_str::Moreeq(const i_ptrdata & right) {
	switch (right->type()) {
	case t_str:
		return s >= ((i_str*)right.get())->s ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}