///////////////////////////////////
//�L�����N�^�|�P�̃W�����v��Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////
#include "pch.h"
#include "Character1JumpState.h"
#include "../../CharacterBase.h"
#include "../Character1Params.h"


//�R���X�g���N�^
Character1JumpState::Character1JumpState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character1JumpState::~Character1JumpState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character1JumpState::Initialize(CharacterBase* pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1JumpState::Update()
{
	if (m_pCharacter->GetJumpFlag() == false)
	{
		//�L�����N�^�[�̈ړ��ʂ�ۑ�
		DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

		//�W�����v�t���O��true�ɂ���
		m_pCharacter->SetJumpFlag(true);
		//�ڒn�t���O��false�ɂ���
		//m_pCharacter->SetLandingFlag(false);

		//������Ɉړ��ʂ�^����
		vel.y = Character1Params::GetInstance()->JUMP_FORCE;
		m_pCharacter->SetVel(vel);
	}

}
