///////////////////////////////////
//�L�����N�^�[�R�̎㉺�U���N���X
//�쐬�ҁFGS305_��_�D��2020�N11��23��
//�쐬���F
///////////////////////////////////

#include "pch.h"
#include "Character3AttackWeakBottom.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"

//�U����
const int Character3AttackWeakBottom::POWER = 5;
//X���W
const float Character3AttackWeakBottom::POS_X = 1.2f;
//Y���W
const float Character3AttackWeakBottom::POS_Y = -2.0f;
//�����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character3AttackWeakBottom::COLL_SIZE = DirectX::SimpleMath::Vector3(0.4f, 0.2f, 0.5f);
//������܂ł̎���
const float Character3AttackWeakBottom::VANISH_TIME = 10.0f;

//�R���X�g���N�^
Character3AttackWeakBottom::Character3AttackWeakBottom()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;
}

//�f�X�g���N�^
Character3AttackWeakBottom::~Character3AttackWeakBottom()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^�A�f�o�C�X���\�[�X
//�߂�l:
//////////////////////////
void Character3AttackWeakBottom::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources();
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackWeakBottom::Update()
{
	//�U�����̓t���O����������
	if (m_pCharacter->GetIsAttackInput(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)) == true)
	{
		for (int i = 0; i < AttackManager::ATTACK_NUM; i++)
		{
			if (m_pCharacter->GetAttackManager()->GetAttackStruct(i)->isUsed == false)
			{
				if (m_pAttack == nullptr)
				{
					m_pAttack = m_pCharacter->GetAttackManager()->GetAttackStruct(i);
					break;
				}
			}
		}
		//�v���C���[�̑O�����̃x�N�g����ۑ�
		m_pCharacter->SetAttackFront(m_pCharacter->GetFrontVector());
		//�g�p����Ă����Ԃɂ���
		m_pAttack->isUsed = true;
		//�З͂�ݒ�
		m_pAttack->power = Character3AttackWeakBottom::POWER;
		//�������W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character3AttackWeakBottom::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y + Character3AttackWeakBottom::POS_Y,
			m_pCharacter->GetPos().z);
		//�����蔻��̃T�C�Y��ݒ�
		m_pAttack->attackColl.size_h = Character3AttackWeakBottom::COLL_SIZE;
		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttack->playerID = m_pCharacter->GetPlayerID();

		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM), true);
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM), false);

		//�U�����̃t���O�̐ݒ�
		m_pCharacter->SetIsAttacking(true);
	}

	if (m_pAttack != nullptr&& m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)) == true)
	{
		//m_pAttack->vel.x = 0.5f * m_frontVector.x;

		//���W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character3AttackWeakBottom::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y + Character3AttackWeakBottom::POS_Y,
			m_pCharacter->GetPos().z);
		m_pAttack->attackColl.pos = m_pAttack->pos;

		//�^�C�}�[�����Z
		m_pAttack->timer++;

		//��莞�Ԍo���������
		if (m_pAttack->timer >= Character3AttackWeakBottom::VANISH_TIME)
		{
			m_pAttack->isUsed = false;
			m_pAttack->timer = 0;
			m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM), false);
			m_pCharacter->SetIsAttacking(false);

		}

		if (m_pAttack->isUsed == false)
		{
			m_pAttack->pos.Zero;
			m_pAttack = nullptr;
			m_pCharacter->SetAttackFront(DirectX::SimpleMath::Vector3::Zero);
		}
	}
}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackWeakBottom::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	if (m_pBulletGP != nullptr)
	{
		if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_1)
			m_pBulletGP->Draw(m_world, view, proj, DirectX::Colors::Red);
		else if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_2)
			m_pBulletGP->Draw(m_world, view, proj, DirectX::Colors::Blue);
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackWeakBottom::Finalize()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}
	m_pDeviceResources = nullptr;
}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackWeakBottom::Reset()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM), false);
	m_pCharacter->SetIsAttacking(false);
}
