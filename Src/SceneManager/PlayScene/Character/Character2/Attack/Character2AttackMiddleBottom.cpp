///////////////////////////////////
//�L�����N�^�[�Q�̒����U��
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��22��
///////////////////////////////////

#include "pch.h"
#include "Character2AttackMiddleBottom.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"
#include "../Character2Params.h"

//�U����
const int Character2AttackMiddleBottom::POWER = 10;
//X���W
const float Character2AttackMiddleBottom::POS_X = 1.0f;
//Y���W
const float Character2AttackMiddleBottom::POS_Y = -1.0f;
//�����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character2AttackMiddleBottom::COLL_SIZE = DirectX::SimpleMath::Vector3(0.6f, 0.5f, 0.3f);
//������܂ł̎���
const float Character2AttackMiddleBottom::VANISH_TIME = 40.0f;
//�v���C���[��X�����̈ړ���(�㏸)
const float Character2AttackMiddleBottom::PLAYER_VEL_X_UP = 0.2f;
//�v���C���[��X�����̈ړ���(���~)
const float Character2AttackMiddleBottom::PLAYER_VEL_X_DOWN = -0.35f;

//�R���X�g���N�^
Character2AttackMiddleBottom::Character2AttackMiddleBottom()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;
}

//�f�X�g���N�^
Character2AttackMiddleBottom::~Character2AttackMiddleBottom()
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
void Character2AttackMiddleBottom::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources();
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackMiddleBottom::Update()
{
	//�L�[���͂��󂯎��
	if (m_pCharacter->GetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)))
	{
		for (int i = 0; i < AttackManager::ATTACK_NUM; i++)
		{
			//�U���̃}�l�[�W���[����g�p����Ă��Ȃ��U���̍\���̂̃|�C���^���󂯎��
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
		m_pAttack->power = Character2AttackMiddleBottom::POWER;
		//�������W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character2AttackMiddleBottom::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y + Character2AttackMiddleBottom::POS_Y,
			m_pCharacter->GetPos().z);
		//�����蔻��̃T�C�Y��ݒ�
		m_pAttack->attackColl.size_h = Character2AttackMiddleBottom::COLL_SIZE;
		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttack->playerID = m_pCharacter->GetPlayerID();

		//�U���g�p���̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), true);
		//�U�����͂̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
		//�U�����̃t���O�̐ݒ�
		m_pCharacter->SetIsAttacking(true);
	}

	if (m_pAttack != nullptr && m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)) == true)
	{
		//�^�C�}�[�����Z
		m_pAttack->timer++;
		//���W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character2AttackMiddleBottom::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y + Character2AttackMiddleBottom::POS_Y,
			m_pCharacter->GetPos().z);
		m_pAttack->attackColl.pos = m_pAttack->pos;

		//�v���C���[�̈ړ��ʂ��擾
		DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

		//�㏸
		if (m_pAttack->timer > 0.0f && m_pAttack->timer < Character2AttackMiddleBottom::VANISH_TIME * 0.5)
		{
			m_pCharacter->SetJumpFlag(true);
			vel.y = Character2AttackMiddleBottom::PLAYER_VEL_X_UP;
		}

		//���~
		else
		{
			vel.y = Character2AttackMiddleBottom::PLAYER_VEL_X_DOWN;
			//if (m_pCharacter->GetLandingFlag() == true)vel.y = 0.0f;

			if (Character2Params::GetInstance()->MOVE_LIMIT_BOTTOM >= m_pCharacter->GetPos().y)
			{
				vel.y = 0.0f;
			}
		}

		//��莞�Ԍo���������
		if (m_pAttack->timer >= Character2AttackMiddleBottom::VANISH_TIME)
		{

			m_pAttack->isUsed = false;
			m_pAttack->timer = 0;
			m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
			m_pCharacter->SetIsAttacking(false);
			vel.x = 0.0f;

		}

		if (m_pAttack->isUsed == false)
		{
			m_pAttack->pos.Zero;
			m_pAttack = nullptr;
			m_pCharacter->SetAttackFront(DirectX::SimpleMath::Vector3::Zero);
		}
		//�v���C���[�̈ړ��ʂ�ݒ�
		m_pCharacter->SetVel(vel);
	}
}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character2AttackMiddleBottom::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
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
void Character2AttackMiddleBottom::Finalize()
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
void Character2AttackMiddleBottom::Reset()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
	m_pCharacter->SetIsAttacking(false);
}
