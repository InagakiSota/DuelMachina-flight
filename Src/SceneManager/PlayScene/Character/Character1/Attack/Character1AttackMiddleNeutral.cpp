///////////////////////////////////
//�L�����N�^�[�P�̒��j���[�g�����U��
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��17��
///////////////////////////////////
#include "pch.h"
#include "Character1AttackMiddleNeutral.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"

//�U����
const int Character1AttackMiddleNeutral::POWER = 10;
//�����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character1AttackMiddleNeutral::COLL_SIZE = DirectX::SimpleMath::Vector3(0.5f, 0.2f, 0.5f);
//X���W
const float Character1AttackMiddleNeutral::POS_X = 0.7f;
//������܂ł̎���
const float Character1AttackMiddleNeutral::VANISH_TIME = 20.0f;

//�R���X�g���N�^
Character1AttackMiddleNeutral::Character1AttackMiddleNeutral()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;
}

//�f�X�g���N�^
Character1AttackMiddleNeutral::~Character1AttackMiddleNeutral()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^�A�f�o�C�X���\�[�X
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleNeutral::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources();
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleNeutral::Update()
{
	//�L�[���͂��󂯎��
	if (m_pCharacter->GetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)) == true)
	{
		for (int i = 0; i < AttackManager::ATTACK_NUM; i++)
		{
			if (m_pCharacter->GetAttackManager()->GetAttackStruct(i)->isUsed == false)
			{
				if (m_pAttack == nullptr)
				{
					m_pAttack =m_pCharacter->GetAttackManager()->GetAttackStruct(i);
					break;
				}
			}

		}
		//�v���C���[�̑O�����̃x�N�g����ۑ�
		m_pCharacter->SetAttackFront(m_pCharacter->GetFrontVector());
		//�g�p����Ă����Ԃɂ���
		m_pAttack->isUsed = true;
		//�З͂�ݒ�
		m_pAttack->power = Character1AttackMiddleNeutral::POWER;
		//�������W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character1AttackMiddleNeutral::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y,
			m_pCharacter->GetPos().z);
		//�����蔻��̃T�C�Y��ݒ�
		m_pAttack->attackColl.size_h = Character1AttackMiddleNeutral::COLL_SIZE;
		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttack->playerID = m_pCharacter->GetPlayerID();


		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), true);
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);

		m_pCharacter->SetIsAttacking(true);

	}

	if (m_pAttack != nullptr && m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)) == true)
	{
		//�^�C�}�[�����Z
		m_pAttack->timer++;

		//���W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character1AttackMiddleNeutral::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y,
			m_pCharacter->GetPos().z);
		m_pAttack->attackColl.pos = m_pAttack->pos;


		//��莞�Ԓ����������
		if (m_pAttack->timer >= Character1AttackMiddleNeutral::VANISH_TIME)
		{
			m_pAttack->isUsed = false;

			m_pAttack->timer = 0;

			m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);
			m_pCharacter->SetIsAttacking(false);

		}

		//���g�p��ԂɂȂ��������
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
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleNeutral::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
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
void Character1AttackMiddleNeutral::Finalize()
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
void Character1AttackMiddleNeutral::Reset()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);
	m_pCharacter->SetIsAttacking(false);
}
