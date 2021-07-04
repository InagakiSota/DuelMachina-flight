#include "pch.h"
#include "CharacterBase.h"

#include "../../PlayerID.h"
#include "Src/FrameWork/FbxResourceManager/FbxResourceManager.h"
#include "../Character/CharacterID.h"
#include "Src/Cgdi.h"
#include "Character1/State/Character1StateManager.h"
#include "Character1/Attack/Character1AttackManager.h"
#include "Character2/State/Character2StateManager.h"
#include "Character2/Attack/Character2AttackManager.h"
#include "Character3/State/Character3StateManager.h"
#include "Character3/Attack/Character3AttackManager.h"
#include "Src/FrameWork/FbxModel/FbxModel.h"
#include "ChracterAnimationNumber.h"
#include "Adx2.h"
#include "CueSheet_0.h"
#include "../AttackManager/AttackManager.h"

//�d��
const float CharacterBase::GRAVITY = -0.007;
//�ړ�����
const float CharacterBase::MOVE_LIMIT_X = 3.0f;
//�J�����̍��W
 const DirectX::SimpleMath::Vector3 CharacterBase::CAMERA_POS = DirectX::SimpleMath::Vector3(0.00f,0.0f,6.0f);

//�R���X�g���N�^
CharacterBase::CharacterBase(ePLAYER_ID playerID)
	: m_jumpFlag(false),
	m_legBoxWorld(DirectX::SimpleMath::Matrix::Identity),
	m_legCollBox{},
	m_pLegBox(nullptr),
	m_pModel(nullptr),
	m_pos{},
	m_vel{},
	m_frontVector{},
	m_pBodyBox(nullptr),
	m_bodyBoxWorld(DirectX::SimpleMath::Matrix::Identity),
	m_bodyCollBox{},
	m_startPos{},
	m_pKeyTracker(nullptr),
	m_playerID(playerID),
	m_isHitEnemyBody(false),
	m_posBuf{},
	m_pAttack(nullptr),
	m_pAttackManager(nullptr),
	m_enemyPos{},
	m_pHeadBox(nullptr),
	m_headCollBox{},
	m_headBoxWorld{},
	m_hp(0),
	m_hpBuffer(0),
	m_charaState(eCHARACTER_STATE::WAIT),
	m_damageTimer( 0.0f),
	m_angleY(0.0f),
	m_aiAttackTimer(0.0f),
	m_aiStateTiemer(0.0f),
	m_aiState(0),
	m_boostCap(0),
	m_pStateManager(nullptr),
	m_pCharacterAttackManager(nullptr),
	m_attackFront{},
	m_isAttacking(false),
	m_pHitEffectManager(nullptr),
	m_pEnemy(nullptr),
	m_characterID(eCHARACTER_ID::NONE),
	m_pPlayScene(nullptr)
{
}

CharacterBase::~CharacterBase()
{
	////���\�[�X�̉��
	//if (m_pBodyBox != nullptr)
	//{
	//	m_pBodyBox.reset();
	//}

	//if (m_pLegBox != nullptr)
	//{
	//	m_pLegBox.reset();
	//}

	//if (m_pHeadBox != nullptr)
	//{
	//	m_pHeadBox.reset();
	//}


	//if (m_pKeyTracker != nullptr)
	//{
	//	m_pKeyTracker.reset();
	//}

	if (m_pFbxModel != nullptr)
	{
		m_pFbxModel = nullptr;
	}

	if (m_pPlayScene != nullptr)m_pPlayScene = nullptr;
}

