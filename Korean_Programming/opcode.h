#pragma once
enum i_opcode {
	//[명령어종류] [a] [b] [c] ..
	op_pop,//스택 pop
	op_push,//정수 a push
	op_pushl,//리터럴 a번째 push
	op_pushn,//다음 push
	op_pusht,//참 push
	op_pushf,//거짓 push
	op_pushs,//문자열 주소 push

	op_mstore,
	op_lstore,//$ base+a번째에 대입
	op_gstore,//$ a번째에 대입
	op_mload,
	op_lload,//$ base+a번째 push
	op_gload,//$ a번째 push

	op_calc,//연산 종류 a

	op_at,//배열 pop번째 접근
	op_at1,
	op_atd,//배열 a번째 접근
	op_atm,//멤버 접근
	op_set,//pop(테이블,요소위치,데이터)
	op_lop,//할당연산 종류 a(지역변수 b) 
	op_gop,//할당연산 종류 a($b)
	op_mop,//
	op_opset,//
	op_call,//pop(호출,인수 a개)
	op_calln,//
	op_ret,
	//op_new,//pop 객체 생성 (인수 a개)

	op_jmp,//a줄로 점프
	op_ujmp,//pop=false면 a줄로 점프

	op_makea,//배열 만들기
	op_maked,//사전 만들기
	//op_maker,//범위 만들기
	op_makeo,//객체 만들기
	op_next,//pop 반복자 next
	op_makes,
	op_isnext,//pop 반복자 next 가능?

	op_print,//출력해
	op_put,//출력
	op_end //코드 종료
};

enum i_op {
	opc_pow = 1, //제곱
	opc_mul,//곱
	opc_div,//나누기
	opc_mod,//나머지
	opc_plus,//더하기
	opc_minus,//빼기
	opc_less,//<
	opc_lesseq,//<=
	opc_more,//>
	opc_moreeq,//>=
	opc_compare,//=
	opc_noteq,//!=
	opc_land,//그리고
	opc_lor,//또는
	opc_not,//!
	opc_min,//-
};

extern vector<int>vm_opcode;