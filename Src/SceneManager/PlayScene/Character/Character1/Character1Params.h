///////////////////////////////////
//�L�����N�^�[1�̒萔�Ǘ��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��18��
///////////////////////////////////

#pragma once

#include <SimpleMath.h>

class Character1Params
{
public:

	//�ő�̗�
	int MAX_HP;
	//�u�[�X�g�e�ʂ̍ő�l
	int BOOST_CAP_MAX;

	//�O�ړ��̈ړ���
	float MOVE_FRONT_FORCE;

	//��ړ��̈ړ���
	float MOVE_BACK_FORCE;

	//�W�����v�̈ړ���
	float JUMP_FORCE;

	//�u�[�X�g�ړ��̈ړ���
	float MOVE_BOOST_FORCE;


	//Y���̊p�x
	static const float ANGLE_Y;
	//�̂̃T�C�Y
	static const float BODY_SIZE;
	//�̂̓����蔻��̃T�C�Y(�ʏ펞)
	static const DirectX::SimpleMath::Vector3 BODY_COLL_SIZE_NORMAL;
	//���̓����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 LEG_COLL_SIZE;
	//���̓����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 HEAD_COLL_SIZE;
	//�O�����̃x�N�g��
	static const DirectX::SimpleMath::Vector3 FRONT_VECTOR;
	//�J�������W
	static const DirectX::SimpleMath::Vector3 CAMERA_POS;
	//�̂̓����蔻��
	static const DirectX::SimpleMath::Vector3 MOVE_BOOST_BODY_SIDE;
	//�ړ��ł���X���W�̍ő�l
	static const float MOVE_LIMIT_X;
	//�ړ��ł���Y���W�̍ő�l
	static const float MOVE_LIMIT_Y;

	//���Ⴊ�ݏ�Ԃ̑̂̃T�C�Y
	static const DirectX::SimpleMath::Vector3 BODY_COLL_SIZE_SQUAT;

	//�u�[�X�g�G�t�F�N�g��X���W
	static const float BOOST_EFFECT_POS_X;
	//�u�[�X�g�G�t�F�N�g��Y���W
	static const float BOOST_EFFECT_POS_Y;
	//�u�[�X�g�G�t�F�N�g�̊p�x(����)	
	static const float BOOST_EFFECT_ANGLE_LEFT;
	//�u�[�X�g�G�t�F�N�g�̊p�x(�E��)
	static const float BOOST_EFFECT_ANGLE_RIGHT;



//�V���O���g��
public:
	//���g�̃C���X�^���X�̎擾
	static Character1Params* GetInstance();
	//���g�̃C���X�^���X�̉��
	void ReleaseInstance();

	//�X�e�[�^�X�f�[�^�̓ǂݍ���
	void LoadStatusData();


private:
	//�R���X�g���N�^
	Character1Params();
	//�f�X�g���N�^
	~Character1Params();
	//���g�̃C���X�^���X
	static Character1Params* m_pMyInstance;


};