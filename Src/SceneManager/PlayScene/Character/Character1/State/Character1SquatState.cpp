///////////////////////////////////
//�L�����N�^�|�P�̂��Ⴊ�ݏ�Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#include "pch.h"
#include "Character1SquatState.h"
#include "../../../../../FrameWork/Collision/Collision.h"
#include "../../CharacterBase.h"
#include "../Character1Params.h"

//Y���̊p�x(�}�C�i�X)
const float Character1SquatState::ANGLE_Y_MINUS = 320.0f;
//Y���̊p�x(�v���X)
const float Character1SquatState::ANGLE_Y_PLUS= 130.0f;
//�̂̓����蔻���Y���W
const float Character1SquatState::BODY_COLL_BOX_POS_Y = -0.37f;
//���̓����蔻���Y���W
const float Character1SquatState::HEAD_COLL_BOX_POS_Y = 0.25f;


//�R���X�g���N�^
Character1SquatState::Character1SquatState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character1SquatState::~Character1SquatState()
{
	m_pCharacter = nullptr;
}

void Character1SquatState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

void Character1SquatState::Update()
{
	//Y���̊p�x�̐ݒ�
	if (m_pCharacter->GetFrontVector().x > 0)
	{
		m_pCharacter->SetAngleY(Character1SquatState::ANGLE_Y_PLUS);
	}
	else
	{
		m_pCharacter->SetAngleY(Character1SquatState::ANGLE_Y_MINUS);
	}

	//���W
	DirectX::SimpleMath::Vector3 pos = m_pCharacter->GetPos();

	//�̂̓����蔻��
	Collision::BoxCollision bodyCollBox = m_pCharacter->GetBodyCollBox();
	//���̓����蔻��
	Collision::BoxCollision headCollBox = m_pCharacter->GetHeadCollBox();
	//���̓����蔻��
	//Collision::BoxCollision legCollBox = m_pCharacter->GetLegCollBox();

	//���W�̐ݒ�
	//pos.y = -1.0f;

	//�̂̓����蔻��̃T�C�Y�A���W�̐ݒ�
	bodyCollBox.size_h = Character1Params::BODY_COLL_SIZE_SQUAT;
	bodyCollBox.pos = DirectX::SimpleMath::Vector3(
		m_pCharacter->GetPos().x,
		m_pCharacter->GetPos().y + Character1SquatState::BODY_COLL_BOX_POS_Y,
		m_pCharacter->GetPos().z);

	//���̓����蔻��̍��W�̐ݒ�
	headCollBox.pos = DirectX::SimpleMath::Vector3(
		m_pCharacter->GetPos().x,
		m_pCharacter->GetPos().y + Character1SquatState::HEAD_COLL_BOX_POS_Y,
		m_pCharacter->GetPos().z);

	////�r�̓����蔻��̍��W�̐ݒ�
	//legCollBox.pos = DirectX::SimpleMath::Vector3(
	//	m_pCharacter->GetPos().x,
	//	m_pCharacter->GetPos().y - 0.1f,
	//	m_pCharacter->GetPos().z);


	m_pCharacter->SetPos(pos);

	m_pCharacter->SetBodyCollBox(bodyCollBox);
	m_pCharacter->SetHeadCollBox(headCollBox);
	//m_pCharacter->SetLegCollBox(legCollBox);
}
