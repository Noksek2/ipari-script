#pragma once
#include "iparidata.h"
i_ptrdata i_num::Plus(const i_ptrdata& right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>(n + ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(n + ((i_num*)right.get())->n);
	case t_str:
		return make_shared < i_str >(to_wstring(n) + ((i_str*)right.get())->s);
	}
	return vm_lit[0];
}
i_ptrdata i_num::Minus(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>(n - ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(n - ((i_num*)right.get())->n);
	}
	return vm_lit[0];
}
i_ptrdata i_num::Multi(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>(n * ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(n * ((i_num*)right.get())->n);
		//case t_str:
			//return make_shared < i_str >(to_wstring(i) + ((i_str*)right.get())->s);
	}
	return vm_lit[0];
}
i_ptrdata i_num::Divi(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>((double)n / (double)((i_int*)right.get())->i);
		break;
	case t_num:
		return make_shared < i_num >((double)n / ((i_num*)right.get())->n);
	}
	return vm_lit[0];
}
i_ptrdata i_num::Pow(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>(pow(n, ((i_int*)right.get())->i));
	case t_num:
		return make_shared < i_num >(pow(n, ((i_num*)right.get())->n));
	}
	return vm_lit[0];
}
i_ptrdata i_num::Mod(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>(fmod(n,((i_int*)right.get())->i));
	case t_num:
		return make_shared < i_num >(fmod(n, ((i_num*)right.get())->n));
	}
	return vm_lit[0];
}
i_ptrdata i_num::And(const i_ptrdata & right) {
	return vm_lit[2];//false
}
i_ptrdata i_num::Or(const i_ptrdata & right) {
	return vm_lit[2];//false
}
i_ptrdata i_num::Compare(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return n == (double)((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return n == ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_num::Notsame(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return n != (double)((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return n != ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_num::Less(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return n < (double)((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return n < ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_num::Lesseq(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return n <= (double)((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return n <= ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_num::More(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return n > (double)((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return n > ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_num::Moreeq(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return n >= (double)((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return n >= ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_num::Min() {
	return make_shared<i_num>(-n);
}
i_ptrdata i_num::Not() {
	return vm_lit[2];
}