///////////////////////////////////
//�L�����N�^�[�P�̑҂���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////
#include "pch.h"
#include "Character1WaitState.h"
#include "../../CharacterBase.h"

//�R���X�g���N�^
Character1WaitState::Character1WaitState()
{
	m_pCharacter = nullptr;
}

//�f�X�g���N�^
Character1WaitState::~Character1WaitState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�N���X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character1WaitState::Initialize(CharacterBase * pCharacterBase)
{
	m_pCharacter = pCharacterBase;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1WaitState::Update()
{
	//DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();
	////���̈ړ��ʂ�0�ɂ���
	//vel.x = 0;
	//m_pCharacter->SetVel(vel);

}
