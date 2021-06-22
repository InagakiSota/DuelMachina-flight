///////////////////////////////////
//�G�t�F�N�g�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��7��
///////////////////////////////////
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

class Effect
{
public:
	//�R���X�g���N�^
	Effect();
	//�f�X�g���N�^
	~Effect();

	//�쐬
	void Create();

	//������
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity);
	//�X�V
	void Update(DX::StepTimer timer);

	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetPos() 
	{
		return m_pos;
	}

	//�ړ��ʂ̎擾
	DirectX::SimpleMath::Vector3 GetVel()
	{ 
		return m_vel; 
	}

	//�d�͂̃t���O�̐ݒ�
	void SetGravity(bool isGravity)
	{
		m_isGravity = isGravity;
	}

private:

	//�^�C�}�[
	DX::StepTimer m_timer;

	//�d��
	DirectX::SimpleMath::Vector3 m_gravity;
	//���W
	DirectX::SimpleMath::Vector3 m_pos;
	//�ړ���
	DirectX::SimpleMath::Vector3 m_vel;
	//����
	float m_life;

	//�����`��
	DirectX::SimpleMath::Vector3 m_startPos;
	//�����ړ���
	DirectX::SimpleMath::Vector3 m_startVel;
	//��������
	float m_startLife;

	//�d�͂̃t���O
	bool m_isGravity;

};