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
	MOVE_FRONT,		//�O�ړ�
	MOVE_BACK,		//���ړ�
	SQUAT,			//���Ⴊ��
	DAMAGE,			//����
	GUARD,			//�K�[�h
	SQUAT_GUARD,	//���Ⴊ�݃K�[�h
	BOOST_MOVE,		//�u�[�X�g�ړ�
	WIN,			//����
	LOSE,			//�s�k

	MAX_NUM
};
