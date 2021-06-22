///////////////////////////////
//�v���C�V�[���̑�������̃N���X
//�쐬���F2021�N5��9��
//�쐬�ҁFGT2_04_��_�D��
///////////////////////////////

#include "pch.h"
#include "PlaySceneManual.h"
#include "../Character/CharacterID.h"
#include "../../PlayScene/Character/CharacterFactory.h"

#include "Adx2.h"
#include "CueSheet_0.h"

#include "../PlayScene.h"

//��������̉摜�̉���
const float PlaySceneManual::MANUAL_SPRITE_WIDTH = 1920.0f;
//��������̉摜�̍���
const float PlaySceneManual::MANUAL_SPRITE_HEIGHT = 1080.0f;

//�R���X�g���N�^
PlaySceneManual::PlaySceneManual()
	:m_isManualDown(false),
	m_isManualLeft(false),
	m_isManualRight(false),
	m_isManualUp(false),
	m_pPlayScene(nullptr)
{
}

//�f�X�g���N�^
PlaySceneManual::~PlaySceneManual()
{
}

////////////////////////
//������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneManual::Initialize()
{
	//��������̉摜�ǂݍ��݁A�������W�ݒ�
	for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
	{
		m_pManualSprite[i] = std::make_unique<Sprite2D>();

		m_ManualSpritePos[i].y = -MANUAL_SPRITE_HEIGHT;

	}
	m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::COMMAND)].x = MANUAL_SPRITE_WIDTH;

	m_pManualSprite[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)]
		->Create(L"Resources/Textures/Manual_1.png");

	//��������̃J�[�\���摜�̓ǂݍ���
	m_pManualCursorSpriteRight = std::make_unique<Sprite2D>();
	m_pManualCursorSpriteRight->Create(L"Resources/Textures/ManualCursolr_Right.png");
	m_pManualCursorSpriteLeft = std::make_unique<Sprite2D>();
	m_pManualCursorSpriteLeft->Create(L"Resources/Textures/ManualCursolr_Left.png");

	//���삵�Ă���L�����N�^�[���Ƃɓǂݍ��ޑ�������̉摜��؂�ւ���
	switch (CharacterFactory::m_player1Chara)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			m_pManualSprite[static_cast<int>(eMANUAL_SPRITE_TYPE::COMMAND)]
				->Create(L"Resources/Textures/Manual_2_chara1.png");
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			m_pManualSprite[static_cast<int>(eMANUAL_SPRITE_TYPE::COMMAND)]
				->Create(L"Resources/Textures/Manual_2_chara2.png");
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			m_pManualSprite[static_cast<int>(eMANUAL_SPRITE_TYPE::COMMAND)]
				->Create(L"Resources/Textures/Manual_2_chara3.png");
			break;
		}

		default:
			break;
	}

}

////////////////////////
//�X�V
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneManual::Update()
{
	//��������\������ESC�L�[�ŃQ�[���ɖ߂�
	if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Escape) && m_pPlayScene->GetIsManualDisplay() == true)
	{
		//���~�t���O������
		m_isManualDown = false;
		//�㏸�t���O�𗧂Ă�
		m_isManualUp = true;

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CANCEL);
	}

	//���E���͂ňړ��t���O�𗧂Ă�
	//������
	if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Left) &&
		m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x < 0.0f)
	{
		m_isManualLeft = false;
		m_isManualRight = true;

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);

	}
	//�E����
	else if (m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Right) &&
		m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x >= 0.0f)
	{
		m_isManualRight = false;
		m_isManualLeft = true;

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);

	}

	//�J�[�\���X�V
	if (m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x < 0.0f)
	{
		m_pManualCursorSpriteRight->Update(DirectX::SimpleMath::Vector2(100.0f, 540.0f));
	}

	//��������̃J�[�\���̍X�V
	m_pManualCursorSpriteRight->Update(DirectX::SimpleMath::Vector2(1720.0f + cosf(m_pPlayScene->GetTotalTime() * 6.0f) * 10.0f, 540.0f));
	m_pManualCursorSpriteLeft->Update(DirectX::SimpleMath::Vector2(50.0f - cosf(m_pPlayScene->GetTotalTime() * 6.0f) * 10.0f, 540.0f));


	//�E�ړ��t���O����������摜���E�Ɉړ�������
	if (m_isManualRight == true)
	{
		for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
		{
			m_ManualSpritePos[i].x += MANUAL_SPRITE_WIDTH / 10.0f;

			//�E�Ɉړ����I�������E�ړ��t���O������
			if (m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x >= 0.0f)
			{
				m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x = 0.0f;
				m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::COMMAND)].x = MANUAL_SPRITE_WIDTH;
				m_isManualRight = false;
			}
		}
	}

	//���ړ��t���O����������摜�����Ɉړ�������
	if (m_isManualLeft == true)
	{
		for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
		{
			m_ManualSpritePos[i].x -= MANUAL_SPRITE_WIDTH / 10.0f;
			//���Ɉړ����I������獶�ړ��t���O������
			if (m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x <= -MANUAL_SPRITE_WIDTH)
			{
				m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x = -MANUAL_SPRITE_WIDTH;
				m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::COMMAND)].x = 0.0f;
				m_isManualLeft = false;
			}
		}

	}

	//���~�t���O����������摜�����~������
	if (m_isManualDown == true)
	{
		for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
		{
			m_ManualSpritePos[i].y += MANUAL_SPRITE_HEIGHT / 10.0f;

			//�~�����I�������~���t���O������
			if (m_ManualSpritePos[i].y >= 0.0f)
			{
				m_ManualSpritePos[i].y = 0.0f;
				m_isManualDown = false;
			}
		}
	}

	//�㏸�t���O����������摜���㏸������
	if (m_isManualUp == true)
	{
		for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
		{
			m_ManualSpritePos[i].y -= MANUAL_SPRITE_HEIGHT / 10.0f;
			//�㏸���I�������㏸�t���O������
			if (m_ManualSpritePos[i].y <= -MANUAL_SPRITE_HEIGHT)
			{
				m_ManualSpritePos[i].y = -MANUAL_SPRITE_HEIGHT;
				m_isManualUp = false;
				//�Q�[����~�t���O������
				m_pPlayScene->SetIsManualDisplay(false);
			}
		}
	}

	//�摜�̍X�V
	for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
	{
		m_pManualSprite[i]->Update(m_ManualSpritePos[i]);

	}

}

////////////////////////
//�`��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneManual::Render()
{
	for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
	{
		m_pManualSprite[i]->Draw(true);
	}

	//��������̃J�[�\���摜�̕`��
	//��
	if (m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::KEYBOARD)].x < 0.0f)
	{
		m_pManualCursorSpriteLeft->Draw(true);
	}
	//�E
	else
	{
		m_pManualCursorSpriteRight->Draw(true);
	}
}

////////////////////////
//�I������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
////////////////////////
void PlaySceneManual::Finalize()
{
	for (int i = 0; i < static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM); i++)
	{
		m_pManualSprite[i]->Reset();

	}

	m_pManualCursorSpriteLeft->Reset();
	m_pManualCursorSpriteLeft.reset();

	m_pManualCursorSpriteRight->Reset();
	m_pManualCursorSpriteRight.reset();

}
