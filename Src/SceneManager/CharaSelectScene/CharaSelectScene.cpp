///////////////////////////////////
//�L�����N�^�[�Z���N�g�V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��15��
///////////////////////////////////

#include "pch.h"
#include "CharaSelectScene.h"
#include "Src\SceneManager\SceneManager.h"
#include "Keyboard.h"

#include "../PlayScene/Character/CharacterID.h"
#include "../PlayScene/Character/CharacterFactory.h"

#include "Src\FrameWork\FadeManager\FadeManager.h"

#include "Src\FrameWork\Sprite2D\Sprite2D.h"

#include "Adx2.h"


#include "CueSheet_0.h"

#include "../../FrameWork/LoadDisplay/LoadDisplay.h"

#include "../../FrameWork/FbxResourceManager/FbxResourceManager.h"
#include "../PlayScene/Character/ChracterAnimationNumber.h"
#include "Src/Cgdi.h"

//�e�L�����N�^�[�̃A�C�R���̍��W
const DirectX::SimpleMath::Vector2 CharaSelectScene::CHARA1_ICON_POS = DirectX::SimpleMath::Vector2(250.0f, 260.0f);
const DirectX::SimpleMath::Vector2 CharaSelectScene::CHARA2_ICON_POS = DirectX::SimpleMath::Vector2(810.0f, 260.0f);
const DirectX::SimpleMath::Vector2 CharaSelectScene::CHARA3_ICON_POS = DirectX::SimpleMath::Vector2(1370.0f, 260.0f);
const float CharaSelectScene::CURSOL_POS = 10.0f;
//�L�����N�^�[�̏��摜�̍��W
const DirectX::SimpleMath::Vector2 CharaSelectScene::CHARA_INFO_POS = DirectX::SimpleMath::Vector2(0,580.0f);
//��������̉摜�̉���
const float CharaSelectScene::MANUAL_SPRITE_WIDTH = 1920.0f;
//��������̉摜�̍���
const float CharaSelectScene::MANUAL_SPRITE_HEIGHT = 1080.0f;
//�e�L�����N�^�[�̃��f���̃T�C�Y
const float CharaSelectScene::MODEL_SIZE[CharaSelectScene::CHARA_NUM] =
{
	0.003f,0.015f,0.015f
};

//���f���̍��W
const DirectX::SimpleMath::Vector3 CharaSelectScene::MODEL_POS = DirectX::SimpleMath::Vector3(-3.7f, -1.0f, 0.0f);
//���f���̐F						 
const DirectX::SimpleMath::Vector4 CharaSelectScene::MODEL_COLOR = DirectX::SimpleMath::Vector4(0.3f, 0.3f, 0.3f, 1.0f);

//�R���X�g���N�^
CharaSelectScene::CharaSelectScene()
	:SceneBase::SceneBase()
{
	m_pSelectSprite = nullptr;
	m_isStop = false;
	m_isManualDown = m_isManualUp = false;
	m_modelAngleY = 0.0f;
}

//�f�X�g���N�^
CharaSelectScene::~CharaSelectScene()
{
	m_pSelectSprite.reset();

	for (int i = 0; i < static_cast<int>(eCHARACTER_ID::OVER_ID); i++)
	{
		m_pCharacterSprite[i].reset();
	}

	m_pCursolSprite.reset();

}

