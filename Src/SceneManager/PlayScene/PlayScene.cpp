///////////////////////////////////
//�v���C�V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////

#include "pch.h"
#include "PlayScene.h"


#include "../../FrameWork/EffectManager/EffectManager.h"
#include "../../FrameWork/FbxModel/FbxModel.h"
#include "../../FrameWork/Sprite2D/Sprite2D.h"
#include "../../FrameWork/DebugFont/DebugFont.h"
#include "../../FrameWork/ModelObject/ModelObject.h"
#include "../../FrameWork/DebugCamera/DebugCamera.h"
#include "Character\CharacterFactory.h"
#include "Character\CharacterBase.h"
#include "Character\CharacterID.h"
#include "../PlayerID.h"

#include "Keyboard.h"
#include "../SceneManager.h"
#include "AttackManager/AttackManager.h"

#include "../ResultScene/ResultScene.h"

#include "../../FrameWork/FbxModel/FbxModel.h"
#include "Character\ShadowManager.h"

#include "Character\HitEffectManager.h"
#include "Src\FrameWork\FadeManager\FadeManager.h"

#include "Adx2.h"
#include "CueSheet_0.h"

#include "../../FrameWork/LoadDisplay/LoadDisplay.h"
#include "Src/Cgdi.h"
#include "UI/PlaySceneUI.h"
#include "Menu/PlaySceneMenu.h"
#include "PlaySceneStateManager/PlaySceneStateManager.h"


 //�J�E���g�_�E���̎���
 const float PlayScene::COUNT_DOWN_TIME = 3.0f;
 //�������Ԃ̍ő�l
 const float PlayScene::TIME_MAX = 60.0f;
 //�^�C���A�b�v�V�[���̐�������
 const float PlayScene::TIME_UP_TIME = 3.0f;
 //���E���h�؂�ւ����̎���
 const float PlayScene::ROUND_CHANGE_TIME = 1.0f;
 //�J�����̍��W
 const DirectX::SimpleMath::Vector3 PlayScene::CAMERA_POS = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 7.0f);

//�R���X�g���N�^
PlayScene::PlayScene()
	:
	m_space(nullptr),
	m_spaceWorld{},
	//m_pAttackManager(nullptr),
	//���N���X�̃R���X�g���N�^
	SceneBase::SceneBase()
{

	m_countdownTimer = 0.0f;

	m_isStop = false;
	m_isManualDisplay = false;
	m_isResult = false;
}

//�f�X�g���N�^
PlayScene::~PlayScene()	
{
	//�O�̂��ߏI������
	//Finalize();

	//m_pFbx.reset();
	m_pDebugCamera.reset();
	m_space.reset();
	m_sprite2D.reset();

	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_pPlayer[i] = nullptr;
	}

	//�U���}�l�[�W���[�̃C���X�^���X�̉��
	AttackManager::ReleaseInstance();
}

