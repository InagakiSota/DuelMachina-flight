///////////////////////////////////
//�G�t�F�N�g�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��7��
///////////////////////////////////
#include "pch.h"
#include "Effect.h"
#include "../../BinaryFile.h"

//�R���X�g���N�^
Effect::Effect()
{
}

//�f�X�g���N�^
Effect::~Effect()
{
}

///////////////////////////
//�쐬
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Effect::Create()
{
}

///////////////////////////
//������
//����:�����A���W�A�ړ���
//�߂�l:�Ȃ�
//////////////////////////
void Effect::Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity)
{
	m_startPos = m_pos = pos;
	m_startVel = m_vel = velocity;
	m_startLife = m_life = life;
	m_gravity = DirectX::SimpleMath::Vector3(0, 0.001f, 0);
}

///////////////////////////
//�X�V
//����:�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void Effect::Update(DX::StepTimer timer)
{
	float time = float(m_timer.GetTotalSeconds());
	m_timer = timer;

	//m_pos = DirectX::SimpleMath::Vector3(cosf(time+m_vel.x), sinf(time + m_vel.x),0);

	//m_pos.x += 0.01f;
	m_life --;

	m_pos += m_vel;

	if (m_life < 0)
	{
		Initialize(m_startLife, m_startPos, m_startVel);
	}

}
