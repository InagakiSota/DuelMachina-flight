///////////////////////////////////
//�L�����N�^�[�R�̒����U���N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��23��
///////////////////////////////////
#include "pch.h"
#include "Character3AttackMiddleSide.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"

//�U����
const int Character3AttackMiddleSide::POWER = 5;
//�����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character3AttackMiddleSide::COLL_SIZE = DirectX::SimpleMath::Vector3(0.15f, 0.15f, 0.15f);
//������܂ł̎���
const float Character3AttackMiddleSide::VANISH_TIME = 60.0f;
//�W�I���g���v���~�e�B�u�̃T�C�Y
const float Character3AttackMiddleSide::GP_SIZE = 2.0f;

//�R���X�g���N�^
Character3AttackMiddleSide::Character3AttackMiddleSide()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;

	for (int i = 0; i < ARRAY_NUM; i++)
	{
		m_pAttackArray[i] = nullptr;
		m_worldArray[i] = DirectX::SimpleMath::Matrix::Identity;
		m_pBulletGPArray[i] = nullptr;
	}
}

//�f�X�g���N�^
Character3AttackMiddleSide::~Character3AttackMiddleSide()
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
void Character3AttackMiddleSide::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources() ;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleSide::Update()
{
	//�L�[���͂��󂯎��
	if (m_pCharacter->GetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)) == true)
	{
		for (int i = 0; i < AttackManager::ATTACK_NUM; i++)
		{
			if (m_pCharacter->GetAttackManager()->GetAttackStruct(i)->isUsed == false)
			{
				if (m_pAttackArray[0] == nullptr)
				{
					m_pAttackArray[0] = m_pCharacter->GetAttackManager()->GetAttackStruct(i);
					break;
				}
			}

		}

		//�v���C���[�̑O�����̃x�N�g����ۑ�
		m_pCharacter->SetAttackFront(m_pCharacter->GetFrontVector());
		//�g�p����Ă����Ԃɂ���
		m_pAttackArray[0]->isUsed = true;
		//�З͂�ݒ�
		m_pAttackArray[0]->power = Character3AttackMiddleSide::POWER;
		//�������W��ݒ�
		m_pAttackArray[0]->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + 0.5f * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y - 0.2f,
			m_pCharacter->GetPos().z);
		//�����蔻��̃T�C�Y��ݒ�
		m_pAttackArray[0]->attackColl.size_h = DirectX::SimpleMath::Vector3(Character3AttackMiddleSide::COLL_SIZE);
		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttackArray[0]->playerID = m_pCharacter->GetPlayerID();
		//�ړ��ʂ�ݒ�
		m_pAttackArray[0]->vel = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetAttackFront().x * 0.2f, 
			0.2f, 
			0.0f);

		//�e�̃W�I���g���v���~�e�B�u����
		m_pBulletGPArray[0] = DirectX::GeometricPrimitive::CreateSphere(m_pDeviceResources->GetD3DDeviceContext(),
			m_pAttackArray[0]->attackColl.size_h.x * Character3AttackMiddleSide::GP_SIZE);

		//�e���̃W�I���g���v���~�e�B�u�̓ǂݍ���
		for (int i = 0; i < BALLISTIC_NUM; i++)
		{
			//��̂ق��ɂȂ�ɂ�T�C�Y������������
			m_pBallisticGPArray[i] =
				DirectX::GeometricPrimitive::CreateSphere(
					m_pDeviceResources->GetD3DDeviceContext(),
					m_pAttackArray[0]->attackColl.size_h.x * Character3AttackMiddleSide::GP_SIZE * (1 - i * 0.1f));;

			//�e���̍��W�̏����l��������
			m_ballisticPos[i] = m_pAttackArray[0]->pos;
		}

		//�U���g�p���̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), true);
		//�U�����͂̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
		//�U�����̃t���O�̐ݒ�
		m_pCharacter->SetIsAttacking(true);
	}

	//�U���̃|�C���^����ł͂Ȃ����A�U���̎g�p�t���O�������Ă����珈�����X�V�������s��
	if (m_pAttackArray[0] != nullptr &&m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)) == true)
	{
		//�G�̍��W�ւ̃x�N�g�������߂�
		DirectX::SimpleMath::Vector3 toEnemyVec =
			DirectX::SimpleMath::Vector3(
				m_pCharacter->GetEnemyPos().x - m_pAttackArray[0]->pos.x,
				(m_pCharacter->GetEnemyPos().y - 1.5f) - m_pAttackArray[0]->pos.y,
				m_pCharacter->GetEnemyPos().z - m_pAttackArray[0]->pos.z);
		DirectX::SimpleMath::Vector3 addVec = m_pAttackArray[0]->vel;
		//addVec.Normalize();
		//�^�C�}�[�����Z
		m_pAttackArray[0]->timer++;

		if (m_pAttackArray[0]->timer >= 10.0f)
		{
			addVec.y += (toEnemyVec.y * 0.2f);
		}

		if (m_pAttackArray[0]->timer > 0.0f)
		{
			//�ړ��ʂ����W�ɉ��Z
			m_pAttackArray[0]->pos += addVec * 0.6f;
			//���W��ݒ�
			m_pAttackArray[0]->attackColl.pos = m_pAttackArray[0]->pos;
			//���W������W�s��𐶐�
			m_worldArray[0] = DirectX::SimpleMath::Matrix::CreateTranslation(m_pAttackArray[0]->attackColl.pos);

			//�e���̍��W��z��̑O�����ɍX�V(�㏑��)����
			for (int i = BALLISTIC_NUM - 2; i >= 0; --i)
			{
				m_ballisticPos[i + 1] = m_ballisticPos[i];
			}
			//�擪�Ɍ��݂̍U���̍��W��������
			m_ballisticPos[0] = m_pAttackArray[0]->pos;

			//�e���̍��W����s����쐬����
			for (int i = 0;i < BALLISTIC_NUM; i++)
			{
				m_ballisticWorld[i] = DirectX::SimpleMath::Matrix::CreateTranslation(m_ballisticPos[i]);
			}
		}

		//�^�C�}�[����莞�Ԓ����������
		if (m_pAttackArray[0]->timer >= Character3AttackMiddleSide::VANISH_TIME)
		{
			m_pAttackArray[0]->isUsed = false;

			m_pAttackArray[0]->timer = 0;

			//m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] = false;

		}
		//����������e������
		if (m_pAttackArray[0]->isHit == true)
		{
			m_pAttackArray[0]->isUsed = false;
		}

		//���g�p��ԂɂȂ��������
		if (m_pAttackArray[0]->isUsed == false)
		{
			m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
			m_pCharacter->SetIsAttacking(false);
			m_pAttackArray[0]->timer = 0;
			m_pAttackArray[0]->pos.Zero;
			m_pAttackArray[0]->vel.Zero;
			m_pAttackArray[0] = nullptr;
			m_pCharacter->SetAttackFront(DirectX::SimpleMath::Vector3::Zero);
			m_pBulletGPArray[0].reset();
			m_worldArray[0] = DirectX::SimpleMath::Matrix::Identity;

		}

	}

}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleSide::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	if (m_pBulletGPArray[0] != nullptr)
	{
		//�e����z��̌�̕�����`�悷��(�����x�͌�̕��Ȃ�قǏオ���Ă���)
		for (int i = BALLISTIC_NUM - 1; i >= 0; i--)
		{
			m_pBallisticGPArray[i]->Draw(m_ballisticWorld[i], view, proj, DirectX::SimpleMath::Vector4(1, 1, 1, 1.0f - i * 0.1f));
		}

		//�g�p����v���C���[���ƂɐF��ς���
		//�v���C���[�P�p(��)
		if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_1)
			m_pBulletGPArray[0]->Draw(m_worldArray[0], view, proj, DirectX::Colors::Red);
		//�v���C���[�Q�p(��)
		else if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_2)
			m_pBulletGPArray[0]->Draw(m_worldArray[0], view, proj, DirectX::Colors::Blue);
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleSide::Finalize()
{
	if (m_pBulletGPArray[0] != nullptr)
	{
		m_pBulletGPArray[0].reset();
	}
	m_pDeviceResources = nullptr;
}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleSide::Reset()
{
	if (m_pBulletGPArray[0] != nullptr)
	{
		m_pBulletGPArray[0].reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
	m_pCharacter->SetIsAttacking(false);
}
