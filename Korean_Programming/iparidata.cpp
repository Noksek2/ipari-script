#include "iparidata.h"
i_ptrdata i_data::Pow(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Multi(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Mod(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Divi(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Plus(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Minus(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Less(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Lesseq(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::More(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Moreeq(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Compare(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Notsame(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::And(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Or(const i_ptrdata& right) { return vm_lit[0]; }
i_ptrdata i_data::Not() { return vm_lit[0]; }
i_ptrdata i_data::Min() { return vm_lit[0]; }
i_ptrdata i_int::Plus(const i_ptrdata& right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_int>(i + ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(i + ((i_num*)right.get())->n);
	case t_str:
		return make_shared < i_str >(to_wstring(i) + ((i_str*)right.get())->s);
	}
	return vm_lit[0];
}
i_ptrdata i_int::Minus(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_int>(i - ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(i - ((i_num*)right.get())->n);
	}
	return vm_lit[0];
}
i_ptrdata i_int::Multi(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_int>(i * ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(i * ((i_num*)right.get())->n);
		//case t_str:
			//return make_shared < i_str >(to_wstring(i) + ((i_str*)right.get())->s);
	}
	return vm_lit[0];
}
i_ptrdata i_int::Divi(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>((double)i / (double)((i_int*)right.get())->i);
		break;
	case t_num:
		return make_shared < i_num >((double)i / ((i_num*)right.get())->n);
	}
	return vm_lit[0];
}
i_ptrdata i_int::Pow(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_num>(pow(i, ((i_int*)right.get())->i));
	case t_num:
		return make_shared < i_num >(pow(i, ((i_num*)right.get())->n));
	}
	return vm_lit[0];
}
i_ptrdata i_int::Mod(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return make_shared<i_int>(i % ((i_int*)right.get())->i);
	case t_num:
		return make_shared < i_num >(fmod((double)i, ((i_num*)right.get())->n));
	}
	return vm_lit[0];
}
i_ptrdata i_int::And(const i_ptrdata & right) {
	return vm_lit[2];//false
}
i_ptrdata i_int::Or(const i_ptrdata & right) {
	return vm_lit[2];//false
}
i_ptrdata i_int::Compare(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return i == ((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return (double)i == ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_int::Notsame(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return i != ((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return (double)i != ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_int::Less(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return i < ((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return (double)i < ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_int::Lesseq(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return i <= ((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return (double)i <= ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_int::More(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return i > ((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return (double)i > ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_int::Moreeq(const i_ptrdata & right) {
	switch (right->type()) {
	case t_int:
		return i >= ((i_int*)right.get())->i ? vm_lit[1] : vm_lit[2];
	case t_num:
		return (double)i >= ((i_num*)right.get())->n ? vm_lit[1] : vm_lit[2];
	}
	return vm_lit[2];
}
i_ptrdata i_int::Min() {
	return make_shared<i_int>(-i);
}
i_ptrdata i_int::Not() {
	return vm_lit[2];
}