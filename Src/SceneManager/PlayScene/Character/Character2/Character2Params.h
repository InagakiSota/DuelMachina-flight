///////////////////////////////////
//�L�����N�^�[2�̒萔�Ǘ��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��18��
///////////////////////////////////

#pragma once

#include <SimpleMath.h>

class Character2Params
{
public:
	//�ő�̗�
	int MAX_HP;
	//�u�[�X�g�e�ʂ̍ő�l
	int BOOST_CAP_MAX;
	//�W�����v�̈ړ���
	float JUMP_FORCE;
	//�O�ړ��̈ړ���
	float MOVE_FRONT_FORCE;
	//��ړ��̈ړ���
	float MOVE_BACK_FORCE;
	//�u�[�X�g�ړ��̈ړ���
	float MOVE_BOOST_FORCE;
	

	//���f���̃T�C�Y
	static const float MODEL_SIZE;
	//Y���̊p�x
	static const float ANGLE_Y;
	//�̂̓����蔻��̃T�C�Y(�ʏ펞)
	static const DirectX::SimpleMath::Vector3 BODY_COLL_SIZE_NORMAL;
	//�̂̓����蔻��̃T�C�Y(���Ⴊ��)
	static const DirectX::SimpleMath::Vector3 BODY_COLL_SIZE_SQUAT;
	//���̓����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 LEG_COLL_SIZE;
	//���̓����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 HEAD_COLL_SIZE;
	//�̂̓����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 MOVE_BOOST_BODY_SIZE;
	//�O�����̃x�N�g��
	static const DirectX::SimpleMath::Vector3 FRONT_VECTOR;
	//�J�������W
	static const DirectX::SimpleMath::Vector3 CAMERA_POS;
	//�ړ��ł���X���W�̍ő�l
	static const float MOVE_LIMIT_X;
	//�ړ��ł���Y���W�̍ő�l
	static const float MOVE_LIMIT_Y;
	//�V�[���h��Y���W
	static const float SHIELD_POS_Y;

	//�u�[�X�g�G�t�F�N�g��X���W
	static const float BOOST_EFFECT_POS_X;
	//�u�[�X�g�G�t�F�N�g��Y���W
	static const float BOOST_EFFECT_POS_Y;
	//�u�[�X�g�G�t�F�N�g�̊p�x(����)	
	static const float BOOST_EFFECT_ANGLE_LEFT;
	//�u�[�X�g�G�t�F�N�g�̊p�x(�E��)
	static const float BOOST_EFFECT_ANGLE_RIGHT;
	//�q�b�g�G�t�F�N�g��Y���W
	static const float HIT_EFFECT_POS_Y;


	//�V���O���g��
public:
	//���g�̃C���X�^���X�̎擾
	static Character2Params* GetInstance();
	//���g�̃C���X�^���X�̉��
	void ReleaseInstance();

	//�X�e�[�^�X�f�[�^�̓ǂݍ���
	void LoadStatusData();


private:
	//�R���X�g���N�^
	Character2Params();
	//�f�X�g���N�^
	~Character2Params();
	//���g�̃C���X�^���X
	static Character2Params* m_pMyInstance;



};