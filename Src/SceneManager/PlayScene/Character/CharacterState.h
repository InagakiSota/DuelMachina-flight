///////////////////////////////////
//�L�����N�^�[�̃X�e�[�g�̗񋓑�
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��17��
///////////////////////////////////

#pragma once

enum class eCHARACTER_STATE : int
{
	NONE = -1,

	WAIT,			//�ҋ@
	JUMP,			//�W�����v
	MOVE,			//�ړ�
	MOVE_FRONT,		//�O�ړ�
	MOVE_BACK,		//���ړ�
	MOVE_UP,		//��ړ�
	MOVE_DOWN,		//���ړ�
	SQUAT,			//���Ⴊ��
	DAMAGE,			//����
	GUARD,			//�K�[�h
	SQUAT_GUARD,	//���Ⴊ�݃K�[�h
	BOOST_MOVE,		//�u�[�X�g�ړ�
	BOOST_MOVE_FRONT,	//�u�[�X�g�ړ��@�O
	BOOST_MOVE_BACK,	//�u�[�X�g�ړ��@��
	BOOST_MOVE_UP,		//�u�[�X�g�ړ��@��
	BOOST_MOVE_DOWN,	//�u�[�X�g�ړ��@��
	WIN,			//����
	LOSE,			//�s�k


	MAX_NUM
};
