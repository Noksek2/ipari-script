#include "iparidata.h"
const wchar* vm_lit_error[100];
i_error::i_error(int i,const wchar* s) {
	wcout << vm_lit_error[i] << s << endl;
}