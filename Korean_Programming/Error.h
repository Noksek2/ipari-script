#pragma once
#include "_Lexer.h"
enum ErrorType {
	ce_nofile,//�������� �ʴ� �����Դϴ�.
	ce_notoken,//��ū�� �ν��� �� �����ϴ�.
	ce_noident,//������� ���� �ĺ����Դϴ�.
	ce_nobrack,//��ȣ �ȿ� ���� �ʿ��մϴ�.
	ce_nosquare,//��ȣ �ȿ� ���� �ʿ��մϴ�.
	ce_badexp,//�ùٸ��� ���� ���Դϴ�.
	ce_badstr,//���ڿ� ����� �߸��Ǿ����ϴ�.
	ce_badident,//�ĺ��� ������ �߸��Ǿ����ϴ�. 
	ce_badenumexp,//��� ���� �ùٸ��� �ʽ��ϴ�.
	ce_baddollat,//@ �Ǵ� $ �ڿ��� �ĺ��ڸ� �� �� �ֽ��ϴ�.
	ce_badmember,//@�� ������ �� �����ϴ�.
	ce_baddot,//����� ������ �߸��Ǿ����ϴ�.
	ce_overident,//�ĺ��ڸ� �缱���� �� �����ϴ�.
	ce_loopident,//��� ���� ���, �Լ�, ��� ���� ���� �ĺ��ڴ� ������ �� �����ϴ�.
	ce_badbreak,//�б⹮�� ��� �ۿ��� ����� �� �����ϴ�.
	ce_badlocfunc,//�Լ��� ������ �� ���� ��ġ�Դϴ�.
	ce_badjump,//������ ��ġ�� �ùٸ��� �ʽ��ϴ�.
	ce_badtype,//Ÿ��
	ce_noequal,
	ce_noaccident,//������ �� ���� �ĺ����Դϴ�.
};
struct ErrorMsg {
	uchar c;
	wstring msg;
	ErrorMsg(uchar cc,const wstring& n):c(cc),msg(n) {}
};