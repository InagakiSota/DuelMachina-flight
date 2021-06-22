///////////////////////////////////
//�����U��
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��17��
///////////////////////////////////
#include "pch.h"
#include "Character1AttackMiddleSide.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"

//�U����
 const int Character1AttackMiddleSide::POWER = 8;
//X���W
 const float Character1AttackMiddleSide::POS_X = 0.5f;
//Y���W
 const float Character1AttackMiddleSide::POS_Y = 0.9f;
//X�����̈ړ���
 const float Character1AttackMiddleSide::VEL_X = 0.2f;
//Y�����̈ړ���
 const float Character1AttackMiddleSide::VEL_Y = -0.01f;
//������܂ł̎���
 const float Character1AttackMiddleSide::VANISH_TIME = 30.0f;
//�W�I���g���v���~�e�B�u�̃T�C�Y
 const int Character1AttackMiddleSide::GP_SIZE = 2;
//�����蔻��̃T�C�Y
 const DirectX::SimpleMath::Vector3 Character1AttackMiddleSide::COLL_SIZE = DirectX::SimpleMath::Vector3(0.2f, 0.2f, 0.2f);

//�R���X�g���N�^
Character1AttackMiddleSide::Character1AttackMiddleSide()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_pDeviceResources = nullptr;

}

//�f�X�g���N�^
Character1AttackMiddleSide::~Character1AttackMiddleSide()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_pDeviceResources = nullptr;

}

///////////////////////////
//������
//����:�L�����N�^�[�̃|�C���^�A�f�o�C�X���\�[�X
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleSide::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources();
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleSide::Update()
{
	//�U���̓��̓t���O����������
	if (m_pCharacter->GetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)) == true)
	{
		//�U���̃}�l�[�W���[����g�p����Ă��Ȃ��U���̍\���̂̃|�C���^���󂯎��
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
		m_pAttack->power = Character1AttackMiddleSide::POWER;
		//�������W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character1AttackMiddleSide::POS_X * m_pCharacter->GetAttackFront().x, 
			m_pCharacter->GetPos().y + Character1AttackMiddleSide::POS_Y,
			m_pCharacter->GetPos().z);
		//�����蔻��̃T�C�Y��ݒ�
		m_pAttack->attackColl.size_h = DirectX::SimpleMath::Vector3(0.2f, 0.2f, 0.2f);
		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttack->playerID = m_pCharacter->GetPlayerID();

		//�^�C�}�[�̏����l�ݒ�
		m_pAttack->timer = 0.0f;

		//�e��ǂݍ���
		m_pBulletGP = DirectX::GeometricPrimitive::CreateSphere(
			m_pDeviceResources->GetD3DDeviceContext(), m_pAttack->attackColl.size_h.x * Character1AttackMiddleSide::GP_SIZE);

		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), true);
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);

		m_pCharacter->SetIsAttacking(true);


		//�ړ��ʂ�ݒ�
		m_pAttack->vel = DirectX::SimpleMath::Vector3(
			Character1AttackMiddleSide::VEL_X * m_pCharacter->GetAttackFront().x, 
			Character1AttackMiddleSide::VEL_Y,
			0.0f);
	}

	if (m_pAttack != nullptr &&	m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE))== true)
	{
		//m_pAttack->vel.x = 0.5f * m_frontVector.x;
		//�^�C�}�[�����Z
		m_pAttack->timer++;
		//���W��ݒ�
		if (m_pAttack->timer > 0.0f)
		{
			m_pAttack->pos += m_pAttack->vel;
			m_pAttack->attackColl.pos = m_pAttack->pos;
			//���W��e�̃��[���h�s��ɕϊ�
			m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pAttack->pos);

		}
		//��莞�Ԓ����������
		if (m_pAttack->timer >= Character1AttackMiddleSide::VANISH_TIME)
		{
			m_pAttack->isUsed = false;

			m_pAttack->timer = 0;

			m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
		
			m_pCharacter->SetIsAttacking(false);
		}

		//���g�p��ԂɂȂ��������
		if (m_pAttack->isUsed == false)
		{
			m_pAttack->pos.Zero;
			m_pAttack = nullptr;
			m_pCharacter->SetAttackFront(DirectX::SimpleMath::Vector3::Zero);
			m_pBulletGP.reset();

		}
	}

}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleSide::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	if (m_pBulletGP != nullptr)
	{
		if(m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_1)
			m_pBulletGP->Draw(m_world, view, proj,DirectX::Colors::Red);
		else if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_2)
			m_pBulletGP->Draw(m_world, view, proj, DirectX::Colors::Blue);
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1AttackMiddleSide::Finalize()
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
void Character1AttackMiddleSide::Reset()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE), false);
	m_pCharacter->SetIsAttacking(false);
}