//////////////////////////
//������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::Initialize()
{
	//�L�[�g���b�J�[�̓ǂݍ���
	m_pKeyTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	//�V�[���h�̃��f���̓ǂݍ���
	m_pShieldModel = FbxResourceManager::GetInstance()->GetShieldModel();
	//�V�[���h�̃��f���̃��[���h�s���������
	m_shieldWorld = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix pos = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Zero);
	m_shieldWorld = pos;

	//�������W�̐ݒ�	
	m_pos = m_startPos;

	//�L�����̃X�e�[�g������
	m_charaState = eCHARACTER_STATE::WAIT;

	//�U���t���O�̏�����
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		m_isAttackUse[i] = false;
		m_isAttackInput[i] = false;
	}

	//�U���̓����蔻��̏�����
	m_pAttack = nullptr;

	//�L�����N�^�[���Ƃɓǂݍ��ރ}�l�[�W���[��ς���
	switch (m_characterID)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{	
			//�X�e�[�g�}�l�[�W���[�̓ǂݍ���
			m_pStateManager = std::make_unique<Character1StateManager>();
			//�U���}�l�[�W���[�̓ǂݍ���
			m_pCharacterAttackManager = std::make_unique<Character1AttackManager>();
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			//�X�e�[�g�}�l�[�W���[�̓ǂݍ���
			m_pStateManager = std::make_unique<Character2StateManager>();
			//�U���}�l�[�W���[�̓ǂݍ���
			m_pCharacterAttackManager = std::make_unique<Character2AttackManager>();
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			//�X�e�[�g�}�l�[�W���[�̓ǂݍ���
			m_pStateManager = std::make_unique<Character3StateManager>();
			//�U���}�l�[�W���[�̓ǂݍ���
			m_pCharacterAttackManager = std::make_unique<Character3AttackManager>();
			break;
		}
		default:
			break;
	}
	//�X�e�[�g�}�l�[�W���[�̓ǂݍ��݁A������
	m_pStateManager->Initialize(this);
	//�U���}�l�[�W���[�̓ǂݍ��݁A������
	m_pCharacterAttackManager->Initialize(this);

	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̓ǂݍ��݁A�쐬
	m_pHitEffectManager = std::make_unique<HitEffectManager>();
	m_pHitEffectManager->Create(gdi->GetDeviceResources(), 50);

	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̓ǂݍ��݁A�쐬
	m_pBoostEffectManager = std::make_unique<BoostEffectManager>();
	m_pBoostEffectManager->Initialize(gdi->GetDeviceResources(), 1, 1, DirectX::SimpleMath::Vector3::Zero);

	//�e�̃��[���h�s��̏�����
	m_bulletWorld = DirectX::SimpleMath::Matrix::Identity;

}

//////////////////////////
//�X�V
//�����F�^�C�}�[
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::Update(DX::StepTimer const& timer)
{
	m_stepTimer = timer;
	//�L�[�{�[�h�̏�Ԃ̎擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_pKeyTracker->Update(keyState);

	//�X�e�[�g�̊Ǘ�
	if (m_playerID == ePLAYER_ID::PLAYER_1 && m_hp > 0)
	{
		StateManager();
	}

	//�v���C���[�Q�Ȃ�AI����
	if (m_playerID == ePLAYER_ID::PLAYER_2 && m_hp > 0)
	{
		AI(timer);
	}

	//�ړ�����
	//if (m_pos.x > -MOVE_LIMIT_X || m_pos.x < MOVE_LIMIT_X)m_vel.x = 0.0f;
	//if (m_pos.x < -MOVE_LIMIT_X) m_pos.x = -MOVE_LIMIT_X;
	//if (m_pos.x > MOVE_LIMIT_X) m_pos.x = MOVE_LIMIT_X;

	//�L�����̃X�e�[�g�X�V
	m_pStateManager->Update(m_charaState);

	//�K�[�h��Ԃ��U�����Ȃ�ړ��ʂ�0�ɂ���
	if (m_charaState == eCHARACTER_STATE::GUARD||
		m_isAttacking == true)m_vel = DirectX::SimpleMath::Vector3::Zero;

	//��]�s����쐬
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));

	//�U��
	if (m_hp > 0)
	{
		Attack();
	}
	//�U���Ƃ̓����蔻��
	HitAttack();
	//�U���}�l�[�W���[�̍X�V
	m_pCharacterAttackManager->Update();
	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	m_pHitEffectManager->Update(timer);

	//�o�b�t�@�ɍ��W���i�[
	m_posBuf = m_pos;
	//�ړ��ʂ����W�ɉ��Z
	m_pos += m_vel;

	//�̗͂̍X�V
	if (m_hp > m_hpBuffer)m_hp--;

	m_legBoxWorld = DirectX::SimpleMath::Matrix::CreateTranslation(m_legCollBox.pos);
	m_bodyBoxWorld = DirectX::SimpleMath::Matrix::CreateTranslation(m_bodyCollBox.pos);
	m_headBoxWorld = DirectX::SimpleMath::Matrix::CreateTranslation(m_headCollBox.pos);
}