///////////////////////////
//������
//����:�f�o�C�X���\�[�X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void PlayScene::Initialize()
{
	//���N���X�̏������֐�
	SceneBase::Initialize();

	//�U���̃}�l�[�W���[�̏�����
	AttackManager::GetInstance()->Initialize(gdi->GetDeviceResources());
	
	//�V���̓ǂݍ���
	m_space = std::make_unique<ModelObject>();
	m_space->Create(gdi->GetDeviceResources(), L"Resources/Models/Space.cmo");
	
	m_isResult = false;

	//�v���C���[�̍쐬
	m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)] = CharacterFactory::CreatePlayer1();
	m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)] = CharacterFactory::CreatePlayer2();

	//�������W�̐ݒ�
	//�v���C���[�P
	switch (m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->GetCharacterID())
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetStartPos(DirectX::SimpleMath::Vector3(-2.0f, 0.0f, 0.0f));

			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetStartPos(DirectX::SimpleMath::Vector3(-2.0f, 1.0f, 0.0f));

			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetStartPos(DirectX::SimpleMath::Vector3(-2.0f, 1.0f, 0.0f));
			break;
		}
		default:
			break;
	}
	//�v���C���[2
	switch (m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->GetCharacterID())
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetStartPos(DirectX::SimpleMath::Vector3(2.0f, 0.0f, 0.0f));

			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetStartPos(DirectX::SimpleMath::Vector3(2.0f, 1.0f, 0.0f));

			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetStartPos(DirectX::SimpleMath::Vector3(2.0f, 1.0f, 0.0f));
			break;
		}
		default:
			break;
	}

	//�v���C���[�Ƀv���C�V�[���̃|�C���^��n��
	m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetPlayScene(this);
	m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetPlayScene(this);

	//UI�N���X�̓ǂݍ���
	m_pPlaySceneUI = std::make_unique <PlaySceneUI>();
	//�v���C�V�[���̃|�C���^��n��
	m_pPlaySceneUI->SetPlayScene(this);
	//UI�N���X�̏�����
	m_pPlaySceneUI->Initialize();


	//�v���C���[�̏�����
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_pPlayer[i]->Initialize();
		m_pPlayer[i]->SetAttackManager(AttackManager::GetInstance());
		//�v���C���[�̏����{���̏�����
		m_playerWinNum[i] = 0;
	
	}

	//�J�����̒����_�̏�����
	SetTargetPos(DirectX::SimpleMath::Vector3::Zero);
	//�J�����̍��W�w��
	SetCameraPos(PlayScene::CAMERA_POS);

	//�v���C�V�[���̃X�e�[�g��������
	m_playSceneState = ePLAY_SCENE_STATE::COUNT_DOWN;

	//���E���h���̏�����
	m_nowRound = eROUND::ROUND_1;

	//�������Ԃ̏�����
	m_time = PlayScene::TIME_MAX;

	//�G�̃|�C���^�擾
	m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetEnemy(m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]);
	m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetEnemy(m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]);

	//���j���[�N���X�̓ǂݍ���
	m_pPlaySceneMenu = std::make_unique<PlaySceneMenu>();
	//�v���C�V�[���̃|�C���^�擾
	m_pPlaySceneMenu->SetPlayScene(this);
	//���j���[�N���X�̏�����
	m_pPlaySceneMenu->Initialize();
	//�v���C�V�[���̃X�e�[�g�}�l�[�W���[�̏�����
	m_pPlaySceneStateManager = std::make_unique<PlaySceneStateManager>();
	m_pPlaySceneStateManager->Initialize(this);
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlayScene::Update(DX::StepTimer const& timer)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//���N���X�̍X�V�֐�
	SceneBase::Update(timer);

	//�o�ߎ��Ԃ����Z����
	m_totalSeconds = static_cast<float>(timer.GetTotalSeconds());


	for (int i = 0; i < PLAYER_NUM; i++)
	{	
		//�̗͂̃o�b�t�@�̓���
		m_playerHpBuffer[i] = m_pPlayer[i]->GetHP();
	}


	//�V����Y���ŉ�]������
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(0.001);
	m_spaceWorld *= rotY;

	//UI�N���X�̍X�V
	m_pPlaySceneUI->Update();

	//�t�F�[�h�}�l�[�W���[�̍X�V
	FadeManager::GetInstance()->Update(timer, GetFadeTimer());

	//��~�t���O�������Ă��Ȃ���΍X�V����
	if (m_isStop == false)
	{
		//�V���̍X�V
		m_space->Update(m_spaceWorld);

		//�v���C�V�[���̃X�e�[�g�}�l�[�W���[�̍X�V
		m_pPlaySceneStateManager->Update(timer, GetSceneState());
	}


	//���j���[�N���X�̍X�V
	if(m_pPlaySceneMenu != nullptr) m_pPlaySceneMenu->Update();
	//���U���g
	if(m_isResult == true)Result(timer);


}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlayScene::Render()
{
	//�V���̕`��
	m_space->Render(GetView(), GetProj());

	//�v���C���[�P�̕`��
	if (m_isResult == false || m_playerWinNum[static_cast<int>(ePLAYER_ID::PLAYER_2)] < WIN_NUM)
	{
		m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->Render(GetView(), GetProj());
	}
	//�v���C���[�Q�̕`��
	if (m_isResult == false || m_playerWinNum[static_cast<int>(ePLAYER_ID::PLAYER_1)] < WIN_NUM)
	{
		m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->Render(GetView(), GetProj());
	}

	//UI�̕`��
	m_pPlaySceneUI->Render();

	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	//���j���[�̕`��
	m_pPlaySceneMenu->Render();

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlayScene::Finalize()
{
	//m_pFbx.reset();
	m_pDebugCamera.reset();
	m_space.reset();
	m_sprite2D.reset();
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		if (m_pPlayer[i] != nullptr)
		{
			m_pPlayer[i]->Finalize();
			//delete m_pPlayer[i];
			m_pPlayer[i] = nullptr;

		}

	}

	DebugFont::Dispose();

	//�U���}�l�[�W���[�̏I������
	AttackManager::GetInstance()->Finalize();
	//�U���}�l�[�W���[�̃C���X�^���X�̉��
	AttackManager::ReleaseInstance();

	//delete m_pFbxModel;
	//m_pFbxModel = nullptr;
	ADX2::GetInstance().Stop(GetSoundID());

	//UI�N���X�̏I������
	m_pPlaySceneUI->Finalize();
	m_pPlaySceneUI.reset();

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlayScene::Reset()
{
	//�e�v���C���[�̃��Z�b�g
	for (int i = 0; i < PLAYER_NUM;i++)
	{
		m_pPlayer[i]->Reset();
	}

	//�U���}�l�[�W���[�̃��Z�b�g
	for (int i = 0; i < AttackManager::ATTACK_NUM; i++)
	{
		AttackManager::GetInstance()->Reset(i);
	}
	//�t�F�[�h�C����Ԃɂ���
	SetSceneState(eSCENE_STATE::FADE_IN);
	//�v���C�V�[���̏�Ԃ��J�E���g�_�E���ɂ���
	m_playSceneState = ePLAY_SCENE_STATE::COUNT_DOWN;
	//�t�F�[�h�̃^�C�}�[��ݒ�
	SetFadeTimer(1.0f);
	//�J�E���g�_�E���̃^�C�}�[��������
	m_countdownTimer = 0.0f;
	//�������Ԃ��ő�l�ɐݒ�
	m_time = PlayScene::TIME_MAX;


	//�J�����̒����_�̏�����
	SetTargetPos(DirectX::SimpleMath::Vector3::Zero);
	SetCameraPos(PlayScene::CAMERA_POS);

	//UI�N���X�̃��Z�b�g
	m_pPlaySceneUI->Reset();
}


///////////////////////////
//���U���g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlayScene::Result(DX::StepTimer const& timer)
{
	if (m_isResult == true)
	{
		SetFadeTimer(0.0f);

		//�v���C���[�P����
		if (m_playerWinNum[static_cast<int>(ePLAYER_ID::PLAYER_1)] >
			m_playerWinNum[static_cast<int>(ePLAYER_ID::PLAYER_2)])
		{
			//�v���C���[�Q�̍��W���J�����O�Ɏ����Ă���
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetPos(
				DirectX::SimpleMath::Vector3(10.0f, 10.0f, 10.0f));
			//�v���C���[�P��������Ԃɂ���
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetCharaState(eCHARACTER_STATE::WIN);

			//m_pPlayer[0]->ChangeAnimation(14);
			//�J�����̍��W�ݒ�
			SetCameraPos(DirectX::SimpleMath::Vector3(
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->GetPos().x,
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->GetPos().y - 1.0f,
				3.0f
			));
			//�����_��ς���
			SetTargetPos(DirectX::SimpleMath::Vector3(
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->GetPos().x,
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->GetPos().y,
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->GetPos().z));

		}
		//�v���C���[�Q����
		else
		{
			//�v���C���[�P�̍��W���J�����O�Ɏ����Ă���
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_1)]->SetPos(
				DirectX::SimpleMath::Vector3(10.0f, 10.0f, 10.0f));

			//�v���C���[�Q��������Ԃɂ���
			m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->SetCharaState(eCHARACTER_STATE::WIN);
			SetCameraPos(DirectX::SimpleMath::Vector3(
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->GetPos().x,
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->GetPos().y - 1.0f,
				3.0f
			));
			//�����_��ς���
			SetTargetPos(DirectX::SimpleMath::Vector3(
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->GetPos().x,
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->GetPos().y,
				m_pPlayer[static_cast<int>(ePLAYER_ID::PLAYER_2)]->GetPos().z));

		}
	}
	//���U���g���ɃX�y�[�X�L�[���͂ŃL�����N�^�[�Z���N�g�ɖ߂�
	if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Space) && m_isResult == true)
	{
		SceneManager::GetInstance()->SetScene(eSCENE_ID::CHARA_SELECT_SCENE);
	}
}
