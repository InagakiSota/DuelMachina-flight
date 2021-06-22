#include "pch.h"
#include "FollowCamera.h"

const float FollowCamera::REF_PERCENT = 0.05f;
//�R���X�g���N�^
FollowCamera::FollowCamera()
//:m_viewMatrix{},
//m_projectionMatrix{},
//m_eye{},
//m_target{},
//m_up{}
{
}

//�f�X�g���N�^
FollowCamera::~FollowCamera()
{
}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FollowCamera::Initialize()
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
void FollowCamera::Update()
{
	m_eye += (m_refEye - m_eye) * REF_PERCENT;

	m_target += (m_refTarget - m_target) * REF_PERCENT;

	m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up);

}

///////////////////////////
//���W�̎擾
//����:�Ȃ�
//�߂�l:���W
//////////////////////////
DirectX::SimpleMath::Vector3 FollowCamera::GetPos()
{
	return m_eye;
}

///////////////////////////
//���W�̐ݒ�
//����:���W
//�߂�l:�Ȃ�
//////////////////////////
void FollowCamera::SetPos(const DirectX::SimpleMath::Vector3& pos)
{
	m_eye = pos;
}

///////////////////////////
//�����_�̎擾
//����:�Ȃ�
//�߂�l:�����_
//////////////////////////
DirectX::SimpleMath::Vector3 FollowCamera::GetTarget()
{
	return m_target;
}

///////////////////////////
//�����_�̐ݒ�
//����:�����_
//�߂�l:�Ȃ�
//////////////////////////
void FollowCamera::SetTarget(const DirectX::SimpleMath::Vector3& target)
{
	m_target = target;
}

///////////////////////////
//�r���[�s��̎擾
//����:�Ȃ�
//�߂�l:�r���[�s��
//////////////////////////
DirectX::SimpleMath::Matrix FollowCamera::GetViewMatrix()
{
	return m_viewMatrix;
}

///////////////////////////
//�ˉe�s��̎擾
//����:�Ȃ�
//�߂�l:�ˉe�s��
//////////////////////////
DirectX::SimpleMath::Matrix FollowCamera::GetProjMatrix()
{
	return m_projectionMatrix;
}

///////////////////////////
//�Q�Ǝ��_�̎擾
//����:�Ȃ�
//�߂�l:�Q�Ǝ��_
//////////////////////////
DirectX::SimpleMath::Vector3 FollowCamera::GetRefEyePos()
{
	return m_refEye;
}

///////////////////////////
//�Q�Ǝ��_�̐ݒ�
//����:�Q�Ǝ��_
//�߂�l:�Ȃ�
//////////////////////////
void FollowCamera::SetRefEyePos(const DirectX::SimpleMath::Vector3& refEyePos)
{
	m_refEye = refEyePos;

}

///////////////////////////
//�Q�ƒ����_�̎擾
//����:�Ȃ�
//�߂�l:�Q��
//////////////////////////
DirectX::SimpleMath::Vector3 FollowCamera::GetRefTargetPos()
{
	return m_refTarget;
}

///////////////////////////
//�Q�ƒ����_�̐ݒ�
//����:�Q�ƒ����_
//�߂�l:�Ȃ�
//////////////////////////
void FollowCamera::SetRefTargetPos(const DirectX::SimpleMath::Vector3& refTargetPos)
{
	m_refTarget = refTargetPos;
}
