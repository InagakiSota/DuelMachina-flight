#pragma once

//�U���̎��
enum class eATTACK_TYPE : int
{
	NONE = -1,

	WEAK_NEUTRAL,		//��j���[�g����
	WEAK_BOTTOM,		//�㉺
	WEAK_SIDE,			//�㉡
	WEAK_TOP,			//���
	WEAK_AERIAL,		//���

	MIDDLE_NEUTRAL,		//���j���[�g����
	MIDDLE_BOTTOM,		//����
	MIDDLE_SIDE,		//����
	MIDDLE_TOP,			//����
	MIDDLE_AERIAL,		//����

	STRONG_NEUTRAL,		//���j���[�g����
	STRONG_BOTTOM,		//����
	STRONG_SIDE,		//����
	STRONG_TOP,			//����
	STRONG_AERIAL,		//����

	ATTACK_TYPE_NUM,
};
