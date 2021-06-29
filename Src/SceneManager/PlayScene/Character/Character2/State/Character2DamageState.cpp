///////////////////////////////////
//�L�����N�^�[2�̂����Ԃ̃N���X
//�쐬�ҁF�Ȃ�
//�쐬���F�Ȃ�
///////////////////////////////////
#include "pch.h"
#include "Character2DamageState.h"
#include "../../CharacterBase.h"
#include "../../CharacterState.h"
#include "../Character2Params.h"

//�X�e�[�g���߂�܂ł̎���
const float Character2DamageState::STATE_BACK_TIME = 5.0f;
//�m�b�N�o�b�N�̈ړ��ʂ̏����l
const float Character2DamageState::KNOCK_BACK_VEL_START = 0.1f;
//�m�b�N�o�b�N�̈ړ���
const float Character2DamageState::KNOCK_BACK_VEL = 0.005f;


//�R���X�g���N�^
Character2DamageState::Character2DamageState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character2DamageState::~Character2DamageState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character2DamageState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2DamageState::Update()
{
	m_pCharacter->SetVel(DirectX::SimpleMath::Vector3::Zero);
	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	m_pCharacter->SetDamageTimer(m_pCharacter->GetDamageTimer() + KNOCK_BACK_VEL_START);

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	static float knockBackVel = KNOCK_BACK_VEL_START;
	knockBackVel -= Character2DamageState::KNOCK_BACK_VEL;
	if (knockBackVel <= 0.0f)knockBackVel = 0.0f;
	//�m�b�N�o�b�N
	if (m_pCharacter->GetFrontVector().x > 0 && m_pCharacter->GetPos().x > -Character2Params::MOVE_LIMIT_X)
	{
		//�m�b�N�o�b�N�̈ړ��ʂ��v���C���[�̈ړ��ʂɑ��
		vel.x = -knockBackVel;
	}
	else if (m_pCharacter->GetFrontVector().x < 0 && m_pCharacter->GetPos().x < Character2Params::MOVE_LIMIT_X)
	{
		//�m�b�N�o�b�N�̈ړ��ʂ��v���C���[�̈ړ��ʂɑ��
		vel.x = knockBackVel;
	}
	m_pCharacter->SetVel(vel);

	//���Ԍo�߂ő҂���Ԃɖ߂�
	if (m_pCharacter->GetDamageTimer() >= Character2DamageState::STATE_BACK_TIME)
	{
		m_pCharacter->SetCharaState(eCHARACTER_STATE::WAIT);

		m_pCharacter->SetDamageTimer(0.0f);

		knockBackVel = KNOCK_BACK_VEL_START;
		//m_vel.x = 0;
	}

}
