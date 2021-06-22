///////////////////////////////////
//�L�����N�^�[�P�̏�ԊǗ��N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��17��
///////////////////////////////////

#include "pch.h"
#include "Character1StateManager.h"

#include "../../CharacterBase.h"

#include "Character1BoostMoveState.h"
#include "Character1MoveFrontState.h"
#include "Character1MoveBackState.h"
#include "Character1SquatState.h"
#include "Character1JumpState.h"
#include "Character1DamageState.h"
#include "Character1WaitState.h"

//�R���X�g���N�^
Character1StateManager::Character1StateManager()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		m_pCharacterStateArray[i] = nullptr;
	}
}

//�f�X�g���N�^
Character1StateManager::~Character1StateManager()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		if (m_pCharacterStateArray[i] != nullptr)
		{
			m_pCharacterStateArray[i].reset();
		}
	}

}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character1StateManager::Initialize(CharacterBase * pCharacterBase)
{
	//�u�[�X�g�ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::BOOST_MOVE)] = 
		std::make_unique<Character1BoostMoveState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::BOOST_MOVE)]->Initialize(pCharacterBase);

	//�O�ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_FRONT)] = 
		std::make_unique<Character1MoveFrontState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_FRONT)]->Initialize(pCharacterBase);

	//��ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_BACK)] = 
		std::make_unique<Character1MoveBackState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_BACK)]->Initialize(pCharacterBase);

	//���Ⴊ�ݏ�Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::SQUAT)] = 
		std::make_unique<Character1SquatState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::SQUAT)]->Initialize(pCharacterBase);

	//�W�����v��Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::JUMP)] = 
		std::make_unique<Character1JumpState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::JUMP)]->Initialize(pCharacterBase);

	//�����Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::DAMAGE)] = 
		std::make_unique<Character1DamageState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::DAMAGE)]->Initialize(pCharacterBase);

	//�҂���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::WAIT)] = 
		std::make_unique<Character1WaitState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::WAIT)]->Initialize(pCharacterBase);

}

///////////////////////////
//�X�V
//����:�L�����N�^�[�̏��
//�߂�l:�Ȃ�
//////////////////////////
void Character1StateManager::Update(const eCHARACTER_STATE& charaState)
{
	//�X�e�[�g���ƂɍX�V��������
	if(charaState != eCHARACTER_STATE::GUARD &&
		charaState != eCHARACTER_STATE::LOSE && 
		charaState != eCHARACTER_STATE::WIN)
		m_pCharacterStateArray[static_cast<int>(charaState)]->Update();
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1StateManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		m_pCharacterStateArray[i].reset();
	}
}
