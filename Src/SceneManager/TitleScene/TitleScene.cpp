///////////////////////////////////
//�^�C�g���V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////

#include "pch.h"
#include "TitleScene.h"

#include "../SceneManager.h"
#include "Keyboard.h"
#include "Src\FrameWork\DebugFont\DebugFont.h"

#include "Src\FrameWork\Sprite2D\Sprite2D.h"
#include "Src\FrameWork\FadeManager\FadeManager.h"
#include "Game.h"

#include "Adx2.h"
#include "CueSheet_0.h"
#include "Src/Cgdi.h"


//pushSpace�̉摜�̍��W
const DirectX::SimpleMath::Vector2 TitleScene::PUSH_SPACE_POS = DirectX::SimpleMath::Vector2(700.0f,700.0f);
//pushSpace�̉摜�̓_�ŃC���^�[�o��
const float TitleScene::PUSH_SPACE_BLIND_INTERBVAL = 1.0f;
//�V���̍��W
const DirectX::SimpleMath::Vector3 TitleScene::SKYBOX_POS = DirectX::SimpleMath::Vector3(0.0f, 20.0f, 0.0f);

TitleScene::TitleScene()
{
	//���N���X�̃R���X�g���N�^
	SceneBase::SceneBase();

	m_pLogoSprite = nullptr;
	m_pSpaceSprite = nullptr;

	m_pushSpaceBlindFlag = true;
	m_pushSpaceBlindTimer = 0.0f;

	m_skyBoxAngleY = 0.0f;
}


TitleScene::~TitleScene()
{
	//���N���X�̃f�X�g���N�^
	SceneBase::~SceneBase();

	m_pLogoSprite.reset();
	m_pSpaceSprite.reset();

	m_pSkyBox.reset();


}


///////////////////////////
//������
//����:�f�o�C�X���\�[�X�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void TitleScene::Initialize()
{
	//���N���X�̏������֐�
	SceneBase::Initialize();

	//���S�摜�̓ǂݍ���
	m_pLogoSprite = std::make_unique<Sprite2D>();
	m_pLogoSprite->Create(L"Resources/Textures/logo.png");
	//pushSpace�̉摜�̓ǂݍ���
	m_pSpaceSprite = std::make_unique<Sprite2D>();
	m_pSpaceSprite->Create(L"Resources/Textures/pushSpace.png");

	//�V���̃��f���ǂݍ���
	m_pSkyBox = std::make_unique<ModelObject>();
	m_pSkyBox->Create(GetDeviceResources(), L"Resources/Models/Space.cmo");
	//�V���̃��[���h�s��ݒ�
	m_skyBoxWorld = DirectX::SimpleMath::Matrix::Identity;

	//pushSpace�̉摜�̓_�Ńt���O������
	m_pushSpaceBlindFlag = true;
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void TitleScene::Update(DX::StepTimer const& timer)
{
	//���N���X�̍X�V
	SceneBase::Update(timer);

	//�X�y�[�X���͂̉摜�X�V
	m_pSpaceSprite->Update(PUSH_SPACE_POS);

	//�V������]������
	DirectX::SimpleMath::Matrix pos = DirectX::SimpleMath::Matrix::CreateTranslation(SKYBOX_POS);
	m_skyBoxAngleY += 0.001f;
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_skyBoxAngleY);
	//�V���̃��[���h�s��̐ݒ�
	m_skyBoxWorld = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Zero) * rotY * pos;

	//�V���̃��f���̍X�V
	m_pSkyBox->Update(m_skyBoxWorld);

	////pushSpace�̉摜�̓_�Ń^�C�}�[�B�t���O�̍X�V
	m_pushSpaceBlindTimer += static_cast<float>(timer.GetElapsedSeconds());
	if (m_pushSpaceBlindTimer >= PUSH_SPACE_BLIND_INTERBVAL)
	{
		m_pushSpaceBlindFlag = !m_pushSpaceBlindFlag;
		m_pushSpaceBlindTimer = 0.0f;
	}

	//�t�F�[�h�}�l�[�W���[�̍X�V
	FadeManager::GetInstance()->Update(timer, GetFadeTimer());

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
				//SE�Đ�
				SetSoundID(ADX2::GetInstance().Play(CRI_CUESHEET_0_SUBMIT));
			}
			//ESC���͂ŃQ�[�����I������
			if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Escape))
			{

				PostQuitMessage(0);

			}

			break;
		}
		//�t�F�[�h�A�E�g
		case eSCENE_STATE::FADE_OUT:
		{
			//�t�F�[�h�̃^�C�}�[�����Z����
			SetFadeTimer(GetFadeTimer() + static_cast<float>(timer.GetElapsedSeconds()) * 2.0f);
			//�^�C�}�[���K��l���z������L�����N�^�[�Z���N�g�V�[���ɑJ��
			if (GetFadeTimer() >= 1.0f)
			{
				SceneManager::GetInstance()->SetScene(eSCENE_ID::CHARA_SELECT_SCENE);
			}

			break;
		}
		default:
			break;
	}
	
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void TitleScene::Render()
{
	//�V���̕`��
	m_pSkyBox->Render(GetView(), GetProj());

	//���S�摜�̕`��
	m_pLogoSprite->Draw(true);
	//pushSpace�̉摜�̕`��
	if(m_pushSpaceBlindFlag)m_pSpaceSprite->Draw(true);
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void TitleScene::Finalize()
{
	m_pSkyBox->Lost();

	m_pLogoSprite->Reset();
	m_pSpaceSprite->Reset();
}