///////////////////////////
//������
//����:�E�B���h�E�A�f�o�C�X
//�߂�l:�Ȃ�
//////////////////////////
void CharaSelectScene::Initialize()
{
	//���N���X�̏���������
	SceneBase::Initialize();

	//�e�L�����N�^�[�̃��f���̓ǂݍ���
	m_pCharacter1Model = FbxResourceManager::GetInstance()->GetModel(eCHARACTER_ID::CHARACTER_1);
	m_pCharacter2Model = FbxResourceManager::GetInstance()->GetModel(eCHARACTER_ID::CHARACTER_2);
	m_pCharacter3Model = FbxResourceManager::GetInstance()->GetModel(eCHARACTER_ID::CHARACTER_3);

	m_pCharacter1Model->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::WAIT));
	m_pCharacter2Model->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::WAIT));
	m_pCharacter3Model->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::WAIT));
		
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_modelAngleY);
	//
	for (int i = 0; i < CHARA_NUM; i++)
	{
		//�e�L�����N�^�[�̃��[���h�s���ݒ�
		m_modelWorld[i] = DirectX::SimpleMath::Matrix::CreateScale(MODEL_SIZE[i]) *  DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Zero) *
			rotY * DirectX::SimpleMath::Matrix::CreateTranslation(MODEL_POS) * rotY;
	}

	//�w�i�摜�̓ǂݍ���
	m_pSelectSprite = std::make_unique<Sprite2D>();
	m_pSelectSprite->Create(L"Resources/Textures/CharacterSelect2.png");

	//�L�����N�^�[�̃A�C�R���̓ǂݍ���
	for (int i = 0; i < static_cast<int>(eCHARACTER_ID::OVER_ID); i++)
	{
		m_pCharacterSprite[i] = std::make_unique<Sprite2D>();
		m_pCharaInfoSprite[i] = std::make_unique<Sprite2D>();
	}
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_1)]->Create(
		L"Resources/Textures/character1_icon.png");
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_2)]->Create(
		L"Resources/Textures/character2_icon.png");
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_3)]->Create(
		L"Resources/Textures/character3_icon.png");
	
	m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_1)]->Create(
		L"Resources/Textures/charaInfo_1.png");
	m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_2)]->Create(
		L"Resources/Textures/charaInfo_2.png");
	m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_3)]->Create(
		L"Resources/Textures/charaInfo_3.png");

	//��������̉摜�̓ǂݍ���
	m_pManualSprite = std::make_unique<Sprite2D>();
	m_pManualSprite->Create(L"Resources/Textures/Manual_1_charaSelect.png");
	//��������̉摜�̏������W�ݒ�
	m_ManualSpritePos = DirectX::SimpleMath::Vector2(0, -MANUAL_SPRITE_HEIGHT);


	//�L�����N�^�[�̏��摜�̍��W�ݒ�
	for (int i = 0; i < static_cast<int>(eCHARACTER_ID::OVER_ID); i++)
	{
		m_pCharaInfoSprite[i]->Update(CHARA_INFO_POS);
	}

	//�L�����N�^�[�̃A�C�R���̏������W�ݒ�
	//�L�����N�^�[�̃A�C�R���̍��W�ݒ�
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_1)]->Update(CHARA1_ICON_POS);
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_2)]->Update(CHARA2_ICON_POS);
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_3)]->Update(CHARA3_ICON_POS);



	//�J�[�\���̉摜�̓ǂݍ���
	m_pCursolSprite = std::make_unique<Sprite2D>();
	m_pCursolSprite->Create(L"Resources/Textures/SelectCursol.png");
	//�J�[�\���̉摜�̏������W�ݒ�
	m_pCursolSprite->Update(CHARA1_ICON_POS.x - CURSOL_POS, CHARA1_ICON_POS.y - CURSOL_POS);

	SetFadeTimer(1.0f);
	SetSceneState(eSCENE_STATE::FADE_IN);

	//���ݑI�����Ă���L�����N�^�[�̏����ݒ�
	m_nowSelect = static_cast<int>(eCHARACTER_ID::CHARACTER_1);

	//BGM�̍Đ�
	m_soundID = ADX2::GetInstance().Play(CRI_CUESHEET_0_SELECTSCENE_BGM);

	//�J�[�\���̏����J���[�ݒ�
	m_cursorColor = DirectX::SimpleMath::Vector4(0.0f, 1.0f, 1.0f, 1.0f);
}

