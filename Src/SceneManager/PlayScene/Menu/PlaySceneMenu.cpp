///////////////////////////////
//�v���C�V�[���̃��j���[�̃N���X
//�쐬���F2021�N5��9��
//�쐬�ҁFGT2_04_��_�D��
///////////////////////////////

#include "pch.h"
#include "PlaySceneMenu.h"
#include "../PlayScene.h"

#include "Adx2.h"
#include "CueSheet_0.h"
#include "../../SceneManager.h"

 //�J�[�\���̍��W
const DirectX::SimpleMath::Vector2 PlaySceneMenu::MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::OVER_ID)] =
{
   DirectX::SimpleMath::Vector2(630.0f,300.0f),
   DirectX::SimpleMath::Vector2(630.0f,500.0f),
   DirectX::SimpleMath::Vector2(630.0f,700.0f)
};
//�R���X�g���N�^
PlaySceneMenu::PlaySceneMenu()
{
	m_menuCursor = static_cast<int>(eMENU_CURSOR::MANUAL);
	m_isMenuDisplay = false;
	m_pPlayScene = nullptr;
}

//�f�X�g���N�^
PlaySceneMenu::~PlaySceneMenu()
{
}

////////////////////////
//������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneMenu::Initialize()
{
	//���j���[�̉摜�ǂݍ���
	m_pMenuSprite = std::make_unique<Sprite2D>();
	m_pMenuSprite->Create(L"Resources/Textures/Menu.png");
	//�J�[�\���̉摜�̓ǂݍ���
	m_pMenuCursorSprite = std::make_unique<Sprite2D>();
	m_pMenuCursorSprite->Create(L"Resources/Textures/menuCursol.png");

	//���������ʃN���X�̃|�C���^
	m_pPlaySceneManual = std::make_unique<PlaySceneManual>();
	//�v���C�V�[���̃|�C���^��n��
	m_pPlaySceneManual->SetPlayScene(m_pPlayScene);
	//���������ʃN���X�̏�����
	m_pPlaySceneManual->Initialize();

}

////////////////////////
//�X�V
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneMenu::Update()
{
	if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Escape) && m_pPlayScene->GetIsManualDisplay() == false)
	{
		//SE�Đ�
		if (m_pPlayScene->GetIsStop() == false)
			ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);
		else if (m_pPlayScene->GetIsStop() == true)
			ADX2::GetInstance().Play(CRI_CUESHEET_0_CANCEL);

		bool isStop = m_pPlayScene->GetIsStop();

		m_pPlayScene->SetIsStop(!isStop);
	}

	//�J�[�\���̍��W�ݒ�
	switch (static_cast<eMENU_CURSOR>(m_menuCursor))
	{
		//�}�j���A��
	case eMENU_CURSOR::MANUAL:
	{
		m_pMenuCursorSprite->
			Update(MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::MANUAL)].x - cosf(m_pPlayScene->GetTotalTime() * 6.0f) * 10.0f, MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::MANUAL)].y);
		break;
	}
	//�L�����N�^�[�Z���N�g
	case eMENU_CURSOR::CHARA_SELECT:
	{
		m_pMenuCursorSprite->
			Update(MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::CHARA_SELECT)].x - cosf(m_pPlayScene->GetTotalTime() * 6.0f) * 10.0f, MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::CHARA_SELECT)].y);
		break;
	}
	//�Q�[���I��
	case eMENU_CURSOR::EXIT:
	{
		m_pMenuCursorSprite->
			Update(MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::EXIT)].x - cosf(m_pPlayScene->GetTotalTime() * 6.0f) * 10.0f, MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::EXIT)].y);
		break;
	}
	default:
		break;
	}

	//�L�[���͂ŃJ�[�\���ړ�
	//�����
	if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Down)
		&& m_pPlayScene->GetIsStop() == true &&
		m_pPlayScene->GetIsManualDisplay() == false)
	{
		m_menuCursor++;
		if (m_menuCursor >= static_cast<int>(eMENU_CURSOR::OVER_ID))
		{
			m_menuCursor = static_cast<int>(eMENU_CURSOR::MANUAL);
		}

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);

	}
	//������
	else if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Up) && m_pPlayScene->GetIsStop() == true && m_pPlayScene->GetIsManualDisplay() == false)
	{
		m_menuCursor--;
		if (m_menuCursor <= static_cast<int>(eMENU_CURSOR::NONE))
		{
			m_menuCursor = static_cast<int>(eMENU_CURSOR::EXIT);
		}

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);
	}

	//�X�y�[�X�L�[���͂Ō���
	if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Space) && m_pPlayScene->GetIsStop() == true && m_pPlayScene->GetIsManualDisplay() == false)
	{
		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_SUBMIT);

		switch (static_cast<eMENU_CURSOR>(m_menuCursor))
		{
			//��������\��
		case eMENU_CURSOR::MANUAL:
		{
			if (m_pPlayScene->GetIsManualDisplay() == false)
			{
				m_pPlayScene->SetIsManualDisplay(true);
				m_pPlaySceneManual->SetIsManualDown(true);
			}
			break;
		}

		//�L�����N�^�[�Z���N�g�ɖ߂�
		case eMENU_CURSOR::CHARA_SELECT:
		{
			SceneManager::GetInstance()->SetScene(eSCENE_ID::CHARA_SELECT_SCENE);
			//SE�Đ�
			//ADX2::GetInstance().Play(CRI_CUESHEET_0_CANCEL);
			//ADX2::GetInstance().Stop(GetSoundID());
			break;
		}

		//�Q�[���I��
		case eMENU_CURSOR::EXIT:
		{
			PostQuitMessage(0);
			break;
		}

		default:
			break;
		}
	}

	//��������̕\���t���O���������瑀������̍X�V
	if (m_pPlayScene->GetIsManualDisplay() == true && m_pPlaySceneManual != nullptr)m_pPlaySceneManual->Update();

}

////////////////////////
//�`��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneMenu::Render()
{
	if (m_pPlayScene->GetIsStop() == true)
	{	
		//���j���[�摜�̕`��
		m_pMenuSprite->Draw(true);
		//���j���[�̃J�[�\���摜�̕`��
		m_pMenuCursorSprite->Draw(true);
	}
	//��������̉摜�̕`��
	if (m_pPlayScene->GetIsManualDisplay() == true)
	{
		m_pPlaySceneManual->Render();
	}
}

////////////////////////
//�I������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneMenu::Finalize()
{
	//��������N���X�̏I������
	m_pPlaySceneManual->Finalize();

	//���\�[�X�̉��
	m_pMenuCursorSprite.reset();
	m_pMenuCursorSprite = nullptr;
	m_pMenuSprite.reset();
	m_pMenuSprite = nullptr;

}
