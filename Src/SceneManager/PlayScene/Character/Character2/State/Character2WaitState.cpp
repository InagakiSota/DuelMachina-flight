///////////////////////////////////
//�L�����N�^�[2�̑҂���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////
#include "pch.h"
#include "Character2WaitState.h"
#include "../../CharacterBase.h"

//�R���X�g���N�^
Character2WaitState::Character2WaitState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character2WaitState::~Character2WaitState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character2WaitState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2WaitState::Update()
{
	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();
	//���̈ړ��ʂ�0�ɂ���
	vel.x = 0;
	m_pCharacter->SetVel(vel);

}