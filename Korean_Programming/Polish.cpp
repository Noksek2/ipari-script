#include "Parser.h"
bool opdirect(uchar o) {
	switch (o) {
	case i_op::opc_min:case opc_pow:return true;
	}
	return false;
}
void Parser::polish_push(uchar optype) {
	//if (!oprank(optype)) {}
	if (optype == _Brackend)polish_brackpop();
	else if (optype != 100)
		polish_pop(oprank(optype), opdirect(optype));
	polish_stack += optype;
}
void Parser::polish_pop(int n,bool b) {
	int toprank = 0;
	if (b)
	{
		while (!polish_stack.empty()) {
			toprank = oprank(polish_stack.back());
			if (toprank < n) {
				vm_opcode.push_back(op_calc);
				vm_opcode.push_back(polish_stack.back());
				polish_stack.pop_back();
			}
			else return;
		}
	}
	else {//¿À¸¥ÂÊ
		while (!polish_stack.empty()) {
			toprank = oprank(polish_stack.back());
			if (toprank <= n) {
				vm_opcode.push_back(op_calc);
				vm_opcode.push_back(polish_stack.back());
				polish_stack.pop_back();
			}
			else return;
		}
	}
}
void Parser::polish_brackpop() {
	char c;
	while (!polish_stack.empty()) {
		if (c=polish_stack.back(),c == 100) {
			polish_stack.pop_back();
			return;
		}
		vm_opcode.push_back(op_calc);
		vm_opcode.push_back(c);
		polish_stack.pop_back();
	}
}
void Parser::polish_clear() {
	while (!polish_stack.empty()) {
		if (polish_stack.back() != 100)
		vm_opcode.push_back(op_calc);
		vm_opcode.push_back(polish_stack.back());
		polish_stack.pop_back();
	}
}