///////////////////////////
//�X�V
//����:�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void CharaSelectScene::Update(DX::StepTimer const & timer)
{
	//���N���X�̍X�V�֐�
	SceneBase::Update(timer);

	//�L�����N�^�[�̃A�C�R���̍��W�ݒ�
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_1)]->Update(CHARA1_ICON_POS);
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_2)]->Update(CHARA2_ICON_POS);
	m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_3)]->Update(CHARA3_ICON_POS);

	static int id;

	m_cursorColor.x = cosf((float)timer.GetTotalSeconds()*3.0f);

	//�t�F�[�h�}�l�[�W���[�̍X�V
	FadeManager::GetInstance()->Update(timer, GetFadeTimer());

	//�V�[���̃X�e�[�g
	switch (GetSceneState())
	{
		//�t�F�[�h�C��
		case eSCENE_STATE::FADE_IN:
		{
			SetFadeTimer(GetFadeTimer() - static_cast<float>(timer.GetElapsedSeconds())* 2.0f);
			if (GetFadeTimer() <= 0.0f)SetSceneState(eSCENE_STATE::MAIN);

			break;
		}
		//���C��
		case eSCENE_STATE::MAIN:
		{

			//�������
			CharaSelectScene::Manual();
			
			m_modelAngleY += 0.01f;
			DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_modelAngleY);
			//
			for (int i = 0; i < CHARA_NUM; i++)
			{
				//m_modelWorld[i] *= DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Zero);
				//m_modelWorld[i] *= rotY;// *DirectX::SimpleMath::Matrix::CreateTranslation(MODEL_POS);
				//m_modelWorld[i] *= DirectX::SimpleMath::Matrix::CreateTranslation(MODEL_POS);
				m_modelWorld[i] = DirectX::SimpleMath::Matrix::CreateScale(MODEL_SIZE[i]) *  DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Zero) *
					rotY * DirectX::SimpleMath::Matrix::CreateTranslation(MODEL_POS);
				
			}
			//m_modelWorld = modelSize;

			if (m_isStop != true)
			{
				//���E�L�[���͂ŃJ�[�\���ړ�
				if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Right))
				{
					m_nowSelect++;
					//SE�Đ�
					ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);

				}
				else if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Left))
				{
					m_nowSelect--;
					//SE�Đ�
					ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);

				}

				switch (static_cast<eCHARACTER_ID>(m_nowSelect))
				{
					case eCHARACTER_ID::NONE:
					{
						m_nowSelect = static_cast<int>(eCHARACTER_ID::CHARACTER_3);
						break;
					}
					case eCHARACTER_ID::CHARACTER_1:
					{
						CharacterFactory::m_player1Chara = eCHARACTER_ID::CHARACTER_1;
						//�J�[�\���̉摜�̍��W�ݒ�
						m_pCursolSprite->Update(CHARA1_ICON_POS.x - CURSOL_POS, CHARA1_ICON_POS.y - CURSOL_POS);


						break;
					}
					case eCHARACTER_ID::CHARACTER_2:
					{
						CharacterFactory::m_player1Chara = eCHARACTER_ID::CHARACTER_2;
						//�J�[�\���̉摜�̍��W�ݒ�
						m_pCursolSprite->Update(CHARA2_ICON_POS.x - CURSOL_POS, CHARA2_ICON_POS.y - CURSOL_POS);

						break;
					}
					case eCHARACTER_ID::CHARACTER_3:
					{
						CharacterFactory::m_player1Chara = eCHARACTER_ID::CHARACTER_3;
						//�J�[�\���̉摜�̍��W�ݒ�
						m_pCursolSprite->Update(CHARA3_ICON_POS.x - CURSOL_POS, CHARA3_ICON_POS.y - CURSOL_POS);

						break;
					}
					case eCHARACTER_ID::OVER_ID:
					{
						m_nowSelect = static_cast<int>(eCHARACTER_ID::CHARACTER_1);
						break;
					}
					default:
						break;
				}

				//�X�y�[�X�L�[���͂Ńt�F�[�h�A�E�g		
				if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Space))
				{
					SetSceneState(eSCENE_STATE::FADE_OUT);
					//SE�Đ�
					ADX2::GetInstance().Play(CRI_CUESHEET_0_SUBMIT);

					//LoadDisplay::GetInstance()->Update(true);
				}

				//�G�X�P�[�v�L�[���͂Ń^�C�g���ɖ߂�
				if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Escape))
				{
					SceneManager::GetInstance()->SetScene(eSCENE_ID::TITLE_SCENE);
					//SE�Đ�
					ADX2::GetInstance().Play(CRI_CUESHEET_0_CANCEL);

					ADX2::GetInstance().Stop(m_soundID);

				}

				
			}
			break; 
		}
		//�t�F�[�h�A�E�g
		case eSCENE_STATE::FADE_OUT:
		{
			SetFadeTimer(GetFadeTimer() + static_cast<float>(timer.GetElapsedSeconds())* 2.0f);
			if (GetFadeTimer() >= 1.0f)
			{
				//�v���C���|�Q�̃L�����N�^�[�������_���őI��
				switch (rand() % static_cast<int>(eCHARACTER_ID::OVER_ID))
					//switch(0)
				{
					//�L�����N�^�[�P
					case static_cast<int>(eCHARACTER_ID::CHARACTER_1) :
					{
						CharacterFactory::m_player2Chara = eCHARACTER_ID::CHARACTER_1;
						break;
					}

																		//�L�����N�^�[�Q
					case static_cast<int>(eCHARACTER_ID::CHARACTER_2) :
					{
						CharacterFactory::m_player2Chara = eCHARACTER_ID::CHARACTER_2;
						break;
					}

																		//�L�����N�^�[�R
					case static_cast<int>(eCHARACTER_ID::CHARACTER_3) :
					{
						CharacterFactory::m_player2Chara = eCHARACTER_ID::CHARACTER_3;
						break;
					}

					default:
						break;
				}
				//BGM��~
				ADX2::GetInstance().Stop(m_soundID);

				//�v���C�V�[���ւ̑J��
				SceneManager::GetInstance()->SetScene(eSCENE_ID::PLAY_SCENE);


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
void CharaSelectScene::Render()
{
	//�w�i�摜�̕`��
	m_pSelectSprite->Draw();

	//�J�[�\���̉摜�̕`��
	m_pCursolSprite->Draw(false,false,m_cursorColor);

	//�L�����N�^�[�̃A�C�R���̕`��
	for (int i = 0; i < static_cast<int>(eCHARACTER_ID::OVER_ID); i++)
	{
		m_pCharacterSprite[i]->Draw();
	}

	//�L�����N�^�[�̏��摜�̕`��
	switch (static_cast<eCHARACTER_ID>(m_nowSelect))
	{
		case eCHARACTER_ID::CHARACTER_1:
		{
			m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_1)]
				->Draw(true);
			//���f���̕`��
			m_pCharacter1Model->Draw(m_modelWorld[static_cast<int>(eCHARACTER_ID::CHARACTER_1)], GetView(), GetProj(), MODEL_COLOR);

			break;
		}

		case eCHARACTER_ID::CHARACTER_2:
		{
			m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_2)]
				->Draw(true);
			//���f���̕`��
			m_pCharacter2Model->Draw(m_modelWorld[static_cast<int>(eCHARACTER_ID::CHARACTER_2)], GetView(), GetProj(), MODEL_COLOR);
			break;
		}

		case eCHARACTER_ID::CHARACTER_3:
		{
			m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::CHARACTER_3)]
				->Draw(true);
			//���f���̕`��
			m_pCharacter3Model->Draw(m_modelWorld[static_cast<int>(eCHARACTER_ID::CHARACTER_3)], GetView(), GetProj(), MODEL_COLOR);
			break;
		}

		default:
			break;
	}

	//��������̉摜�̕`��
	if(m_isStop == true && m_pManualSprite != nullptr)
		m_pManualSprite->Draw(true);

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharaSelectScene::Finalize()
{
	m_pSelectSprite->Reset();


	for (int i = 0; i < static_cast<int>(eCHARACTER_ID::OVER_ID); i++)
	{
		m_pCharacterSprite[i]->Reset();
		m_pCharaInfoSprite[i]->Reset();
	}

	m_pCursolSprite->Reset();
	m_pManualSprite->Reset();


	ADX2::GetInstance().Stop(GetSoundID());

	//�L�����N�^�[�̃��f���̃|�C���^���
	m_pCharacter1Model = nullptr;
	m_pCharacter2Model = nullptr;
	m_pCharacter3Model = nullptr;

}

