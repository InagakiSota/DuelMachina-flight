///////////////////////////////////
//�L�����N�^�[�Q�̍U���}�l�[�W���[�N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��19��
///////////////////////////////////
#include "pch.h"
#include "Character2AttackManager.h"
#include "../../CharacterAttackBase.h"

#include "Character2AttackWeakNeutral.h"
#include "Character2AttackWeakBottom.h"
#include "Character2AttackWeakSide.h"
#include "Character2AttackMiddleNeutral.h"
#include "Character2AttackMiddleSide.h"
#include "Character2AttackMiddleBottom.h"

//�R���X�g���N�^
Character2AttackManager::Character2AttackManager()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		m_pCharacterAttackArray[i] = nullptr;
	}
}

//�f�X�g���N�^
Character2AttackManager::~Character2AttackManager()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)m_pCharacterAttackArray[i].reset();
		m_pCharacterAttackArray[i] = nullptr;
	}

}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^�A�f�o�C�X���\�[�X
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackManager::Initialize(CharacterBase * pCharacter)
{
	//�e�U���̓ǂݍ���
	//��j���[�g����
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] = std::make_unique<Character2AttackWeakNeutral>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)]->Initialize(pCharacter);
	//�㉺
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] = std::make_unique < Character2AttackWeakBottom>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)]->Initialize(pCharacter);
	//�㉡
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] = std::make_unique < Character2AttackWeakSide>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)]->Initialize(pCharacter);
	//���j���[�g����
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] = std::make_unique < Character2AttackMiddleNeutral>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)]->Initialize(pCharacter);
	//����
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] = std::make_unique < Character2AttackMiddleSide>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)]->Initialize(pCharacter);
	//����
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] = std::make_unique < Character2AttackMiddleBottom>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)]->Initialize(pCharacter);

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackManager::Update()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//�U���̔z��̍X�V
			m_pCharacterAttackArray[i]->Update();
		}
	}
}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackManager::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//�U���̔z��̕`��
			m_pCharacterAttackArray[i]->Render(view, proj);
		}
	}

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//�U���̔z��̏I������
			m_pCharacterAttackArray[i]->Finalize();
		}

		m_pCharacterAttackArray[i].reset();
		m_pCharacterAttackArray[i] = nullptr;
	}

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackManager::Reset()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			m_pCharacterAttackArray[i]->Reset();
		}
	}
}
