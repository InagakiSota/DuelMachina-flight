#pragma once
#include "SimpleMath.h"


class FollowCamera
{
public:
	FollowCamera();
	~FollowCamera();


	//������
	void Initialize();

	//�X�V
	void Update();

	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetPos();

	//���W�̐ݒ�
	void SetPos(const DirectX::SimpleMath::Vector3& pos);

	//�����_�̎擾
	DirectX::SimpleMath::Vector3 GetTarget();

	//�����_�̐ݒ�
	void SetTarget(const DirectX::SimpleMath::Vector3& target);

	//�r���[�s��̎擾
	DirectX::SimpleMath::Matrix GetViewMatrix();

	//�ˉe�s��̎擾
	DirectX::SimpleMath::Matrix GetProjMatrix();

	//�Q�Ǝ��_�̎擾
	DirectX::SimpleMath::Vector3 GetRefEyePos();

	//�Q�Ǝ��_�̐ݒ�
	void SetRefEyePos(const DirectX::SimpleMath::Vector3& refEyePos);

	//�Q�ƒ����_�̎擾
	DirectX::SimpleMath::Vector3 GetRefTargetPos();

	//�Q�ƒ����_�̐ݒ�
	void SetRefTargetPos(const DirectX::SimpleMath::Vector3& refTargetPos);

	//�Ǐ]�x
	static const float REF_PERCENT;

private:
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_viewMatrix;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projectionMatrix;

	//���W
	DirectX::SimpleMath::Vector3 m_eye;
	//�����_
	DirectX::SimpleMath::Vector3 m_target;
	//������x�N�g��
	DirectX::SimpleMath::Vector3 m_up;

	// �Q�Ǝ��_
	DirectX::SimpleMath::Vector3 m_refEye;

	// �Q�ƒ����_
	DirectX::SimpleMath::Vector3 m_refTarget;

};

