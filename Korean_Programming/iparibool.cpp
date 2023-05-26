#pragma once
#include "iparidata.h"
i_ptrdata i_bool::And(const i_ptrdata & right) {
	if (right->type() == t_bool) {
		return (b && ((i_bool*)right.get())->b ? vm_lit[1] : vm_lit[2]);
	}
	return vm_lit[2];//false
}
i_ptrdata i_bool::Or(const i_ptrdata & right) {
	if (right->type() == t_bool) {
		return (b || ((i_bool*)right.get())->b ? vm_lit[1] : vm_lit[2]);
	}
	return vm_lit[2];//false
}
i_ptrdata i_bool::Compare(const i_ptrdata & right) {
	if (right->type() == t_bool) {
		return (b == ((i_bool*)right.get())->b ? vm_lit[1] : vm_lit[2]);
	}
	return vm_lit[2];
}
i_ptrdata i_bool::Notsame(const i_ptrdata & right) {
	if (right->type() == t_bool) {
		return (b != ((i_bool*)right.get())->b ? vm_lit[1] : vm_lit[2]);
	}
	return vm_lit[2];
}
i_ptrdata i_bool::Less(const i_ptrdata & right) {
	return vm_lit[2];
}
i_ptrdata i_bool::Lesseq(const i_ptrdata & right) {
	return vm_lit[2];
}
i_ptrdata i_bool::More(const i_ptrdata & right) {
	return vm_lit[2];
}
i_ptrdata i_bool::Moreeq(const i_ptrdata & right) {
	return vm_lit[2];
}
i_ptrdata i_bool::Not() {
	return (!b ? vm_lit[1] : vm_lit[2]);
}