///////////////////////////////////
//�L�����N�^�[�P�̂����Ԃ̃N���X
//�쐬�ҁF�Ȃ�
//�쐬���F�Ȃ�
///////////////////////////////////
#include "pch.h"
#include "Character1DamageState.h"
#include "../../CharacterBase.h"
#include "../../CharacterState.h"
#include "../Character1Params.h"


//�X�e�[�g���߂�܂ł̎���
const float Character1DamageState::STATE_BACK_TIME = 3.0f;
//�m�b�N�o�b�N�̈ړ��ʂ̏����l
const float Character1DamageState::KNOCK_BACK_VEL_START = 0.1f;
//�m�b�N�o�b�N�̈ړ���
const float Character1DamageState::KNOCK_BACK_VEL = 0.005f;


//�R���X�g���N�^
Character1DamageState::Character1DamageState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character1DamageState::~Character1DamageState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character1DamageState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1DamageState::Update()
{
	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	m_pCharacter->SetDamageTimer(m_pCharacter->GetDamageTimer() + KNOCK_BACK_VEL_START);

	//�m�b�N�o�b�N�̈ړ��ʂ�ݒ�
	static float knockBackVel = KNOCK_BACK_VEL_START;
	knockBackVel -= Character1DamageState::KNOCK_BACK_VEL;
	if (knockBackVel <= 0.0f)knockBackVel = 0.0f;

	//�m�b�N�o�b�N
	if (m_pCharacter->GetFrontVector().x > 0 && m_pCharacter->GetPos().x > -Character1Params::MOVE_LIMIT_X)
	{
		//�m�b�N�o�b�N�̈ړ��ʂ��v���C���[�̈ړ��ʂɑ��
		vel.x = -knockBackVel;
	}
	else if (m_pCharacter->GetFrontVector().x < 0 && m_pCharacter->GetPos().x <  Character1Params::MOVE_LIMIT_X)
	{
		//�m�b�N�o�b�N�̈ړ��ʂ��v���C���[�̈ړ��ʂɑ��
		vel.x = knockBackVel;
	}
	m_pCharacter->SetVel(vel);

	//���Ԍo�߂ő҂���Ԃɖ߂�
	if (m_pCharacter->GetDamageTimer() >= Character1DamageState::STATE_BACK_TIME)
	{
		m_pCharacter->SetCharaState(eCHARACTER_STATE::WAIT);

		m_pCharacter->SetDamageTimer(0.0f);

		knockBackVel = KNOCK_BACK_VEL_START;
	}

}
