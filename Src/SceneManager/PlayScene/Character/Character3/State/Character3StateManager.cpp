///////////////////////////////////
//�L�����N�^�[3�̏�ԊǗ��N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��17��
///////////////////////////////////

#include "pch.h"
#include "Character3StateManager.h"

#include "../../CharacterState.h"
#include "../../CharacterBase.h"

#include "Character3BoostMoveState.h"
#include "Character3MoveFrontState.h"
#include "Character3MoveBackState.h"
#include "Character3SquatState.h"
#include "Character3JumpState.h"
#include "Character3DamageState.h"
#include "Character3WaitState.h"

//�R���X�g���N�^
Character3StateManager::Character3StateManager()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		m_pCharacterStateArray[i] = nullptr;
	}
}

//�f�X�g���N�^
Character3StateManager::~Character3StateManager()
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
void Character3StateManager::Initialize(CharacterBase * pCharacterBase)
{
	//�u�[�X�g�ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::BOOST_MOVE)] = 
		std::make_unique<Character3BoostMoveState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::BOOST_MOVE)]->Initialize(pCharacterBase);

	//�O�ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_FRONT)] = 
		std::make_unique<Character3MoveFrontState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_FRONT)]->Initialize(pCharacterBase);

	//��ړ���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_BACK)] = 
		std::make_unique<Character3MoveBackState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::MOVE_BACK)]->Initialize(pCharacterBase);

	//���Ⴊ�ݏ�Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::SQUAT)] = 
		std::make_unique<Character3SquatState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::SQUAT)]->Initialize(pCharacterBase);

	//�W�����v��Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::JUMP)] = 
		std::make_unique<Character3JumpState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::JUMP)]->Initialize(pCharacterBase);

	//�����Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::DAMAGE)] = 
		std::make_unique<Character3DamageState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::DAMAGE)]->Initialize(pCharacterBase);

	//�҂���Ԃ̓ǂݍ���
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::WAIT)] =
		std::make_unique<Character3WaitState>();
	m_pCharacterStateArray[static_cast<int>(eCHARACTER_STATE::WAIT)]->Initialize(pCharacterBase);

}

///////////////////////////
//�X�V
//����:�L�����N�^�[�̏��
//�߂�l:�Ȃ�
//////////////////////////
void Character3StateManager::Update(const eCHARACTER_STATE& charaState)
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
void Character3StateManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(eCHARACTER_STATE::MAX_NUM); i++)
	{
		m_pCharacterStateArray[i].reset();
	}
}
