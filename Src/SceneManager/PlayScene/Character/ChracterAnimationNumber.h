#pragma once

//�L�����N�^�[�̃A�j���[�V�����ԍ�
enum class eCHARACTER_ANIMATION_NUMBER : int
{
	NONE = -1,

	WAIT,								//�ҋ@
	SQUAT,								//���Ⴊ��
	JUMP,								//�W�����v
	GUARD,								//�K�[�h
	MOVE_FRONT,							//�O�ړ�
	MOVE_BACK,							//��ړ�
	MOVE_BOOST,							//�u�[�X�g�ړ�
	DAMAGE,								//����
	ATTACK_WEAK_NEUTRAL,				//��j���[�g�����U��
	ATTACK_WEAK_BOTTOM,					//�㉺�U��
	ATTACK_WEKA_SIDE,					//�㉡�U��
	ATTACK_MIDDLE_NEUTRAL,				//���j���[�g�����U��
	ATTACK_MIDDLE_BOTTOM,				//�����U��
	ATTACK_MIDDLE_SIDE,					//�����U��
	WIN_POSE,							//�����|�[�Y
	LOSE_POSE,							//�s�k�|�[�Y

	ANIMATION_NUM						//����
};