///////////////////////////////////
//�L�����N�^�[�R�̒����U���N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��23��
///////////////////////////////////

#include "pch.h"
#include "Character3AttackMiddleBottom.h"
#include "../../CharacterBase.h"
#include "../../../AttackManager/AttackManager.h"
#include "Src/Cgdi.h"

//X���W
const float Character3AttackMiddleBottom::POS_X = 0.5f;
//������܂ł̎���
const float Character3AttackMiddleBottom::VANISH_TIME = 40.0f;
//�`���[�W�ɗv���鎞��
const float Character3AttackMiddleBottom::CHARAGE_TIME = 10.0f;

//�R���X�g���N�^
Character3AttackMiddleBottom::Character3AttackMiddleBottom()
{
	m_pCharacter = nullptr;
	m_pAttack = nullptr;
	m_pBulletGP = nullptr;
	m_pDeviceResources = nullptr;
	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_isShot = false;
}

//�f�X�g���N�^
Character3AttackMiddleBottom::~Character3AttackMiddleBottom()
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
void Character3AttackMiddleBottom::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
	m_pDeviceResources = gdi->GetDeviceResources();

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleBottom::Update()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	//�U���̓��̓t���O����������
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
		m_pAttack->power = 0;
		//�������W��ݒ�
		m_pAttack->pos = DirectX::SimpleMath::Vector3(
			m_pCharacter->GetPos().x + Character3AttackMiddleBottom::POS_X * m_pCharacter->GetAttackFront().x,
			m_pCharacter->GetHeadCollBox().pos.y,
			m_pCharacter->GetPos().z);

		//�v���C���[��ID��ݒ�(�g�p�҂̃v���C���[ID�Ɠ���)
		m_pAttack->playerID = m_pCharacter->GetPlayerID();

		//�^�C�}�[�̏����l�ݒ�
		m_pAttack->timer = 0.0f;

		//�����蔻��̃T�C�Y������
		m_pAttack->attackColl.size_h = DirectX::SimpleMath::Vector3::Zero;

		//�ړ��ʂ�ݒ�
		m_pAttack->vel = DirectX::SimpleMath::Vector3(
			0.2f * m_pCharacter->GetAttackFront().x,
			0.0f, 
			0.0f);

		//�U���g�p���̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), true);
		//�U�����͂̃t���O�̐ݒ�
		m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
		//�U�����̃t���O�̐ݒ�
		m_pCharacter->SetIsAttacking(true);
	}

	if (m_pAttack != nullptr && m_pCharacter->GetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)) == true)
	{
		//m_pAttack->vel.x = 0.5f * m_frontVector.x;
		//�^�C�}�[�����Z
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) == true && keyState.IsKeyDown(DirectX::Keyboard::Keys::X) == true && m_isShot == false)
		{
			m_pAttack->timer++;
			if (m_pAttack->timer >= Character3AttackMiddleBottom::CHARAGE_TIME)
			{
				m_pAttack->timer = Character3AttackMiddleBottom::CHARAGE_TIME;
			}
			//�������W��ݒ�
			m_pAttack->attackColl.pos = m_pAttack->pos;
			m_pAttack->attackColl.size_h = DirectX::SimpleMath::Vector3::Zero;
			m_pAttack->vel.x = (0.2f + (m_pAttack->timer * 0.03f)) * m_pCharacter->GetAttackFront().x;
			//�e�̃W�I���g���v���~�e�B�u����
			m_pBulletGP = DirectX::GeometricPrimitive::CreateSphere(m_pDeviceResources->GetD3DDeviceContext(), m_pAttack->timer * 0.06f);
			m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pAttack->pos);
			//�U���͂̐ݒ�
			m_pAttack->power = static_cast<int>(m_pAttack->timer);
		}

		else if ((keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) == false || keyState.IsKeyDown(DirectX::Keyboard::Keys::X) == false) && m_isShot == false)
		{
			float timerBuf = m_pAttack->timer;
			m_pAttack->attackColl.size_h = DirectX::SimpleMath::Vector3((timerBuf * 0.06f)*0.5f, (timerBuf * 0.06f)*0.5f, (timerBuf * 0.06f)*0.5f);
			m_isShot = true;
		}

		if (m_isShot == true)
		{
			m_pAttack->timer++;
			//���W��ݒ�
			if (m_pAttack->timer > 0.0f)
			{
				m_pAttack->pos += m_pAttack->vel;
				m_pAttack->attackColl.pos = m_pAttack->pos;
				m_world = DirectX::SimpleMath::Matrix::CreateTranslation(m_pAttack->pos);
			}
			//��莞�Ԓ����������
			if (m_pAttack->timer >= Character3AttackMiddleBottom::VANISH_TIME)
			{
				m_pAttack->isUsed = false;
				m_pAttack->timer = 0;
				m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
				m_pCharacter->SetIsAttacking(false);
			}

			//���g�p��ԂɂȂ��������
			if (m_pAttack->isUsed == false)
			{
				m_isShot = false;
				m_pAttack->pos.Zero;
				m_pAttack->vel.Zero;
				m_pAttack = nullptr;
				m_pCharacter->SetAttackFront(DirectX::SimpleMath::Vector3::Zero);
				m_world = DirectX::SimpleMath::Matrix::Identity;
				m_pBulletGP.reset();
			}
		}

	}
}

///////////////////////////
//�`��
//����:�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void Character3AttackMiddleBottom::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
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
void Character3AttackMiddleBottom::Finalize()
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
void Character3AttackMiddleBottom::Reset()
{
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}

	m_pCharacter->SetIsAttackUse(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
	m_pCharacter->SetIsAttackInput(static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM), false);
	m_pCharacter->SetIsAttacking(false);
}
