#include "Parser.h"
void Parser::print_error(const wchar* file, uchar etype,
	const wchar* msg, int line) {
	wcout << file << L'(' << line << L") : error c" << (int)etype << L" : ";
	switch (etype) {
	case ce_nofile:
		wcout << L"존재하지 않는 파일입니다.";
		break;
	case ce_notoken:
		wcout << msg << L"토큰을 인식할 수 없습니다.";
		break;
	case ce_noident:
		wcout << '\''<<msg << L"'은/는 선언되지 않은 식별자입니다.";
		break;
	case ce_nobrack:case ce_nosquare:
		wcout << L"괄호 안에 식이 필요합니다.";
		break;
	case ce_badenumexp:
		wcout << L"상수 식이 올바르지 않습니다.";
		break;
	case ce_badexp:
		wcout << L"올바르지 않은 식입니다.";
		break;
	case ce_badstr:
		wcout << L"문자열 사용이 잘못되었습니다.";
		break;
	case ce_badident:
		wcout << L"식별자 선언이 잘못되었습니다. '" << msg << '\'';
		break;
	case ce_baddollat:
		wcout << L"@ 또는 $ 뒤에는 식별자만 올 수 있습니다." << '\'';
		break;
	case ce_badmember:
		wcout << L"@로 접근할 수 없습니다.";
		break;
	case ce_baddot:
		wcout << L"멤버의 접근이 잘못되었습니다.";
		break;
	case ce_overident:
		wcout << L"식별자를 재선언할 수 없습니다.'" << msg << '\'';
		break;
	case ce_loopident:
		wcout << L"제어문 내에 기능, 함수, 상수 등의 정적 식별자는 선언할 수 없습니다.";
		break;
	case ce_badbreak:
		wcout << L"분기문은 제어문 밖에서 사용할 수 없습니다.";
		break;
	case ce_badjump:
		wcout << L"점프할 위치가 올바르지 않습니다.";
		break;
	}
	wcout << endl;
	errorcnt++;
}
