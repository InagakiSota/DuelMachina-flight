///////////////////////////////////
//�L�����N�^�|2�̂��Ⴊ�ݏ�Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#include "pch.h"
#include "Character2SquatState.h"
#include "../../../../../FrameWork/Collision/Collision.h"
#include "../../CharacterBase.h"
#include "../Character2Params.h"

//�̂̓����蔻���Y���W
const float Character2SquatState::BODY_COLL_POS_Y = 1.2f;
//���̓����蔻���Y���W
const float Character2SquatState::HEAD_COLL_POS_Y = 0.5f;

//�R���X�g���N�^
Character2SquatState::Character2SquatState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character2SquatState::~Character2SquatState()
{
	m_pCharacter = nullptr;
}

void Character2SquatState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

void Character2SquatState::Update()
{
	//�̂̓����蔻��
	Collision::BoxCollision bodyCollBox = m_pCharacter->GetBodyCollBox();
	//���̓����蔻��
	Collision::BoxCollision headCollBox = m_pCharacter->GetHeadCollBox();

	//�̂̓����蔻��̃T�C�Y�A���W�̐ݒ�
	bodyCollBox.size_h = Character2Params::BODY_COLL_SIZE_SQUAT;
	bodyCollBox.pos = DirectX::SimpleMath::Vector3(
		m_pCharacter->GetPos().x,
		m_pCharacter->GetPos().y - Character2SquatState::BODY_COLL_POS_Y,
		m_pCharacter->GetPos().z);
	//���̓����蔻��̍��W�̐ݒ�
	headCollBox.pos = DirectX::SimpleMath::Vector3(
		m_pCharacter->GetPos().x,
		m_pCharacter->GetPos().y - Character2SquatState::HEAD_COLL_POS_Y,
		m_pCharacter->GetPos().z);

	m_pCharacter->SetBodyCollBox(bodyCollBox);
	m_pCharacter->SetHeadCollBox(headCollBox);
}
