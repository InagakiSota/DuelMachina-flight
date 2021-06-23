///////////////////////////////////
//�L�����N�^�[2�̏�ԊǗ��N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��17��
///////////////////////////////////

#include "pch.h"
#include "Character2StateManager.h"

#include "../../CharacterState.h"
#include "../../CharacterBase.h"

#include "Character2BoostMoveState.h"
#include "Character2MoveFrontState.h"
#include "Character2MoveBackState.h"
#include "Character2SquatState.h"
#include "Character2JumpState.h"
#include "Character2DamageState.h"
#include "Character2WaitState.h"

//�R���X�g���N�^
Character2StateManager::Character2StateManager()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		m_pCharacterStateArray[i] = nullptr;
	}
}

//�f�X�g���N�^
Character2StateManager::~Character2StateManager()
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
void Character2StateManager::Initialize(CharacterBase * pCharacterBase)
{
	//�u�[�X�g�ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::BOOST_MOVE)] = 
		std::make_unique<Character2BoostMoveState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::BOOST_MOVE)]->Initialize(pCharacterBase);

	//�O�ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_FRONT)] = 
		std::make_unique<Character2MoveFrontState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_FRONT)]->Initialize(pCharacterBase);

	//��ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_BACK)] = 
		std::make_unique<Character2MoveBackState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_BACK)]->Initialize(pCharacterBase);

	//���Ⴊ�ݏ�Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::SQUAT)] = 
		std::make_unique<Character2SquatState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::SQUAT)]->Initialize(pCharacterBase);

	//�W�����v��Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::JUMP)] = 
		std::make_unique<Character2JumpState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::JUMP)]->Initialize(pCharacterBase);

	//�����Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::DAMAGE)] = 
		std::make_unique<Character2DamageState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::DAMAGE)]->Initialize(pCharacterBase);

	//�҂���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::WAIT)] = 
		std::make_unique<Character2WaitState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::WAIT)]->Initialize(pCharacterBase);

}

///////////////////////////
//�X�V
//����:�L�����N�^�[�̏��
//�߂�l:�Ȃ�
//////////////////////////
void Character2StateManager::Update(const eCHARACTER_STATE& charaState)
{
	//�X�e�[�g���ƂɍX�V��������
	if (charaState != eCHARACTER_STATE::GUARD &&
		charaState != eCHARACTER_STATE::LOSE &&
		charaState != eCHARACTER_STATE::WIN &&
		charaState != eCHARACTER_STATE::MOVE)
		m_pCharacterStateArray[static_cast<int>(charaState)]->Update();
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2StateManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		m_pCharacterStateArray[i].reset();
	}
}
