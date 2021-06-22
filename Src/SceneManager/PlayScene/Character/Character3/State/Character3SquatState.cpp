///////////////////////////////////
//�L�����N�^�|2�̂��Ⴊ�ݏ�Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#include "pch.h"
#include "Character3SquatState.h"
#include "../../../../../FrameWork/Collision/Collision.h"
#include "../../CharacterBase.h"
#include "../Character3Params.h"

//�R���X�g���N�^
Character3SquatState::Character3SquatState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character3SquatState::~Character3SquatState()
{
	m_pCharacter = nullptr;
}

void Character3SquatState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

void Character3SquatState::Update()
{
	//�̂̓����蔻��
	Collision::BoxCollision bodyCollBox = m_pCharacter->GetBodyCollBox();
	//���̓����蔻��
	Collision::BoxCollision headCollBox = m_pCharacter->GetHeadCollBox();

	//�̂̓����蔻��̃T�C�Y�A���W�̐ݒ�
	bodyCollBox.size_h = Character3Params::BODY_COLL_SIZE_SQUAT;
	bodyCollBox.pos = DirectX::SimpleMath::Vector3(m_pCharacter->GetPos().x, m_pCharacter->GetPos().y - 1.7f, m_pCharacter->GetPos().z);
	//���̓����蔻��̍��W�̐ݒ�
	headCollBox.pos = DirectX::SimpleMath::Vector3(m_pCharacter->GetPos().x, m_pCharacter->GetPos().y - 1.1f, m_pCharacter->GetPos().z);

	m_pCharacter->SetBodyCollBox(bodyCollBox);
	m_pCharacter->SetHeadCollBox(headCollBox);
}
