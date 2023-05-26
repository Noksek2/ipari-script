#include "Parser.h"
map<wstring, uchar>i_lex_keyword;
uchar* i_lex_char;
unordered_map<wstring, int>string_map;
void Parser::getfile(const wchar* dir,wstring& s) {
	HANDLE file;
	file = CreateFile(dir, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD size=GetFileSize(file, 0);
	char* buf = (char*)malloc(size);
	(void)ReadFile(file, buf, size, 0, 0);
	if (!buf) {
		print_error(dir, ce_nofile,0,0);
		return;
	}
	int ulen = MultiByteToWideChar(CP_UTF8, 0, buf, size, 0, 0);
	s.resize(ulen+1);
	MultiByteToWideChar(CP_UTF8, 0, buf, size, &s[0], ulen);
	free(buf);
	CloseHandle(file);
}
void Parser::compile(const wchar* file) {
	wstring a;
	getfile(file, a);
	//a = L"출력해 3-100^4^5+100*5\n출력해 30+29";
	lex.emplace_back();
	lex.back().Init(a.c_str(), file);
	nownode = lex.back().node_vec.back();
	parsing();
	vm_base.resize(lex.back().node_main->frame);
	lex.pop_back();
}
void Parser::parsing() {
	Next();
	while (t.type != _eof) {
		try {
			state();
		}
		catch (ErrorMsg m) {
			print_error(lex.back().file.c_str(), m.c, m.msg.c_str(), lex.back().line + 1);
			lex.back().errorflag = true;
			lex.back().strflag = 0;
			polish_clear();
			//break_stack.clear();
			//nowblock = 0;
			//loopblock = 0;
			Next();
		}
	}
}