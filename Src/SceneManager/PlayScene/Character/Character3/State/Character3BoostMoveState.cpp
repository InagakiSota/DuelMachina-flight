///////////////////////////////////
//�L�����N�^�[�P�̃u�[�X�g�ړ���Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��16��
///////////////////////////////////
#include "pch.h"
#include "Character3BoostMoveState.h"
#include "Keyboard.h"
#include "../../CharacterBase.h"
#include "../../CharacterState.h"
#include "../Character3Params.h"

//�R���X�g���N�^
Character3BoostMoveState::Character3BoostMoveState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character3BoostMoveState::~Character3BoostMoveState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character3BoostMoveState::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3BoostMoveState::Update()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	//�u�[�X�g�e�ʂ����炷
	int boostCap = m_pCharacter->GetBoostCap();
	boostCap--;
	m_pCharacter->SetBoostCap(boostCap);

	//�u�[�X�g�e�ʂ�0�ȉ��ɂȂ�����0���
	if (m_pCharacter->GetBoostCap() <= 0)
	{
		m_pCharacter->SetBoostCap(0);
	}

	//�E����
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) && m_pCharacter->GetPos().x <Character3Params::MOVE_LIMIT_X)
	{
		vel.x = Character3Params::GetInstance()->MOVE_BOOST_FORCE;
	}
	//������
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) && m_pCharacter->GetPos().x > -Character3Params::MOVE_LIMIT_X)
	{
		vel.x = -Character3Params::GetInstance()->MOVE_BOOST_FORCE;
	}
	else vel.x = 0.0f;

	m_pCharacter->SetVel(vel);

	//�X�y�[�X�L�[��������u�[�X�g�e�ʂ�0�ɂȂ����猳�̃X�e�[�g�ɖ߂�
	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::Space) || m_pCharacter->GetBoostCap() <= 0)
	{
		m_pCharacter->SetCharaState(eCHARACTER_STATE::WAIT);
	}
}
