///////////////////////////////////
//���U���g�V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��28��
///////////////////////////////////

#include "pch.h"
#include "ResultScene.h"

#include "Keyboard.h"
#include "../SceneManager.h"
#include "Src\FrameWork\Sprite2D\Sprite2D.h"
#include "Src\FrameWork\FadeManager\FadeManager.h"
#include "Src/Cgdi.h"

ePLAYER_ID ResultScene::m_winPlayerID = ePLAYER_ID::PLAYER_1;

//�R���X�g���N�^
ResultScene::ResultScene()
{
	//���N���X�̃R���X�g���N�^
	SceneBase::SceneBase();
}

//�f�X�g���N�^
ResultScene::~ResultScene()
{
	//���N���X�̃f�X�g���N�^
	SceneBase::~SceneBase();
}

///////////////////////////
//������
//����:�E�B���h�E�A�f�o�C�X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void ResultScene::Initialize()
{
	//���N���X�̏������֐�
	SceneBase::Initialize();


	SetFadeTimer(1.0f);
	SetSceneState(eSCENE_STATE::FADE_IN);

	//�摜�̓ǂݍ���
	m_winPlayer1Sprite = std::make_unique<Sprite2D>();
	m_winPlayer1Sprite->Create(L"Resources/Textures/p1win_result.png");
	m_winPlayer2Sprite = std::make_unique<Sprite2D>();
	m_winPlayer2Sprite->Create(L"Resources/Textures/p2win_result.png");
	m_winPlayer1Sprite->Update(640.0f, 300.0f);
	m_winPlayer2Sprite->Update(640.0f, 300.0f);

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ResultScene::Update(DX::StepTimer const & timer)
{
	//���N���X�̍X�V�֐�
	SceneBase::Update(timer);

	//�r���[�s��̍X�V
	//SetView( DirectX::SimpleMath::Matrix::CreateLookAt(GetCameraPos(), GetTargetPos(), DirectX::SimpleMath::Vector3::UnitY));
	//m_view = m_pDebugCamera->getViewMatrix();

	float time = float(timer.GetTotalSeconds());

	//�V�[���̃X�e�[�g
	switch (GetSceneState())
	{
		//�t�F�[�h�C��
		case eSCENE_STATE::FADE_IN:
		{
			//�t�F�[�h�̃^�C�}�[�����Z����
			SetFadeTimer(GetFadeTimer() - static_cast<float>(timer.GetElapsedSeconds()) * 2.0f);
			//�^�C�}�[��0�ȉ��ɂȂ����烁�C���X�e�[�g�ɑJ��
			if (GetFadeTimer() <= 0.0f)SetSceneState(eSCENE_STATE::MAIN);
			break;
		}
		//���C��
		case eSCENE_STATE::MAIN:
		{
			//�X�y�[�X�L�[���͂Ńt�F�[�h�A�E�g�ɑJ��
			if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Space))
			{
				SetSceneState(eSCENE_STATE::FADE_OUT);
			}

			break;
		}


		//�t�F�[�h�A�E�g
		case eSCENE_STATE::FADE_OUT:
		{
			//�t�F�[�h�̃^�C�}�[�����Z����
			SetFadeTimer(GetFadeTimer() + static_cast<float>(timer.GetElapsedSeconds()) * 2.0f);
			//�^�C�}�[���K��l���z������L�����N�^�[�Z���N�g�V�[���ɑJ��
			if (GetFadeTimer() >= 1.0f)SceneManager::GetInstance()->SetScene(eSCENE_ID::CHARA_SELECT_SCENE);

			break;
		}
		default:
			break;
	}

	//�t�F�[�h�}�l�[�W���[�̍X�V
	FadeManager::GetInstance()->Update(timer, GetFadeTimer());
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ResultScene::Render()
{
	if (m_winPlayerID == ePLAYER_ID::PLAYER_1)
	{
		m_winPlayer1Sprite->Draw(true, false);
	}
	else if (m_winPlayerID == ePLAYER_ID::PLAYER_2)
	{
		m_winPlayer2Sprite->Draw(true, false);
	}

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ResultScene::Finalize()
{
	m_winPlayer1Sprite->Reset();
	m_winPlayer2Sprite->Reset();

}
