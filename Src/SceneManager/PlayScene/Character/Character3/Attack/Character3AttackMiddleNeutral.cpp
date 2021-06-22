///////////////////////////////////
//�L�����N�^�[�R�̒��j���[�g�����U���N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��23��
///////////////////////////////////

#include "pch.h"
#include "Character3AttackMiddleNeutral.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"
//�U����
const int Character3AttackMiddleNeutral::POWER = 5;
//X���W
const float Character3AttackMiddleNeutral::POS_X = 0.5f;
//Y���W
const float Character3AttackMiddleNeutral::POS_Y = -0.3f;
//X�����̈ړ���
const float Character3AttackMiddleNeutral::VEL_X = 0.2f;
//Y�����̈ړ���
const float Character3AttackMiddleNeutral::VEL_Y = -0.02f;
//������܂ł̎���
const float Character3AttackMiddleNeutral::VANISH_TIME = 30.0f;
//�W�I���g���v���~�e�B�u�̃T�C�Y
const float Character3AttackMiddleNeutral::GP_SIZE = 2.0f;
//�����蔻��̃T�C�Y
const DirectX::SimpleMath::Vector3 Character3AttackMiddleNeutral::COLL_SIZE = DirectX::SimpleMath::Vector3(0.15f, 0.15f, 0.5f);

//�R���X�g���N�^
Character3AttackMiddleNeutral::Character3AttackMiddleNeutral()
{
	//�ϐ��̏�����
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;

}

//�f�X�g���N�^
Character3AttackMiddleNeutral::~Character3AttackMiddleNeutral()
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
void Character3AttackMiddleNeutral::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources();

	for (int i = 0; i < BALLISTIC_NUM;i++)
	{
		m_pBallisticGPArray[i] = nullptr;
		m_ballisticPos[i] = DirectX::SimpleMath::Vector3::Zero;
		m_ballisticWorld[i] = DirectX::SimpleMath::Matrix::Identity;
	}


}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleNeutral::Update()
{
	//�U���̓��̓t���O����������
	if (m_pCharacter->GetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)))
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
		m_pAttack->power = Character3AttackMiddleNeutral::POWER;
		//�������W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character3AttackMiddleNeutral::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetPos().y + Character3AttackMiddleNeutral::POS_Y,
			m_pCharacter->GetPos().z);
		//�����蔻��̃T�C�Y��ݒ�
		m_pAttack->attackColl.size_h = DirectX::SimpleMath::Vector3(COLL_SIZE);
		//�e�̃W�I���g���v���~�e�B�u����
		m_pBulletGP = DirectX::GeometricPrimitive::CreateSphere(m_pDeviceResources->GetD3DDeviceContext(), m_pAttack->attackColl.size_h.x * Character3AttackMiddleNeutral::GP_SIZE);
		//�e���̃W�I���g���v���~�e�B�u�̓ǂݍ���
		for (int i = 0; i < BALLISTIC_NUM; i++)
		{
			//��̂ق��ɂȂ�ɂ�T�C�Y������������
			m_pBallisticGPArray[i] = 
				DirectX::GeometricPrimitive::CreateSphere(
					m_pDeviceResources->GetD3DDeviceContext(), 
					m_pAttack->attackColl.size_h.x * Character3AttackMiddleNeutral::GP_SIZE * (1- i*0.1f));;
		
			//�e���̍��W�̏����l��������
			m_ballisticPos[i] = m_pAttack->pos;
		}

		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttack->playerID = m_pCharacter->GetPlayerID();

		//�^�C�}�[�̏����l�ݒ�
		m_pAttack->timer = 0.0f;

		//�ړ��ʂ�ݒ�
		m_pAttack->vel = DirectX::SimpleMath::Vector3(
			Character3AttackMiddleNeutral::VEL_X * m_pCharacter->GetAttackFront().x,
			Character3AttackMiddleNeutral::VEL_X,
			0.0f);

		//�U���g�p���̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), true);
		//�U�����͂̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);
		//�U�����̃t���O�̐ݒ�
		m_pCharacter->SetIsAttacking(true);
	}

	//�U���̃|�C���^����ł͂Ȃ����A�U���̎g�p�t���O�������Ă����珈�����X�V�������s��
	if (m_pAttack != nullptr &&m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)) == true)
	{
		//�^�C�}�[�����Z
		m_pAttack->timer++;

		//���W��ݒ�
		if (m_pAttack->timer > 0.0f)
		{
			//Y�ړ��ʂ�^����
			m_pAttack->vel.y += Character3AttackMiddleNeutral::VEL_Y;
			//�ړ��ʂ����W�ə�����
			m_pAttack->pos += m_pAttack->vel;
			//�����蔻��ƍ��W�𓯊�������
			m_pAttack->attackColl.pos = m_pAttack->pos;
			//���[���h�s��ɍ��W�s���������
			m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pAttack->pos);

			//�e���̍��W��z��̑O�����ɍX�V(�㏑��)����
			for (int i = BALLISTIC_NUM - 2; i >= 0; --i)
			{
				m_ballisticPos[i + 1] = m_ballisticPos[i];
			}
			//�擪�Ɍ��݂̍U���̍��W��������
			m_ballisticPos[0] = m_pAttack->pos;

			//�e���̍��W����s����쐬����
			for (int i = 0;i < BALLISTIC_NUM; i++)
			{
				m_ballisticWorld[i] = DirectX::SimpleMath::Matrix::CreateTranslation(m_ballisticPos[i]);
			}
		}
		//��莞�Ԓ����������
		if (m_pAttack->timer >= Character3AttackMiddleNeutral::VANISH_TIME)
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
			m_pAttack->vel.Zero;
			m_pAttack = nullptr;
			m_pCharacter->SetAttackFront(DirectX::SimpleMath::Vector3::Zero);
			m_world = DirectX::SimpleMath::Matrix::Identity;
			m_pBulletGP.reset();

			for (int i = 0; i < BALLISTIC_NUM; i++)
			{
				m_pBallisticGPArray[i].reset();
				m_ballisticPos[i] = DirectX::SimpleMath::Vector3::Zero;
				m_ballisticWorld[i] = DirectX::SimpleMath::Matrix::Identity;
			}
		}
	}
}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleNeutral::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	if (m_pBulletGP != nullptr)
	{
		//�e����z��̌�̕�����`�悷��(�����x�͌�̕��Ȃ�قǏオ���Ă���)
		for (int i = BALLISTIC_NUM - 1; i >= 0; i--)
		{
			m_pBallisticGPArray[i]->Draw(m_ballisticWorld[i], view, proj, DirectX::SimpleMath::Vector4( 1, 1, 1, 1.0f- i *0.1f));
		}

		//�g�p����v���C���[���ƂɐF��ς���
		//�v���C���[�P�p(��)
		if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_1)
			m_pBulletGP->Draw(m_world, view, proj, DirectX::Colors::Red);
		//�v���C���[�Q�p(��)
		else if (m_pCharacter->GetPlayerID() == ePLAYER_ID::PLAYER_2)
			m_pBulletGP->Draw(m_world, view, proj, DirectX::Colors::Blue);

	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleNeutral::Finalize()
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
void Character3AttackMiddleNeutral::Reset()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL), false);
	m_pCharacter->SetIsAttacking(false);
}
