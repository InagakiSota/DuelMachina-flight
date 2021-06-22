///////////////////////////////////
//�G�t�F�N�g�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��20��
///////////////////////////////////
#pragma once

#include "StepTimer.h"
#include <SimpleMath.h>

class MyEffect
{
public:

	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity);
	void Update(DX::StepTimer timer);

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	DirectX::SimpleMath::Vector3 GetVelocity() { return m_velocity; }
private:

	DX::StepTimer                           m_timer;


	DirectX::SimpleMath::Vector3		m_gravity;
	DirectX::SimpleMath::Vector3		m_position;
	DirectX::SimpleMath::Vector3		m_velocity;
	float								m_life;

	DirectX::SimpleMath::Vector3		m_startPosition;
	DirectX::SimpleMath::Vector3		m_startVelocity;
	float								m_startLife;

};