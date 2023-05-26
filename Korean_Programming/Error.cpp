#include "Parser.h"
void Parser::print_error(const wchar* file, uchar etype,
	const wchar* msg, int line) {
	wcout << file << L'(' << line << L") : error c" << (int)etype << L" : ";
	switch (etype) {
	case ce_nofile:
		wcout << L"�������� �ʴ� �����Դϴ�.";
		break;
	case ce_notoken:
		wcout << msg << L"��ū�� �ν��� �� �����ϴ�.";
		break;
	case ce_noident:
		wcout << '\''<<msg << L"'��/�� ������� ���� �ĺ����Դϴ�.";
		break;
	case ce_nobrack:case ce_nosquare:
		wcout << L"��ȣ �ȿ� ���� �ʿ��մϴ�.";
		break;
	case ce_badenumexp:
		wcout << L"��� ���� �ùٸ��� �ʽ��ϴ�.";
		break;
	case ce_badexp:
		wcout << L"�ùٸ��� ���� ���Դϴ�.";
		break;
	case ce_badstr:
		wcout << L"���ڿ� ����� �߸��Ǿ����ϴ�.";
		break;
	case ce_badident:
		wcout << L"�ĺ��� ������ �߸��Ǿ����ϴ�. '" << msg << '\'';
		break;
	case ce_baddollat:
		wcout << L"@ �Ǵ� $ �ڿ��� �ĺ��ڸ� �� �� �ֽ��ϴ�." << '\'';
		break;
	case ce_badmember:
		wcout << L"@�� ������ �� �����ϴ�.";
		break;
	case ce_baddot:
		wcout << L"����� ������ �߸��Ǿ����ϴ�.";
		break;
	case ce_overident:
		wcout << L"�ĺ��ڸ� �缱���� �� �����ϴ�.'" << msg << '\'';
		break;
	case ce_loopident:
		wcout << L"��� ���� ���, �Լ�, ��� ���� ���� �ĺ��ڴ� ������ �� �����ϴ�.";
		break;
	case ce_badbreak:
		wcout << L"�б⹮�� ��� �ۿ��� ����� �� �����ϴ�.";
		break;
	case ce_badjump:
		wcout << L"������ ��ġ�� �ùٸ��� �ʽ��ϴ�.";
		break;
	}
	wcout << endl;
	errorcnt++;
}
