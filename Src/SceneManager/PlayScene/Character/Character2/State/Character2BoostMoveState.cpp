///////////////////////////////////
//�L�����N�^�[�P�̃u�[�X�g�ړ���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��16��
///////////////////////////////////
#include "pch.h"
#include "Character2BoostMoveState.h"
#include "Keyboard.h"
#include "../../CharacterBase.h"
#include "../../CharacterState.h"
#include "../Character2Params.h"
#include "../../ChracterAnimationNumber.h"

//�R���X�g���N�^
Character2BoostMoveState::Character2BoostMoveState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character2BoostMoveState::~Character2BoostMoveState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character2BoostMoveState::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2BoostMoveState::Update()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	//�̂̓����蔻��
	Collision::BoxCollision bodyColl = m_pCharacter->GetBodyCollBox();
	bodyColl.size_h = Character2Params::GetInstance()->MOVE_BOOST_BODY_SIZE;
	bodyColl.pos = DirectX::SimpleMath::Vector3(m_pCharacter->GetPos().x, m_pCharacter->GetPos().y - 0.5f, m_pCharacter->GetPos().z);
	m_pCharacter->SetBodyCollBox(bodyColl);

	//�u�[�X�g�e�ʂ����炷
	int boostCap = m_pCharacter->GetBoostCap();
	boostCap--;
	m_pCharacter->SetBoostCap(boostCap);

	//�u�[�X�g�e�ʂ�0�ȉ��ɂȂ�����0���
	if (m_pCharacter->GetBoostCap() <= 0)
	{
		m_pCharacter->SetBoostCap(0);
	}

	//�����
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) && m_pCharacter->GetPos().y < Character2Params::MOVE_LIMIT_TOP)
	{
		vel.y = 1;
		//�A�j���[�V�����̐؂�ւ�
		m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
	}
	//������
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) && m_pCharacter->GetPos().y > Character2Params::MOVE_LIMIT_BOTTOM)
	{
		vel.y = -1;
		//�A�j���[�V�����̐؂�ւ�
		m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
	}
	else vel.y = 0.0f;
	//�E����
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) && m_pCharacter->GetPos().x < Character2Params::MOVE_LIMIT_X)
	{
		vel.x = 1;
		//�A�j���[�V�����̐؂�ւ�
		if (m_pCharacter->GetFrontVector().x > 0)
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
		}
		else
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
		}

	}
	//������
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) && m_pCharacter->GetPos().x > -Character2Params::MOVE_LIMIT_X)
	{
		vel.x = -1;
		//�A�j���[�V�����̐؂�ւ�
		if (m_pCharacter->GetFrontVector().x > 0)
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
		}
		else
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
		}

	}
	else vel.x = 0.0f;


	//�ړ��ʂ𐳋K��
	vel.Normalize();

	m_pCharacter->SetVel(vel * Character2Params::GetInstance()->MOVE_BOOST_FORCE);

	//�X�y�[�X�L�[��������u�[�X�g�e�ʂ�0�ɂȂ����猳�̃X�e�[�g�ɖ߂�
	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::Space) || m_pCharacter->GetBoostCap() <= 0)
	{
		m_pCharacter->SetCharaState(eCHARACTER_STATE::WAIT);
	}
}

