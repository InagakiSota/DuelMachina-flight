///////////////////////////////////
//�L�����N�^�[2�̑O�ړ���Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��16��
///////////////////////////////////
#include "pch.h"

#include "Character3MoveFrontState.h"
#include "../../CharacterBase.h"
#include "../Character3Params.h"



//�R���X�g���N�^
Character3MoveFrontState::Character3MoveFrontState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character3MoveFrontState::~Character3MoveFrontState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character3MoveFrontState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3MoveFrontState::Update()
{
	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	//�ړ��������ɂ�����ړ�
	if (m_pCharacter->GetPos().x >= -Character3Params::MOVE_LIMIT_X || m_pCharacter->GetPos().x <= Character3Params::MOVE_LIMIT_X)
	{
		//�G���E���ɂ�����E�����Ɉړ�
		if (m_pCharacter->GetFrontVector().x > 0)
		{
			vel.x = Character3Params::GetInstance()->MOVE_FRONT_FORCE;
		}
		//�G�������ɂ����獶�����Ɉړ�
		else if (m_pCharacter->GetFrontVector().x < 0)
		{
			vel.x = -(Character3Params::GetInstance()->MOVE_FRONT_FORCE);
		}
		m_pCharacter->SetVel(vel);
	}

}