///////////////////////////
//�������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void CharaSelectScene::Manual()
{
	//��������\������X�L�[���͂Ō��̉�ʂɖ߂�
	if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::X) && m_isStop == true)
	{
		m_isManualDown = false;
		m_isManualUp = true;

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CANCEL);

	}

	//X�L�[���͂ő�������̕\��
	if (GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::X) && m_isStop == false)
	{
		m_isStop = true;
		m_isManualDown = true;

		//SE�Đ�
		ADX2::GetInstance().Play(CRI_CUESHEET_0_CURSOL);

	}

	//���~�t���O����������摜�����~������
	if (m_isManualDown == true)
	{
		m_ManualSpritePos.y += MANUAL_SPRITE_HEIGHT / 10.0f;

		if (m_ManualSpritePos.y >= 0.0f)
		{
			m_ManualSpritePos.y = 0.0f;
			m_isManualDown = false;
		}
	}

	//�㏸�t���O����������摜���㏸������
	if (m_isManualUp == true)
	{
		m_ManualSpritePos.y -= MANUAL_SPRITE_HEIGHT / 10.0f;

		if (m_ManualSpritePos.y <= -MANUAL_SPRITE_HEIGHT)
		{
			m_ManualSpritePos.y = -MANUAL_SPRITE_HEIGHT;
			m_isManualUp = false;
			//�Q�[����~�t���O������
			m_isStop = false;
		}
	}

	//�摜�̍X�V
	if(m_pManualSprite != nullptr)
		m_pManualSprite->Update(m_ManualSpritePos);


}

