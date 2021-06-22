#pragma once
#include "SimpleMath.h"

class FixCamera
{
public:
	FixCamera();
	~FixCamera();

	//������
	void Initialize();

	//�X�V
	void Update();

	//���W�̎擾
	DirectX::SimpleMath::Vector3 GetPos();

	//���W�̐ݒ�
	void SetPos(DirectX::SimpleMath::Vector3 pos);

	//�����_�̎擾
	DirectX::SimpleMath::Vector3 GetTarget();

	//�����_�̐ݒ�
	void SetTarget(DirectX::SimpleMath::Vector3 target);

	//�r���[�s��̎擾
	DirectX::SimpleMath::Matrix GetViewMatrix();

	//�ˉe�s��̎擾
	DirectX::SimpleMath::Matrix GetProjMatrix();

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


};

