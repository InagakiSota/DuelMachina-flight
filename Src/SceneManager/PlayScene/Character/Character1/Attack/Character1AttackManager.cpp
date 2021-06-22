///////////////////////////////////
//�L�����N�^�[�P�̍U���}�l�[�W���[�N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��13��
///////////////////////////////////

#include "pch.h"
#include "Character1AttackManager.h"
#include "../../CharacterBase.h"
#include "../../CharacterAttackBase.h"

#include "Character1AttackWeakNeutral.h"
#include "Character1AttackWeakSide.h"
#include "Character1AttackWeakBottom.h"
#include "Character1AttackMiddleNeutral.h"
#include "Character1AttackMiddleBottom.h"
#include "Character1AttackMiddleSide.h"


//�R���X�g���N�^
Character1AttackManager::Character1AttackManager()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		m_pCharacterAttackArray[i] = nullptr;
	}
}

//�f�X�g���N�^
Character1AttackManager::~Character1AttackManager()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if(m_pCharacterAttackArray[i] != nullptr)m_pCharacterAttackArray[i].reset();
		m_pCharacterAttackArray[i] = nullptr;
	}
}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackManager::Initialize(CharacterBase * pCharacter)
{
	//��j���[�g����
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] = std::make_unique< Character1AttackWeakNeutral>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)]->Initialize(pCharacter);
	//�㉡
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] = std::make_unique < Character1AttackWeakSide>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)]->Initialize(pCharacter);
	//�㉺
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] = std::make_unique < Character1AttackWeakBottom>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)]->Initialize(pCharacter);
	//���j���[�g�����U��
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] = std::make_unique < Character1AttackMiddleNeutral>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)]->Initialize(pCharacter);
	//�����U��
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] = std::make_unique < Character1AttackMiddleBottom>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)]->Initialize(pCharacter);
	//�����U��
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] = std::make_unique < Character1AttackMiddleSide>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)]->Initialize(pCharacter);

}

///////////////////////////
//�X�V
//����:�U���̓��̓t���O
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackManager::Update()
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
void Character1AttackManager::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//�U���̔z��̕`��
			m_pCharacterAttackArray[i]->Render(view,proj);
		}
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackManager::Finalize()
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
void Character1AttackManager::Reset()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//�U���̔z��̃��Z�b�g�֐�
			m_pCharacterAttackArray[i]->Reset();
		}
	}

}
