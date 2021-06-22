///////////////////////////////////
//�L�����N�^�[2�̑O�ړ���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��16��
///////////////////////////////////
#include "pch.h"

#include "Character2MoveFrontState.h"
#include "../../CharacterBase.h"
#include "../Character2Params.h"


//�R���X�g���N�^
Character2MoveFrontState::Character2MoveFrontState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character2MoveFrontState::~Character2MoveFrontState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character2MoveFrontState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2MoveFrontState::Update()
{
	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	//�ړ��������ɂ�����ړ�
	if (m_pCharacter->GetPos().x >= -Character2Params::MOVE_LIMIT_X || m_pCharacter->GetPos().x <= Character2Params::MOVE_LIMIT_X && m_pCharacter->GetLandingFlag() == true)
	{
		//�G���E���ɂ�����E�����Ɉړ�
		if (m_pCharacter->GetFrontVector().x > 0)
		{
			vel.x = Character2Params::GetInstance()->MOVE_FRONT_FORCE;
		}
		//�G�������ɂ����獶�����Ɉړ�
		else if (m_pCharacter->GetFrontVector().x < 0)
		{
			vel.x = -(Character2Params::GetInstance()->MOVE_FRONT_FORCE);
		}
		m_pCharacter->SetVel(vel);
	}

}
