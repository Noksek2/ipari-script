#include "Parser.h"
#include <conio.h>
#pragma warning(disable:4996)
vector<int>vm_opcode;
vector<i_ptrdata>vm_lit, vm_base;
vector<i_ptrdata>vm_opstack;
void keyword_init() {
	i_lex_keyword.emplace(L"출력", _put);
	i_lex_keyword.emplace(L"출력해", _print);
	i_lex_keyword.emplace(L"함수", _func);
	i_lex_keyword.emplace(L"변수", _var);
	i_lex_keyword.emplace(L"반복", _for);
	i_lex_keyword.emplace(L"무한반복", _loop);
	i_lex_keyword.emplace(L"되풀이", _while);
	i_lex_keyword.emplace(L"그리고", _And);
	i_lex_keyword.emplace(L"또는", _Or);
	i_lex_keyword.emplace(L"만약", _if);
	i_lex_keyword.emplace(L"아니고", _elif);
	i_lex_keyword.emplace(L"아니면", _else);
	i_lex_keyword.emplace(L"판단", _switch);
	i_lex_keyword.emplace(L"반환", _return);
	i_lex_keyword.emplace(L"객체", _class);
	i_lex_keyword.emplace(L"끝", _end);
	i_lex_keyword.emplace(L"상수", _enum);
	i_lex_keyword.emplace(L"불러오기", _import);
	i_lex_keyword.emplace(L"사용하기", _using);
	i_lex_keyword.emplace(L"참", _true);
	i_lex_keyword.emplace(L"거짓", _false);
	i_lex_keyword.emplace(L"공백", _null);
	i_lex_keyword.emplace(L"기능", _pack);

	i_lex_keyword.emplace(L"탈출", _break); i_lex_keyword.emplace(L"건너뛰기", _skip);

	i_lex_keyword.emplace(L"->", _Case);
	i_lex_keyword.emplace(L"^", _Pow);
	i_lex_keyword.emplace(L"*", _Multi);
	i_lex_keyword.emplace(L"/", _Divi);
	i_lex_keyword.emplace(L"%", _Mod);
	i_lex_keyword.emplace(L"+", _Plus);
	i_lex_keyword.emplace(L"-", _Minus);
	i_lex_keyword.emplace(L"<", _Less);
	i_lex_keyword.emplace(L"<=", _Lesseq);
	i_lex_keyword.emplace(L">", _More);
	i_lex_keyword.emplace(L">=", _Moreeq);
	i_lex_keyword.emplace(L"!=", _Noteq);
	i_lex_keyword.emplace(L"~", _Range);
	i_lex_keyword.emplace(L"..", _Range2);

	i_lex_keyword.emplace(L"=", _Equal);
	i_lex_keyword.emplace(L"!", _Not);

	i_lex_keyword.emplace(L"^=", _Poweq);
	i_lex_keyword.emplace(L"*=", _Multieq);
	i_lex_keyword.emplace(L"/=", _Divieq);
	i_lex_keyword.emplace(L"%=", _Modeq);
	i_lex_keyword.emplace(L"+=", _Pluseq);
	i_lex_keyword.emplace(L"-=", _Minuseq);
	i_lex_keyword.emplace(L",", _Comma);
	i_lex_keyword.emplace(L".", _Dot);
	i_lex_keyword.emplace(L"'", _Quot);
	i_lex_keyword.emplace(L"\"", _Quots);
	i_lex_keyword.emplace(L"#", _Sharp);
	i_lex_keyword.emplace(L"##", _Comment);
	i_lex_keyword.emplace(L"$", _Doll);
	i_lex_keyword.emplace(L"@", _Atsign);
	i_lex_keyword.emplace(L":", _Colon);
	i_lex_keyword.emplace(L";", _Semi);
	
	i_lex_keyword.emplace(L"(", _Brack); i_lex_keyword.emplace(L")", _Brackend);
	i_lex_keyword.emplace(L"[", _Square); i_lex_keyword.emplace(L"]", _Squareend);
	i_lex_keyword.emplace(L"{", _Block); i_lex_keyword.emplace(L"}", _Blockend);
}
void compile_init() {
	wcout.imbue(locale("kor"));
	wcin.imbue(locale("kor"));
	keyword_init();

	i_lex_char = new uchar[65536];
	for (wchar i = 0x1100; i <= 0x11FF; i++)
		i_lex_char[i] = lit_str;
	for (wchar i = L'0'; i <= L'9'; i++)
		i_lex_char[i] = lit_int;
	for (wchar i = 0x3131; i <= 0x318E; i++)
		i_lex_char[i] = lit_str;
	for (wchar i = 0xAC00; i <= 0xD7A3; i++)
		i_lex_char[i] = lit_str;
	for (wchar i = L'A'; i <= L'Z';i++)
		i_lex_char[i] = lit_str;
	for (wchar i = L'a'; i <= L'z';i++)
		i_lex_char[i] = lit_str;
	i_lex_char['_'] = lit_str;
	i_lex_char['\''] = _Quot; i_lex_char['"'] = _Quots;
	i_lex_char['#'] = _Sharp;
}
void compile_release() {
	delete[] i_lex_char;
	i_lex_char = 0;
}
void wmain(int argc, wchar** argv)
{
	time_t s, e;
	wchar dir[_MAX_PATH];
	wcin.imbue(locale("kor"));
	wstring file;
	if (argc == 1) {
		cout << "파일 입력(.ipari) : ";
		wcin >> file;
		file += L".ipari";
	}
	else file = argv[1];
	compile_init();
	(void)_wfullpath(dir, file.c_str(), _MAX_PATH);
	Parser* parse = new Parser();
	vm_lit.push_back(make_shared<i_data>());
	vm_lit.push_back(make_shared<i_bool>(true));
	vm_lit.push_back(make_shared<i_bool>(false));
	parse->compile(dir);
	int cnt = parse->errorcnt;
	delete parse;
	compile_release();
	if (cnt) {
		cout << "오류 : " << cnt << '\n';
		return;
	}
	vm_opcode.push_back(op_end);

	int opcode_size[120];
	opcode_size[op_end] =
		opcode_size[op_pushn] =
		opcode_size[op_pusht] =
		opcode_size[op_pushf] =
		opcode_size[op_pop] =
		1;
	opcode_size[op_push] =
		opcode_size[op_pushl] =
		opcode_size[op_print] =
		opcode_size[op_put] =
		opcode_size[op_jmp] =
		opcode_size[op_ujmp] =
		opcode_size[op_makea] =
		opcode_size[op_maked] =
		opcode_size[op_makes] =
		opcode_size[op_calc] =
		opcode_size[op_lstore] =
		opcode_size[op_gstore] =
		opcode_size[op_lload] =
		opcode_size[op_gload] =
		opcode_size[op_at] =
		opcode_size[op_call] =
		opcode_size[op_calln] =
		2;
	opcode_size[op_gop] =
		opcode_size[op_lop] =
		3;
	auto pc = vm_opcode.begin();
	i_ptrdata n1, n2;
	int ts = clock(),te=0;
	int pbase=0;
	wstring str;
	vector<int>prevbase,prevpc;
	int pci = 0;
	for (;;) {
	pc_main:
		switch (*pc) {
		case op_pop:
			vm_opstack.pop_back();
			break;
		case op_call:
			n1 = *(vm_opstack.end() - 1 - *(pc + 1));
			switch (n1->type()) {
			case i_data::t_cfunc:
				//vm_opstack.push_back(
				//	shared_ptr<i_data>((((i_data * (*)(i_ptrdata*, int))(((i_cfunc*)n1.get())->f))(n2.get())))
				//);
				break;
			case i_data::t_func:
				//pc
				//frame
				
				prevbase.push_back(pbase);
				pbase = vm_base.size();
				for (int i = 0; i < *(pc + 1)/2; i++) {
					n2 = *(vm_opstack.end() - 1-i);
					*(vm_opstack.end() - i-1) = *(vm_opstack.end() - *(pc + 1));
					*(vm_opstack.end() - *(pc + 1)) = n2;
				}
				vm_base.resize(vm_base.size() + ((i_func*)n1.get())->frame);
				prevpc.push_back(pci+2);
				pci = ((i_func*)n1.get())->pc;
				pc = vm_opcode.begin() + pci;
				n2 = n1 = nullptr;
				goto pc_main;
			}
			n2 = n1 = nullptr;
			break;
			/*출력 관련*/
		case op_ret:
			pbase = prevbase.back();
			pci = prevpc.back();
			pc = vm_opcode.begin() + pci;
			prevbase.pop_back(); prevpc.pop_back();
			goto pc_main;
		case op_print:
			for (int i = *(pc + 1); i > 0; i--) {
				wcout << ((vm_opstack.end() - i)->get())->tostr();
			}
			vm_opstack.resize(vm_opstack.size() - *(pc + 1));
			wcout << endl;
			break;
		case op_put:
			for (int i = *(pc + 1); i > 0; i--) {
				wcout << ((vm_opstack.end() - i)->get())->tostr();
			}
			vm_opstack.resize(vm_opstack.size() - *(pc + 1));
			break;
			/*PUSH 관련*/
		case op_push:
			vm_opstack.push_back(make_shared<i_int>(*(pc + 1)));
			break;
		case op_pushl:
			vm_opstack.push_back(vm_lit[*(pc + 1)]);
			break;
		case op_pushn:
			vm_opstack.push_back(vm_lit[0]);
			break;
		case op_pusht:
			vm_opstack.push_back(vm_lit[1]);
			break;
		case op_pushf:
			vm_opstack.push_back(vm_lit[2]);
			break;
			/*JMP 관련*/
		case op_jmp:
			pci = *(pc + 1);
			pc = vm_opcode.begin() + pci;
			goto pc_main;
			break;
		case op_ujmp:
			n1 = vm_opstack.back();
			if (n1->type() == i_data::t_bool) {
				if (!((i_bool*)n1.get())->b) {
					pci = *(pc + 1);
					pc = vm_opcode.begin() + pci;
					n1 = nullptr;
					goto pc_main;
				}
			}
			n1 = nullptr;
			break;
			/*MAKE 관련*/
		case op_makes:
			for (int i = *(pc + 1); i > 0; i--) {
				str += (vm_opstack.end() - i)->get()->tostr();
			}
			vm_opstack.resize(vm_opstack.size() - *(pc + 1));
			vm_opstack.emplace_back(make_shared<i_str>(str));
			str = L"";
			break;
		case op_makea:
			break;
			/*STORE 관련*/
		case op_gstore:
			vm_base[*(pc + 1)] = vm_opstack.back();
			vm_opstack.pop_back();
			break;
		case op_lstore:
			vm_base[pbase + *(pc + 1)] = vm_opstack.back();
			vm_opstack.pop_back();
			break;
		case op_gop:
			n1 = vm_opstack.back();
			n2 = vm_base[*(pc + 2)];
			vm_opstack.pop_back();
			switch (*(pc + 1)) {
			case opc_pow:vm_base[*(pc + 2)] = n2->Pow(n1);
				break;
			case opc_mul:vm_base[*(pc + 2)] = n2->Multi(n1);
				break;
			case opc_div:vm_base[*(pc + 2)] = n2->Divi(n1);
				break;
			case opc_mod:vm_base[*(pc + 2)] = n2->Mod(n1);
				break;
			case opc_plus:vm_base[*(pc + 2)] = n2->Plus(n1);
				break;
			case opc_minus:vm_base[*(pc + 2)] = n2->Minus(n1);
				break;
			case opc_compare:vm_base[*(pc + 2)] = n2->Compare(n1);
				break;
			case opc_noteq:vm_base[*(pc + 2)] = n2->Notsame(n1);
				break;
			case opc_less:vm_base[*(pc + 2)] = n2->Less(n1);
				break;
			case opc_lesseq:vm_base[*(pc + 2)] = n2->Lesseq(n1);
				break;
			case opc_more:
				vm_base[*(pc + 2)] = n2->More(n1);
				break;
			case opc_moreeq:
				vm_base[*(pc + 2)] = n2->Moreeq(n1);
				break;
			case opc_land:
				vm_base[*(pc + 2)] = n2->And(n1);
				break;
			case opc_lor:
				vm_base[*(pc + 2)] = n2->Or(n1);
				break;
			}
			n1 = nullptr;
			break;
		case op_lop:
			n1 = vm_opstack.back();
			n2 = vm_base[pbase + *(pc + 2)];
			vm_opstack.pop_back();
			switch (*(pc + 1)) {
			case opc_pow:vm_base[pbase + *(pc + 2)] = n2->Pow(n1);
				break;
			case opc_mul:vm_base[pbase + *(pc + 2)] = n2->Multi(n1);
				break;
			case opc_div:vm_base[pbase + *(pc + 2)] = n2->Divi(n1);
				break;
			case opc_mod:vm_base[pbase + *(pc + 2)] = n2->Mod(n1);
				break;
			case opc_plus:vm_base[pbase + *(pc + 2)] = n2->Plus(n1);
				break;
			case opc_minus:vm_base[pbase + *(pc + 2)] = n2->Minus(n1);
				break;
			case opc_compare:vm_base[pbase + *(pc + 2)] = n2->Compare(n1);
				break;
			case opc_noteq:vm_base[pbase + *(pc + 2)] = n2->Notsame(n1);
				break;
			case opc_less:vm_base[pbase + *(pc + 2)] = n2->Less(n1);
				break;
			case opc_lesseq:vm_base[pbase + *(pc + 2)] = n2->Lesseq(n1);
				break;
			case opc_more:
				vm_base[pbase + *(pc + 2)] = n2->More(n1);
				break;
			case opc_moreeq:
				vm_base[pbase + *(pc + 2)] = n2->Moreeq(n1);
				break;
			case opc_land:
				vm_base[pbase + *(pc + 2)] = n2->And(n1);
				break;
			case opc_lor:
				vm_base[pbase + *(pc + 2)] = n2->Or(n1);
				break;
			}
			n1 = nullptr;
			break;

		case op_gload:
			vm_opstack.push_back(vm_base[*(pc + 1)]);
			break;
		case op_lload:
			vm_opstack.push_back(vm_base[pbase + *(pc + 1)]);
			break;
			/*연산 관련
			case op_min:
			n1 = vm_opstack.back()->Min();
			vm_opstack.pop_back();
			vm_opstack.push_back(n1);
			n1 = nullptr;
			break;
		case op_not:
			n1 = vm_opstack.back()->Not();
			vm_opstack.pop_back();
			vm_opstack.push_back(n1);
			n1 = nullptr;
			break;*/
		
		case op_calc:
			n2 = vm_opstack.back();
			vm_opstack.pop_back();
			if (*(pc + 1) != opc_not&& *(pc + 1) != opc_min) {
				n1 = vm_opstack.back();
				vm_opstack.pop_back();
			}
			else if(*(pc + 1) == opc_not){
				vm_opstack.push_back(n2->Not());
				break;
			}
			else if (*(pc + 1) == opc_min) {
				vm_opstack.push_back(n2->Min());
				break;
			}
			switch (*(pc + 1)) {
			case opc_pow:vm_opstack.push_back(n1->Pow(n2));
				break;
			case opc_mul:vm_opstack.push_back(n1->Multi(n2));
				break;
			case opc_div:vm_opstack.push_back(n1->Divi(n2));
				break;
			case opc_mod:vm_opstack.push_back(n1->Mod(n2));
				break;
			case opc_plus:vm_opstack.push_back(n1->Plus(n2));
				break;
			case opc_minus:vm_opstack.push_back(n1->Minus(n2));
				break;
			case opc_compare:vm_opstack.push_back(n1->Compare(n2));
				break;
			case opc_noteq:vm_opstack.push_back(n1->Notsame(n2));
				break;
			case opc_less:vm_opstack.push_back(n1->Less(n2));
				break;
			case opc_lesseq:vm_opstack.push_back(n1->Lesseq(n2));
				break;
			case opc_more:vm_opstack.push_back(n1->More(n2));
				break;
			case opc_moreeq:vm_opstack.push_back(n1->Moreeq(n2));
				break;
			case opc_land:vm_opstack.push_back(n1->And(n2));
				break;
			case opc_lor:vm_opstack.push_back(n1->Or(n2));
				break;
			}
			n1 = n2 = nullptr;
			break;
		case op_end:
			te = clock();
			if (argc == 1)cout << "\nRuntime time : " << (double)(te - ts) / (double)CLOCKS_PER_SEC << "sec";
			return;
		}
		pc += opcode_size[*pc];
		pci += opcode_size[*pc];
	}
	_getch();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

