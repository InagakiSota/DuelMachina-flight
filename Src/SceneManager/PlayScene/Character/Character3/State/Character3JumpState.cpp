///////////////////////////////////
//�L�����N�^�|2�̃W�����v��Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��22��
///////////////////////////////////
#include "pch.h"
#include "Character3JumpState.h"
#include "../../CharacterBase.h"
#include "../Character3Params.h"

//�R���X�g���N�^
Character3JumpState::Character3JumpState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character3JumpState::~Character3JumpState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character3JumpState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3JumpState::Update()
{
	if (m_pCharacter->GetJumpFlag() == false && m_pCharacter->GetLandingFlag() == true)
	{
		//�L�����N�^�[�̈ړ��ʂ�ۑ�
		DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

		//�W�����v�t���O��true�ɂ���
		m_pCharacter->SetJumpFlag(true);
		//�ڒn�t���O��false�ɂ���
		m_pCharacter->SetLandingFlag(false);

		//������Ɉړ��ʂ�^����
		vel.y = Character3Params::GetInstance()->JUMP_FORCE;
		m_pCharacter->SetVel(vel);
	}

}