//////////////////////////
//�`��
//�����F�r���[�s��A�ˉe�s��
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//�K�[�h��Ԃ̃��f���̕`��
	if (m_charaState == eCHARACTER_STATE::GUARD)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::GUARD));

	}
	//���Ⴊ�ݏ�Ԃ̃��f���̕`��
	else if (m_charaState == eCHARACTER_STATE::SQUAT
		&& m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] == false
		&& m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] == false)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::SQUAT));
	}
	//�u�[�X�g�ړ���Ԃ̃��f���̕`��
	else if (m_charaState == eCHARACTER_STATE::BOOST_MOVE)
	{
		//m_pBoostEffectManager->SetRenderState(view, proj);
		m_pBoostEffectManager->Render(view, proj);
	}

	//�O�ړ���Ԃ̃��f���̕`��
	else if (m_charaState == eCHARACTER_STATE::MOVE_FRONT
		&& m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] == false
		&& m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] == false)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_FRONT));

	}

	//��ړ���Ԃ̃��f���̕`��
	else if (m_charaState == eCHARACTER_STATE::MOVE_BACK)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
	}

	//�W�����v��Ԃ̃��f���̕`��
	else if (m_charaState == eCHARACTER_STATE::JUMP)
	{
		//m_pFbxModel_Jump->Draw(m_world,view,proj);
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::JUMP));
	}

	//����
	else if (m_charaState == eCHARACTER_STATE::DAMAGE)
	{
		//m_pFbxModel_Damage->Draw(m_world, view, proj);
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::DAMAGE));
	}

	//��j���[�g�����U���̕`��
	else if (m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)])
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::ATTACK_WEAK_NEUTRAL));

	}

	//�㉺�U���̕`��
	else if (m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)])
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::ATTACK_WEAK_BOTTOM));

	}

	//�㉡�U���̕`��
	else if (m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)])
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::ATTACK_WEKA_SIDE));

	}

	//���j���[�g�����U���̕`��
	else if (m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)])
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::ATTACK_MIDDLE_NEUTRAL));

	}

	//�����U���̕`��
	else if (m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)])
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::ATTACK_MIDDLE_BOTTOM));

	}

	//�����U���̕`��
	else if (m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)])
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::ATTACK_MIDDLE_SIDE));

	}

	//����
	else if (m_charaState == eCHARACTER_STATE::WIN)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::WIN_POSE));
	}

	//�s�k
	else if (m_charaState == eCHARACTER_STATE::LOSE)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::LOSE_POSE));

	}

	//�ҋ@��Ԃ̃��f���̕`��
	else if(m_charaState == eCHARACTER_STATE::WAIT)
	{
		m_pFbxModel->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::WAIT));
	}


	if (m_playerID == ePLAYER_ID::PLAYER_1)
		m_pFbxModel->Draw(m_world, view, proj, DirectX::SimpleMath::Vector4(0.7f, 0.0f, 0.0f, 1.0f));
	else if (m_playerID == ePLAYER_ID::PLAYER_2)
		m_pFbxModel->Draw(m_world, view, proj, DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.7f, 1.0f));


	if (m_charaState == eCHARACTER_STATE::GUARD)
	{
		//�V�[���h�̕`��
		if (m_playerID == ePLAYER_ID::PLAYER_1)
			m_pShieldModel->Draw(m_shieldWorld, view, proj, DirectX::SimpleMath::Vector4(1.0f, 0.0f, 0.0f, 0.3f));
		else if (m_playerID == ePLAYER_ID::PLAYER_2)
			m_pShieldModel->Draw(m_shieldWorld, view, proj, DirectX::SimpleMath::Vector4(0.0f, 0.0f, 1.0f, 0.3f));
	}


	//�U���}�l�[�W���[�̕`��
	m_pCharacterAttackManager->Render(view, proj);
	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̕`��
	m_pHitEffectManager->SetRenderState(CAMERA_POS, view, proj);
	m_pHitEffectManager->Render();

}

//////////////////////////
//�I������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::Finalize()
{
	m_pFbxModel = nullptr;

	//delete m_pShieldModel;
	m_pShieldModel = nullptr;


	//�W�I���g���v���~�e�B�u�̉��
	m_pLegBox.reset();

	//delete m_pDeviceResources;

	//�X�e�[�g�}�l�[�W���[�̏I������
	m_pStateManager->Finalize();
	m_pStateManager.reset();
	m_pStateManager = nullptr;

	//�U���}�l�[�W���̏I������
	m_pCharacterAttackManager->Finalize();
	m_pCharacterAttackManager.reset();
	m_pCharacterAttackManager = nullptr;

	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̏I������
	m_pHitEffectManager->Finalize();
	m_pHitEffectManager.reset();
	m_pHitEffectManager = nullptr;

	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̏I������
	m_pBoostEffectManager->Finalize();
	m_pBoostEffectManager.reset();
	m_pBoostEffectManager = nullptr;
	m_pEnemy = nullptr;
}



//////////////////////////
//���Ƃ̓����蔻��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::HitFloor(const Collision::BoxCollision& floorColl)
{
	//if (Collision::CheckHitBox2Box(m_legCollBox, floorColl))
	//{
	//	//Y�����̈ړ��ʂ�0�ɂ���
	//	m_vel.y = 0.0f;

	//	//���n�t���O�𗧂Ă�
	//	m_landingFlag = true;
	//	//m_pos.y += 0.0001f;
	//	m_jumpFlag = false;
	//	//�W�����v��ԂȂ�҂���Ԃɂ���
	//	if (m_charaState == eCHARACTER_STATE::JUMP)
	//	{
	//		m_charaState = eCHARACTER_STATE::WAIT;
	//	}
	//	
	//	//���n������J������U��������
	//	if (m_pPlayScene != nullptr)
	//	{
	//		if(m_landingFlag == true && m_landingFlagBuf == false)
	//			m_pPlayScene->CameraShake(0.5f, 0.1f);
	//	}

	//	//���n�t���O�̃o�b�t�@�̓���
	//	m_landingFlagBuf = m_landingFlag;
	//}
	//else
	//{
	//	m_landingFlag = false;
	//	//���n�t���O�̃o�b�t�@�̓���
	//	m_landingFlagBuf = m_landingFlag;

	//}

}

//////////////////////////
//�G�Ƃ̓����蔻��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::HitEnemyBody(const Collision::BoxCollision& enemyBodyColl, const Collision::BoxCollision& enemyHeadColl)
{
	//�̂Ƒ̂̓����蔻��
	if (Collision::CheckHitBox2Box(m_bodyCollBox, enemyBodyColl))
	{
		//�O�t���[���̍��W�ɖ߂�
		//if (m_landingFlag == true)
		{
			m_pos = m_posBuf;
		}
		//else if (m_jumpFlag == true)
		//{
		//	m_pos.x = m_posBuf.x;
		//}
	}

	//�̂Ɠ��̓����蔻��(�ォ��������)
	if (Collision::CheckHitBox2Box(m_bodyCollBox, enemyHeadColl))
	{
		//���n�t���O�𗧂Ă�
		//m_landingFlag = true;
		//�ҋ@��Ԃɂ���
		m_charaState = eCHARACTER_STATE::WAIT;
		//Y�����̈ړ��ʂ�0�ɂ���
		m_vel.y = 0.0f;
		//�G���E�[�ɂ����玩�g�������Ɉړ�������
		if (enemyHeadColl.pos.x > 2.0f || m_bodyCollBox.pos.x > 2.0f)
		{
			m_pos.x -= 0.25f;
		}
		//�G�����[�ɂ����玩�g���E���Ɉړ�������
		else if (enemyHeadColl.pos.x < -2.0f || m_bodyCollBox.pos.x < -2.0f)
		{
			m_pos.x += 0.25f;
		}
		//�G�̍����ɏ�����玩�g�������Ɉړ�������
		if (m_bodyCollBox.pos.x < enemyHeadColl.pos.x)
		{
			m_pos.x -= 0.15f;
		}
		//�G�̉E���ɏ�����玩�g���E���Ɉړ�������
		else if (m_bodyCollBox.pos.x > enemyHeadColl.pos.x)
		{
			m_pos.x += 0.15f;

		}

	}
}

//////////////////////////
//�U���Ƃ̓����蔻��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
//////////////////////////
void CharacterBase::HitAttack()
{
	//�L�[�̏�Ԏ擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	for (int i = 0; i < AttackManager::ATTACK_NUM; i++)
	{
		//�g�p����Ă��Ȃ���΃X���[
		if (m_pAttackManager->GetAttackStruct(i)->isUsed == false)continue;
		//�U���̃v���C���[ID��������ID�ƈ�v���Ă���΃X���[
		if (m_pAttackManager->GetAttackStruct(i)->playerID == m_playerID)continue;

		if (Collision::CheckHitBox2Box(m_bodyCollBox, m_pAttackManager->GetAttackStruct(i)->attackColl) && m_pAttackManager->GetAttackStruct(i)->isHit == false)
		{
			//�K�[�h�Ȃ��œ������������
			if (m_charaState != eCHARACTER_STATE::GUARD)
			{
				//�̗͂����炷
				m_hpBuffer = m_hp - m_pAttackManager->GetAttackStruct(i)->power;

				//�����Ԃɐ؂�ւ���
				m_charaState = eCHARACTER_STATE::DAMAGE;

				//���������t���O�𗧂Ă�
				m_pAttackManager->GetAttackStruct(i)->isHit = true;

				//�q�b�g�G�t�F�N�g�̍Đ�
				m_pHitEffectManager->Play(40.0f, m_pos);

				//�q�b�g���̍Đ�
				static int id;
				id = ADX2::GetInstance().Play(CRI_CUESHEET_0_DAMAGE);

				//�U���͂�5���傫����΃q�b�g�X�g�b�v
				if (m_pAttackManager->GetAttackStruct(i)->power > 5)
				{
					Sleep(150);
				}
			}

			//�K�[�h���ɍU��������������_���[�W�ʂ����炷
			else if (m_charaState == eCHARACTER_STATE::GUARD)
			{
				//�̗͂����炷
				m_hpBuffer = m_hp - (m_pAttackManager->GetAttackStruct(i)->power / m_pAttackManager->GetAttackStruct(i)->power);

				//���������t���O�𗧂Ă�
				m_pAttackManager->GetAttackStruct(i)->isHit = true;
				//�q�b�g�G�t�F�N�g�̍Đ�
				m_pHitEffectManager->Play(10.0f, m_pos);


			}
		}
	}

}

///////////////////////////
//����
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::Ready(DX::StepTimer const& timer)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_pKeyTracker->Update(keyState);

	//�X�e�[�g�̊Ǘ�
	if (m_hp > 0)StateManager();


	//�L�����̃X�e�[�g�X�V
	m_pStateManager->Update(m_charaState);


	//�o�b�t�@�ɍ��W���i�[
	m_posBuf = m_pos;
	//�ړ��ʂ����W�ɉ��Z
	m_pos += m_vel;

	//�U���}�l�[�W���[�̍X�V
	m_pCharacterAttackManager->Update();
	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	m_pHitEffectManager->Update(timer);


}

///////////////////////////
//�s�k
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::Lose(DX::StepTimer const& timer)
{
	//X�����̈ړ��ʂ�0�ɂ���
	m_vel.x = 0.0f;
	//�X�e�[�g�𕉂���Ԃɂ���
	m_charaState = eCHARACTER_STATE::LOSE;

	//�o�b�t�@�ɍ��W���i�[
	m_posBuf = m_pos;
	//�ړ��ʂ����W�ɉ��Z
	m_pos += m_vel;

	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	m_pHitEffectManager->Update(timer);

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::Reset()
{
	//�������W�̐ݒ�
	m_pos = m_startPos;
	m_posBuf = m_pos;
	//�̗͂̐ݒ�
	m_hp = m_hpMax;
	m_hpBuffer = m_hp;
	//�X�e�[�g�̐ݒ�
	m_charaState = eCHARACTER_STATE::WAIT;

	m_pAttack = nullptr;

	//�U���̓����蔻��̏�����
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		m_isAttackInput[i] = false;
		m_isAttackUse[i] = false;
	}

	//�e�̃W�I���g���v���~�e�B�u�̃��Z�b�g
	if (m_pBulletGP != nullptr)
	{
		m_pBulletGP.reset();
	}
	//�U���}�l�[�W���[�̃��Z�b�g
	m_pCharacterAttackManager->Reset();
	//�q�b�g�G�t�F�N�g�̃��Z�b�g
	m_pHitEffectManager->Reset();
}

///////////////////////////
//�A�j���[�V�����̐؂�ւ�
//����:�؂�ւ���A�j���[�V�����̔ԍ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::ChangeAnimation(const int& animationStack)
{
	//���f���̃A�j���[�V������؂�ւ���
	m_pFbxModel->ChangeAnimation(animationStack);

}

///////////////////////////
//�X�e�[�g�̊Ǘ�
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::StateManager()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//�v���C���[�P�̏���
	if (m_playerID == ePLAYER_ID::PLAYER_1)
	{
		//�����ԂłȂ���Ίe��Ԃ̏���������
		if (m_charaState != eCHARACTER_STATE::DAMAGE)
		{
			//���͖����őҋ@���
			if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Space) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::X) != true &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Z) != true)
			{
				m_charaState = eCHARACTER_STATE::WAIT;
			}

			if ((keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) == true ||
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) == true ||
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) == true ||
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) == true) &&
				m_charaState != eCHARACTER_STATE::GUARD)
			{
				m_charaState = eCHARACTER_STATE::MOVE;
			}

			//��Shift�ŃK�[�h
			if ((m_charaState == eCHARACTER_STATE::WAIT ||
				m_charaState == eCHARACTER_STATE::MOVE) &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::LeftShift))
			{
				m_charaState = eCHARACTER_STATE::GUARD;
			}

			//�X�y�[�X�L�[���͂��u�[�X�g�e�ʂ�����΃u�[�X�g�ړ�
			if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Space) && m_boostCap > 0)
			{
				m_charaState = eCHARACTER_STATE::BOOST_MOVE;
			}


			//�҂���Ԃɉ����͂ł��Ⴊ��
			if (m_charaState == eCHARACTER_STATE::WAIT && keyState.IsKeyDown(DirectX::Keyboard::Keys::Down))
			{
				//m_charaState = eCHARACTER_STATE::SQUAT;
			}

			//�҂���Ԃō��E���͂ňړ�
			if (((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) && m_frontVector.x > 0 &&
				m_charaState != eCHARACTER_STATE::SQUAT &&
				m_charaState != eCHARACTER_STATE::GUARD &&
				m_isAttacking == false) ||
				((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
					keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) && m_frontVector.x < 0 &&
					m_charaState != eCHARACTER_STATE::SQUAT && m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttacking == false))
			{
				//�O�ړ�
				//m_charaState = eCHARACTER_STATE::MOVE_FRONT;
			}
			if (((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) && m_frontVector.x > 0 &&
				m_charaState != eCHARACTER_STATE::SQUAT &&
				m_charaState != eCHARACTER_STATE::GUARD &&
				m_isAttacking == false) ||
				((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
					keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) && m_frontVector.x < 0 &&
					m_charaState != eCHARACTER_STATE::SQUAT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttacking == false))
			{
				//��ړ�
				//m_charaState = eCHARACTER_STATE::MOVE_BACK;
			}
			//����͂ŏ�ړ�
			//if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::Up) &&
			//	m_charaState != eCHARACTER_STATE::SQUAT &&
			//	m_charaState != eCHARACTER_STATE::BOOST_MOVE)
			//{
			//	m_charaState = eCHARACTER_STATE::JUMP;
			//}
		}
	}

	//else if (m_playerID == ePLAYER_ID::PLAYER_2)
	//{
	//	//�����ԂłȂ���Ίe��Ԃ̏���������
	//	if (m_charaState != eCHARACTER_STATE::DAMAGE)
	//	{
	//		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::W) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::A) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::S) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::D) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::LeftShift) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::Space) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::X) != true &&
	//			m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::Z) != true)
	//		{
	//			m_charaState = eCHARACTER_STATE::WAIT;
	//		}

	//		//�҂���Ԃɉ����͂ł��Ⴊ��
	//		if (m_charaState == eCHARACTER_STATE::WAIT && keyState.IsKeyDown(DirectX::Keyboard::Keys::S))
	//		{
	//			m_charaState = eCHARACTER_STATE::SQUAT;
	//		}

	//		//�҂���Ԃō��E���͂ňړ�
	//		if (((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
	//			keyState.IsKeyDown(DirectX::Keyboard::Keys::D) && m_frontVector.x > 0 &&
	//			m_charaState != eCHARACTER_STATE::SQUAT && m_charaState != eCHARACTER_STATE::GUARD) ||
	//			((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
	//				keyState.IsKeyDown(DirectX::Keyboard::Keys::A) && m_frontVector.x < 0 &&
	//				m_charaState != eCHARACTER_STATE::SQUAT && m_charaState != eCHARACTER_STATE::GUARD))
	//		{
	//			//�O�ړ�
	//			m_charaState = eCHARACTER_STATE::MOVE_FRONT;
	//		}
	//		if (((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
	//			keyState.IsKeyDown(DirectX::Keyboard::Keys::A) && m_frontVector.x > 0 &&
	//			m_charaState != eCHARACTER_STATE::SQUAT) ||
	//			((m_charaState == eCHARACTER_STATE::WAIT || m_charaState == eCHARACTER_STATE::JUMP) &&
	//				keyState.IsKeyDown(DirectX::Keyboard::Keys::D) && m_frontVector.x < 0 &&
	//				m_charaState != eCHARACTER_STATE::SQUAT))
	//		{
	//			//��ړ�
	//			m_charaState = eCHARACTER_STATE::MOVE_BACK;

	//		}

	//		//����͂ŃW�����v
	//		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::W) &&
	//			m_charaState != eCHARACTER_STATE::SQUAT &&
	//			m_charaState != eCHARACTER_STATE::BOOST_MOVE)
	//		{
	//			m_charaState = eCHARACTER_STATE::JUMP;
	//		}

	//		//��Shift�ŃK�[�h
	//		if ((m_charaState == eCHARACTER_STATE::WAIT ||
	//			m_charaState == eCHARACTER_STATE::SQUAT ||
	//			m_charaState == eCHARACTER_STATE::MOVE_BACK ||
	//			m_charaState == eCHARACTER_STATE::MOVE_FRONT) &&
	//			keyState.IsKeyDown(DirectX::Keyboard::Keys::Q))
	//		{
	//			m_charaState = eCHARACTER_STATE::GUARD;
	//		}


	//	}
	//}

}



///////////////////////////
//�U��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::Attack()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//�v���C���[�P�̏���
	if (m_playerID == ePLAYER_ID::PLAYER_1)
	{
		//��j���[�g�����U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::Z) &&
			m_charaState == eCHARACTER_STATE::WAIT &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_charaState != eCHARACTER_STATE::DAMAGE &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] = true;
		}

		//�㉺�U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::Z) &&
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_charaState != eCHARACTER_STATE::DAMAGE &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] = true;
		}

		//�㉡�U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::Z) &&
			(keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) ||
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Right)) &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_charaState != eCHARACTER_STATE::DAMAGE &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] = true;
		}

		//���j���[�g�����U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::X) &&
			m_charaState == eCHARACTER_STATE::WAIT &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_charaState != eCHARACTER_STATE::DAMAGE &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] = true;
		}

		//�����U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::X) &&
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_charaState != eCHARACTER_STATE::DAMAGE &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] = true;
		}

		//�����U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::X) &&
			(keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) ||
				keyState.IsKeyDown(DirectX::Keyboard::Keys::Right)) &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_charaState != eCHARACTER_STATE::DAMAGE &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] = true;
		}
	}

	//�v���C���[�Q�̏���
	else if (m_playerID == ePLAYER_ID::PLAYER_2)
	{
		m_aiAttackTimer--;
		if (m_aiAttackTimer <= 0.0f)
		{
			int random = rand() % 2;
			//��U��
			if (random == 0)
			{
				//�j���[�g����
				if (m_charaState == eCHARACTER_STATE::WAIT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] == false &&
					m_isAttacking == false)
				{
					m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] = true;

				}
				//��
				else if (m_charaState == eCHARACTER_STATE::MOVE_FRONT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] == false &&
					m_isAttacking == false)
				{
					m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] = true;

				}
				//��
				else if (m_charaState == eCHARACTER_STATE::SQUAT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] == false &&
					m_isAttacking == false)
				{
					m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] = true;
				}
			}
			//���U��
			else if (random == 1)
			{
				//�j���[�g����
				if (m_charaState == eCHARACTER_STATE::WAIT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] == false &&
					m_isAttacking == false)
				{
					m_isAttackInput[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] = true;

				}
				//��
				else if (m_charaState == eCHARACTER_STATE::MOVE_FRONT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] == false &&
					m_isAttacking == false)
				{
					m_isAttackInput[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] = true;

				}
				//��
				else if (m_charaState == eCHARACTER_STATE::SQUAT &&
					m_charaState != eCHARACTER_STATE::GUARD &&
					m_isAttackUse[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] == false &&
					m_isAttacking == false)
				{
					m_isAttackInput[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] = true;
				}
			}
			m_aiAttackTimer = (rand() % 30) + 30.0f;
		}


		//��j���[�g�����U��
		if (m_pKeyTracker->IsKeyPressed(DirectX::Keyboard::Keys::O) &&
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) == false &&
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) == false &&
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) == false &&
			keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) == false &&
			m_charaState != eCHARACTER_STATE::GUARD &&
			m_isAttackUse[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] == false &&
			m_isAttacking == false)
		{
			m_isAttackInput[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] = true;
		}

	}

}

///////////////////////////
//AI
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharacterBase::AI(DX::StepTimer const& timer)
{
	//�G�Ƃ̋���
	float distance = m_pos.x - m_enemyPos.x;
	//�^�C�}�[�̒l�����炷
	m_aiStateTiemer -= static_cast<float>(m_stepTimer.GetElapsedSeconds());
	//�^�C�}�[�̒l��0�ɂȂ����烉���_���ɏ�Ԃ�؂�ւ���
	if (m_aiStateTiemer <= 0.0f)
	{
		m_aiState = rand() % 8;
		//m_aiStateTiemer = (rand() % 30) + 30.0f;
		m_aiStateTiemer = 1.0f;
	}

	if (m_charaState != eCHARACTER_STATE::DAMAGE)
	{
		switch (m_aiState)
		{
			//�ҋ@
			case 0:
			{
				m_charaState = eCHARACTER_STATE::WAIT;
				break;
			}
			//�ړ�
			case 1:
			{
				m_charaState = eCHARACTER_STATE::MOVE_AI;
				break;
			}
			//�ړ�
			case 2:
			{
				m_charaState = eCHARACTER_STATE::MOVE_AI;
				break;
			}
			//�ړ�
			case 3:
			{
				m_charaState = eCHARACTER_STATE::MOVE_AI;
				break;
			}
			//�ړ�
			case 4:
			{
				m_charaState = eCHARACTER_STATE::MOVE_AI;
				break;
			}
			//�K�[�h
			case 5:
			{
				m_charaState = eCHARACTER_STATE::GUARD;
				break;
			}
			//�u�[�X�g�ړ�
			case 7:
			{
				m_charaState = eCHARACTER_STATE::BOOST_MOVE;
				break;

			}
			default:
				break;
		}
	}

}
