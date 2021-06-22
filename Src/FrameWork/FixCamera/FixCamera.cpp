#include "pch.h"
#include "FixCamera.h"

//�R���X�g���N�^
FixCamera::FixCamera()
	//:m_viewMatrix{},
	//m_projectionMatrix{},
	//m_eye{},
	//m_target{},
	//m_up{}
{
}

//�f�X�g���N�^
FixCamera::~FixCamera()
{
}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FixCamera::Initialize()
{
	m_eye = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 10.0f);
	m_target = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	m_up = DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f);

	m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FixCamera::Update()
{

	//m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

}

///////////////////////////
//���W�̎擾
//����:�Ȃ�
//�߂�l:���W
//////////////////////////
DirectX::SimpleMath::Vector3 FixCamera::GetPos()
{
	return m_eye;
}

///////////////////////////
//���W�̐ݒ�
//����:���W
//�߂�l:�Ȃ�
//////////////////////////
void FixCamera::SetPos(DirectX::SimpleMath::Vector3 pos)
{
	m_eye = pos;
}

///////////////////////////
//�����_�̎擾
//����:�Ȃ�
//�߂�l:�����_
//////////////////////////
DirectX::SimpleMath::Vector3 FixCamera::GetTarget()
{
	return m_target;
}

///////////////////////////
//�����_�̐ݒ�
//����:�����_
//�߂�l:�Ȃ�
//////////////////////////
void FixCamera::SetTarget(DirectX::SimpleMath::Vector3 target)
{
	m_target = target;
}

///////////////////////////
//�r���[�s��̎擾
//����:�Ȃ�
//�߂�l:�r���[�s��
//////////////////////////
DirectX::SimpleMath::Matrix FixCamera::GetViewMatrix()
{
	return m_viewMatrix;
}

///////////////////////////
//�ˉe�s��̎擾
//����:�Ȃ�
//�߂�l:�ˉe�s��
//////////////////////////
DirectX::SimpleMath::Matrix FixCamera::GetProjMatrix()
{
	return m_projectionMatrix;
}
