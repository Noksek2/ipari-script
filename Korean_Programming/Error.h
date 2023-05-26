#pragma once
#include "_Lexer.h"
enum ErrorType {
	ce_nofile,//존재하지 않는 파일입니다.
	ce_notoken,//토큰을 인식할 수 없습니다.
	ce_noident,//선언되지 않은 식별자입니다.
	ce_nobrack,//괄호 안에 식이 필요합니다.
	ce_nosquare,//괄호 안에 식이 필요합니다.
	ce_badexp,//올바르지 않은 식입니다.
	ce_badstr,//문자열 사용이 잘못되었습니다.
	ce_badident,//식별자 선언이 잘못되었습니다. 
	ce_badenumexp,//상수 식이 올바르지 않습니다.
	ce_baddollat,//@ 또는 $ 뒤에는 식별자만 올 수 있습니다.
	ce_badmember,//@로 접근할 수 없습니다.
	ce_baddot,//멤버의 접근이 잘못되었습니다.
	ce_overident,//식별자를 재선언할 수 없습니다.
	ce_loopident,//제어문 내에 기능, 함수, 상수 등의 정적 식별자는 선언할 수 없습니다.
	ce_badbreak,//분기문은 제어문 밖에서 사용할 수 없습니다.
	ce_badlocfunc,//함수를 선언할 수 없는 위치입니다.
	ce_badjump,//점프할 위치가 올바르지 않습니다.
	ce_badtype,//타입
	ce_noequal,
	ce_noaccident,//접근할 수 없는 식별자입니다.
};
struct ErrorMsg {
	uchar c;
	wstring msg;
	ErrorMsg(uchar cc,const wstring& n):c(cc),msg(n) {}
};