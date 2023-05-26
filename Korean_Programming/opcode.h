#pragma once
enum i_opcode {
	//[��ɾ�����] [a] [b] [c] ..
	op_pop,//���� pop
	op_push,//���� a push
	op_pushl,//���ͷ� a��° push
	op_pushn,//���� push
	op_pusht,//�� push
	op_pushf,//���� push
	op_pushs,//���ڿ� �ּ� push

	op_mstore,
	op_lstore,//$ base+a��°�� ����
	op_gstore,//$ a��°�� ����
	op_mload,
	op_lload,//$ base+a��° push
	op_gload,//$ a��° push

	op_calc,//���� ���� a

	op_at,//�迭 pop��° ����
	op_at1,
	op_atd,//�迭 a��° ����
	op_atm,//��� ����
	op_set,//pop(���̺�,�����ġ,������)
	op_lop,//�Ҵ翬�� ���� a(�������� b) 
	op_gop,//�Ҵ翬�� ���� a($b)
	op_mop,//
	op_opset,//
	op_call,//pop(ȣ��,�μ� a��)
	op_calln,//
	op_ret,
	//op_new,//pop ��ü ���� (�μ� a��)

	op_jmp,//a�ٷ� ����
	op_ujmp,//pop=false�� a�ٷ� ����

	op_makea,//�迭 �����
	op_maked,//���� �����
	//op_maker,//���� �����
	op_makeo,//��ü �����
	op_next,//pop �ݺ��� next
	op_makes,
	op_isnext,//pop �ݺ��� next ����?

	op_print,//�����
	op_put,//���
	op_end //�ڵ� ����
};

enum i_op {
	opc_pow = 1, //����
	opc_mul,//��
	opc_div,//������
	opc_mod,//������
	opc_plus,//���ϱ�
	opc_minus,//����
	opc_less,//<
	opc_lesseq,//<=
	opc_more,//>
	opc_moreeq,//>=
	opc_compare,//=
	opc_noteq,//!=
	opc_land,//�׸���
	opc_lor,//�Ǵ�
	opc_not,//!
	opc_min,//-
};

extern vector<int>vm_opcode;