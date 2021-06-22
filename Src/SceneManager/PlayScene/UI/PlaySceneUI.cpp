//////////////////////////
//�v���C�V�[����UI�N���X
//�쐬���F2021�N4��30��
//�쐬�ҁFGT2_04_��_�D��
/////////////////////////

#include "pch.h"
#include "PlaySceneUI.h"
#include "Src/SceneManager/PlayerID.h"
#include "../Character/CharacterBase.h"
#include "../Character/CharacterFactory.h"

//�̗̓o�[�̉���
const float PlaySceneUI::HP_BAR_WIDTH = 800.0f;
//�̗̓o�[�̍���
const float PlaySceneUI::HP_BAR_HEIGHT = 101.0f;
//�̗̓o�[�̃}�[�W��
const float PlaySceneUI::HP_BAR_MARGIN = 20.0f;

//�u�[�X�g�e�ʃo�[�̉���
const float PlaySceneUI::BOOST_BAR_WIDTH = 700.0f;
//�̗̓o�[�̍���
const float PlaySceneUI::BOOST_BAR_HEIGHT = 70.0f;

//�J�E���g�_�E���̎���
const float PlaySceneUI::COUNT_DOWN_TIME = 3.0f;
//�J�E���g�_�E���摜�̍��W
const DirectX::SimpleMath::Vector2 PlaySceneUI::COUNT_DOWN_SPRITE_POS = DirectX::SimpleMath::Vector2(640.0f, 300.0f);
//�������Ԃ̍ő�l
const float PlaySceneUI::TIME_MAX = 60;
//�����{���̉摜�̉���
const float PlaySceneUI::WIN_NUM_SPRITE_WIDTH = 100.0f;
//�����{���̉摜�̍���
const float  PlaySceneUI::WIN_NUM_SPRITE_HEIGHT = 50.0f;
//�������Ԃ̉摜�̉���
const float PlaySceneUI::TIME_SPRITE_WIDTH = 100.0f;
//�������Ԃ̉摜�̍���
const float PlaySceneUI::TIME_SPRITE_HEIGHT = 200.0f;
//�������Ԃ̉摜��X���W
const float PlaySceneUI::TIME_SPRITE_POS_X = 960.0f;
//���U���g��pushSpace�̉摜�̍��W
const DirectX::SimpleMath::Vector2  PlaySceneUI::PUSH_SPACE_RESULT_POS =
DirectX::SimpleMath::Vector2(1300.0f, 800.0f);


//�̗̓o�[�̍��W
const DirectX::SimpleMath::Vector2 PlaySceneUI::HP_BAR_POS[PlaySceneUI::PLAYER_NUM] =
{
	DirectX::SimpleMath::Vector2(20.0f,50.0f),
	DirectX::SimpleMath::Vector2(1900.0f - HP_BAR_WIDTH,50.0f)
};

//�̗̓o�[�̍��W
const DirectX::SimpleMath::Vector2 PlaySceneUI::BOOST_BAR_POS[PlaySceneUI::PLAYER_NUM] =
{
	DirectX::SimpleMath::Vector2(20.0f,900.0f),
	DirectX::SimpleMath::Vector2(1900.0f - BOOST_BAR_WIDTH,900.0f)
};


//�R���X�g���N�^
PlaySceneUI::PlaySceneUI()
	: m_hpBarPos{},
	m_timeSpriteOneRect{},
	m_timeSpriteTenRect{},
	m_pTimeSpriteOne(nullptr),
	m_pTimeSpriteTen(nullptr),
	m_winSpritePos{}
{
}

//�f�X�g���N�^
PlaySceneUI::~PlaySceneUI()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_pHPBar[i].reset();
		m_pHPBar[i] = nullptr;
		m_pHPBarBack[i].reset();
		m_pHPBarBack[i] = nullptr;
		m_pWinSprite[i].reset();
		m_pWinSprite[i] = nullptr;
	}

	m_pTimeSpriteOne.reset();
	m_pTimeSpriteTen.reset();
}

/////////////////////
//������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
/////////////////////
void PlaySceneUI::Initialize()
{
	//�摜�̓ǂݍ���
	PlaySceneUI::Load();

	//�����摜�̍��W�ݒ�
	m_winSpritePos = DirectX::SimpleMath::Vector2(640.0f, 300.0f);

	for (int i = 0;i < PLAYER_NUM;i++)
	{
		//�̗̓o�[�̐؂���ʒu�ݒ�
		m_hpBarRect[i].top = 0;
		m_hpBarRect[i].bottom = static_cast<LONG>(HP_BAR_HEIGHT);
		m_hpBarRect[i].left = 0;
		m_hpBarRect[i].right = static_cast<LONG>(HP_BAR_WIDTH);
		//�̗̓o�[�̍��W�ݒ�
		m_hpBarPos[i] = HP_BAR_POS[i];

		//�u�[�X�g�e�ʃo�[�̐؂���ʒu�ݒ�
		m_boostBarRect[i].top = 0;
		m_boostBarRect[i].bottom = static_cast<LONG>(BOOST_BAR_HEIGHT);
		m_boostBarRect[i].left = 0;
		m_boostBarRect[i].right = static_cast<LONG>(BOOST_BAR_WIDTH);
		//�u�[�X�g�e�ʃo�[�̍��W�ݒ�
		m_boostBarPos[i] = BOOST_BAR_POS[i];

		for (int j = 0; j < WIN_NUM; j++)
		{
			//���E���h�擾�{���̉摜�̐؂���ʒu�ݒ�
			m_winNumSpriteRect[i][j].top = 0;
			m_winNumSpriteRect[i][j].bottom = static_cast<LONG>(WIN_NUM_SPRITE_HEIGHT);
			m_winNumSpriteRect[i][j].left = 0;
			m_winNumSpriteRect[i][j].right = static_cast<LONG>(WIN_NUM_SPRITE_WIDTH * 0.5);

		}

		//���E���h�擾�{���̉摜�̍��W�ݒ�
		//�v���C���[1�p
		m_winNumSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_1)][i].y = 170.0f;
		m_winNumSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_1)][i].x = 70.0f + ((WIN_NUM_SPRITE_WIDTH * 0.5f +10.0f) * i);
		//�v���C���[2�p
		m_winNumSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_2)][i].y = 170.0f;
		m_winNumSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_2)][i].x = 1920.0f - ((WIN_NUM_SPRITE_WIDTH * 0.5f + 10.0f) * (i + 1)) - 70.0f;


	}

}



/////////////////////
//�X�V
//�����F�Ȃ�
//�߂�l�F�Ȃ�
/////////////////////
void PlaySceneUI::Update()
{
	//UI�̉摜�̍��W�ݒ�
	for (int i = 0; i < static_cast<int>(PlayScene::eROUND::ROUND_NUM); i++)
	{
		m_pRoundSprite[i]->Update(COUNT_DOWN_SPRITE_POS);
	}
	m_pFightSprite->Update(COUNT_DOWN_SPRITE_POS);
	m_pTimeUpSprite->Update(COUNT_DOWN_SPRITE_POS);
	m_pDrawSprite->Update(COUNT_DOWN_SPRITE_POS);

	//�̗̓o�[�̐؂���ʒu�̍X�V
	m_hpBarRect[static_cast<int>(ePLAYER_ID::PLAYER_1)].left = static_cast<LONG>(
		(HP_BAR_WIDTH /m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetMaxHP()) *
		(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetMaxHP() - m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP()));
	m_hpBarPos[static_cast<int>(ePLAYER_ID::PLAYER_1)].x = m_hpBarRect[static_cast<int>(ePLAYER_ID::PLAYER_1)].left + HP_BAR_MARGIN;


	m_hpBarRect[static_cast<int>(ePLAYER_ID::PLAYER_2)].right = static_cast<LONG>(HP_BAR_WIDTH -
		((HP_BAR_WIDTH / m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetMaxHP()) *
			(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetMaxHP() -
				m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())));

	//�u�[�X�g�e�ʃo�[�̐؂���ʒu�̍X�V
	m_boostBarRect[static_cast<int>(ePLAYER_ID::PLAYER_1)].left = static_cast<LONG>(
		(BOOST_BAR_WIDTH / m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetMaxBoostCap()) *
		(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetMaxBoostCap() - 
			m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetBoostCap()));
	m_boostBarPos[static_cast<int>(ePLAYER_ID::PLAYER_1)].x = m_boostBarRect[static_cast<int>(ePLAYER_ID::PLAYER_1)].left + HP_BAR_MARGIN;

	m_boostBarRect[static_cast<int>(ePLAYER_ID::PLAYER_2)].right = static_cast<LONG>(BOOST_BAR_WIDTH -
		((BOOST_BAR_WIDTH / m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetMaxBoostCap()) *
			(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetMaxBoostCap() -
				m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetBoostCap())));

	//�����{���̉摜�̐؂���ʒu�̍X�V
	//�v���C���[�P
	for (int i = 0; i < m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)); i++)
	{
		if (m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) > 0)
		{
			m_winNumSpriteRect[static_cast<int>(ePLAYER_ID::PLAYER_1)][m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) - 1].left = static_cast<LONG>(WIN_NUM_SPRITE_WIDTH * 0.5);
			m_winNumSpriteRect[static_cast<int>(ePLAYER_ID::PLAYER_1)][m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) - 1].right = static_cast<LONG>(WIN_NUM_SPRITE_WIDTH);
		}
	}
	//�v���C���[2
	for (int i = 0; i < m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)); i++)
	{
		if (m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) > 0)
		{
			m_winNumSpriteRect[static_cast<int>(ePLAYER_ID::PLAYER_2)][m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) - 1].left = static_cast<LONG>(WIN_NUM_SPRITE_WIDTH * 0.5);
			m_winNumSpriteRect[static_cast<int>(ePLAYER_ID::PLAYER_2)][m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) - 1].right = static_cast<LONG>(WIN_NUM_SPRITE_WIDTH);
		}
	}

	//����̉摜��Y���W�X�V
	//�v���C���[1�p
	switch (CharacterFactory::m_player1Chara)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			m_overHeadSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_1)].y =
				((m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetPos().y - 0.5f) * -1) * 260.0f;
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			m_overHeadSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_1)].y =
				((m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetPos().y - 1.5f) * -1) * 260.0f;
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			m_overHeadSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_1)].y =
				((m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetPos().y - 2.0f) * -1) * 260.0f;
			break;
		}

	default:
		break;
	}
	//�v���C���[2�p
	switch (CharacterFactory::m_player2Chara)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			m_overHeadSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_2)].y =
				((m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetPos().y - 0.5f) * -1) * 260.0f;
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			m_overHeadSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_2)].y =
				((m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetPos().y - 1.5f) * -1) * 260.0f;
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			m_overHeadSpritePos[static_cast<int>(ePLAYER_ID::PLAYER_2)].y =
				((m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetPos().y - 2.0f) * -1) * 260.0f;
			break;
		}

		default:
			break;
	}


	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//�̗̓o�[�̍X�V	
		m_pHPBar[i]->Update(m_hpBarPos[i], m_hpBarRect[i]);
		m_pHPBarDanger[i]->Update(m_hpBarPos[i], m_hpBarRect[i]);
		m_pHPBarBack[i]->Update(HP_BAR_POS[i].x - 10.0f, HP_BAR_POS[i].y - 10.0f);
		//�u�[�X�g�e�ʃo�[�̍X�V
		m_pBoostBar[i]->Update(m_boostBarPos[i], m_boostBarRect[i]);
		m_pBoostBack[i]->Update(BOOST_BAR_POS[i].x - 10.0f, BOOST_BAR_POS[i].y - 10.0f);

		//����̉摜�̍X�V
		m_overHeadSpritePos[i].x = 960.0f - 50.0f + (m_pPlayScene->GetPlayer(i))->GetPos().x * 230.0f;
		m_pOverHeadSprite[i]->Update(m_overHeadSpritePos[i]);

		//�����{���̉摜�̍X�V
		for (int j = 0; j < WIN_NUM; j++)
		{
			m_pWinNumSprtie[i][j]->Update(m_winNumSpritePos[i][j], m_winNumSpriteRect[i][j]);
		}

		//���U���g�̏����摜�̍X�V
		if (m_pPlayScene->GetPlaySceneState() == PlayScene::ePLAY_SCENE_STATE::RESULT)
		{
			if (m_pWinSprite[i] != nullptr)
				m_pWinSprite[i]->Update(m_winSpritePos);
		}

	}

	//�������Ԃ̉摜�̐؂���ʒu�̐ݒ�
	m_timeSpriteOneRect.top = 0;
	m_timeSpriteOneRect.bottom = static_cast<LONG>(PlaySceneUI::TIME_SPRITE_HEIGHT);
	m_timeSpriteOneRect.left = static_cast<LONG>(PlaySceneUI::TIME_SPRITE_WIDTH * (static_cast<int>(m_pPlayScene->GetTime()) % 10));
	m_timeSpriteOneRect.right = m_timeSpriteOneRect.left + static_cast<LONG>(PlaySceneUI::TIME_SPRITE_WIDTH);

	m_timeSpriteTenRect.top = 0;
	m_timeSpriteTenRect.left = static_cast<LONG>(PlaySceneUI::TIME_SPRITE_WIDTH * (static_cast<int>(m_pPlayScene->GetTime()) / 10));
	m_timeSpriteTenRect.bottom = static_cast<LONG>(PlaySceneUI::TIME_SPRITE_HEIGHT);
	m_timeSpriteTenRect.right = m_timeSpriteTenRect.left + static_cast<LONG>(PlaySceneUI::TIME_SPRITE_WIDTH);

	m_pTimeSpriteOne->Update(PlaySceneUI::TIME_SPRITE_POS_X, 0.0f, m_timeSpriteOneRect);
	m_pTimeSpriteTen->Update(PlaySceneUI::TIME_SPRITE_POS_X - PlaySceneUI::TIME_SPRITE_WIDTH, 0.0f, m_timeSpriteTenRect);


}

/////////////////////
//�`��
//�����F�Ȃ�
//�߂�l�F�Ȃ�
/////////////////////
void PlaySceneUI::Render()
{
	//�v���C���[�P�̏����摜
	if (m_pPlayScene->GetPlaySceneState() == PlayScene::ePLAY_SCENE_STATE::RESULT &&
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() >
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())
	{
		m_pWinSprite[static_cast<int>(ePLAYER_ID::PLAYER_1)]->Draw(true);
	}

	//�v���C���[2�̏����摜
	else if (m_pPlayScene->GetPlaySceneState() == PlayScene::ePLAY_SCENE_STATE::RESULT &&
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP() >
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP())
	{
		m_pWinSprite[static_cast<int>(ePLAYER_ID::PLAYER_2)]->Draw(true);
	}

	//���������摜
	else if (m_pPlayScene->GetPlaySceneState() == PlayScene::ePLAY_SCENE_STATE::RESULT &&
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() ==
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())
	{
		m_pDrawSprite->Draw(true);
	}

	if (m_pPlayScene->GetIsResult() == false)
	{
		//�̗̓o�[�A�u�[�X�g�e�ʃo�[�̕`��
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			//�w�i
			m_pHPBarBack[i]->Draw();
			m_pBoostBack[i]->Draw();

			//�{��
			if (m_pPlayScene->GetPlayer(i)->GetHP() > m_pPlayScene->GetPlayer(i)->GetMaxHP() * 0.3f)
				m_pHPBar[i]->Draw(false, true);
			else m_pHPBarDanger[i]->Draw(false, true);

			m_pBoostBar[i]->Draw(false, true);

			//�����{���̉摜�̕`��
			for (int j = 0; j < WIN_NUM; j++)
			{
				m_pWinNumSprtie[i][j]->Draw(false, true);
			}
		}

		//����̉摜�̕`��
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			//����̉摜
			m_pOverHeadSprite[i]->Draw(true);
		}


		//�������Ԃ̉摜
		m_pTimeSpriteOne->Draw(true, true);
		m_pTimeSpriteTen->Draw(true, true);

		//�J�E���g�_�E���̉摜
		if (m_pPlayScene->GetPlaySceneState() == PlayScene::ePLAY_SCENE_STATE::COUNT_DOWN)
		{
			if (m_pPlayScene->GetCountDownTimer() <= COUNT_DOWN_TIME / 2)
			{
				//���݂̃��E���h���ɂ���ĕ\������摜��؂�ւ���
				switch (m_pPlayScene->GetNowRound())
				{
					case PlayScene::eROUND::ROUND_1:
					{
						m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_1)]->Draw(true);

						break;
					}
					case PlayScene::eROUND::ROUND_2:
					{
						m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_2)]->Draw(true);

						break;
					}

					case PlayScene::eROUND::ROUND_3:
					{
						m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_3)]->Draw(true);
						break;
					}

					default:
						break;
				}

			}
			else
			{
				m_pFightSprite->Draw(true);
			}
		}
	}
	else
	{
		for (int i = 0; i < PLAYER_NUM; i++)
		{
			if (m_pWinSprite[i] != nullptr)
				m_pWinSprite[i]->Update(m_winSpritePos.x + 600.0f, m_winSpritePos.y - 300.0f);
		}

		m_pPushSpaceResult->Update(PUSH_SPACE_RESULT_POS);
		m_pPushSpaceResult->Draw(true);
	}

	//�^�C���A�b�v�̉摜
	if (m_pPlayScene->GetPlaySceneState() == PlayScene::ePLAY_SCENE_STATE::TIME_UP)
	{
		m_pTimeUpSprite->Draw(true);
	}

}

/////////////////////
//�I������
//�����F�Ȃ�
//�߂�l�F�Ȃ�
/////////////////////
void PlaySceneUI::Finalize()
{
	m_pPushSpaceResult->Reset();


	for (int i = 0; i < PLAYER_NUM; i++)
	{
		m_pHPBar[i]->Reset();
		m_pHPBar[i].reset();

		m_pHPBarDanger[i]->Reset();
		m_pHPBarDanger[i].reset();


		m_pHPBarBack[i]->Reset();
		m_pHPBarBack[i].reset();

		m_pWinSprite[i]->Reset();
		m_pWinSprite[i].reset();

		for (int j = 0; j < WIN_NUM; j++)
		{
			m_pWinNumSprtie[i][j]->Reset();
			m_pWinNumSprtie[i][j].reset();
		}


		m_pOverHeadSprite[i]->Reset();
		m_pOverHeadSprite[i].reset();

	}
	for (int i = 0; i < static_cast<int>(PlayScene::eROUND::ROUND_NUM); i++)
	{
		m_pRoundSprite[i]->Reset();
		m_pRoundSprite[i].reset();
	}
	m_pFightSprite->Reset();
	m_pFightSprite.reset();

	m_pTimeUpSprite->Reset();
	m_pTimeUpSprite.reset();

	m_pDrawSprite->Reset();
	m_pDrawSprite.reset();

	m_pTimeSpriteOne->Reset();
	m_pTimeSpriteOne.reset();

	m_pTimeSpriteTen->Reset();
	m_pTimeSpriteTen.reset();


}


/////////////////////
//�摜�̓ǂݍ���
//�����F�Ȃ�
//�߂�l�F�Ȃ�
/////////////////////
void PlaySceneUI::Load()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//�����摜�̓ǂݍ���
		m_pWinSprite[i] = std::make_unique<Sprite2D>();

		//�̗̓o�[�̔w�i�ǂݍ���
		m_pHPBarBack[i] = std::make_unique<Sprite2D>();
		m_pHPBarBack[i]->Create(L"Resources/Textures/HPBar.jpg");

		//�u�[�X�g�e�ʃo�[�̔w�i�ǂݍ���
		m_pBoostBack[i] = std::make_unique<Sprite2D>();
		m_pBoostBack[i]->Create(L"Resources/Textures/BoostBar_Gray.jpg");

		//�̗̓o�[�̓ǂݍ���
		m_pHPBar[i] = std::make_unique<Sprite2D>();
		m_pHPBar[i]->Create(L"Resources/Textures/HPBar.png");
		//�댯��Ԃ̗̑̓o�[�̓ǂݍ���
		m_pHPBarDanger[i] = std::make_unique<Sprite2D>();
		m_pHPBarDanger[i]->Create(L"Resources/Textures/HPBar_Red.jpg");

		//�u�[�X�g�e�ʃo�[�̓ǂݍ���
		m_pBoostBar[i] = std::make_unique<Sprite2D>();
		m_pBoostBar[i]->Create(L"Resources/Textures/BoostBar.jpg");

		//�����{���̉摜�̕`��
		for (int j = 0; j < WIN_NUM; j++)
		{
			m_pWinNumSprtie[i][j] = std::make_unique<Sprite2D>();
			m_pWinNumSprtie[i][j]->Create(L"Resources/Textures/winNum.png");


		}

		//�v���C���[�̓���̉摜�ǂݍ���
		m_pOverHeadSprite[i] = std::make_unique<Sprite2D>();
	}

	//�v���C���[���Ƃ̏����摜�ǂݍ���
	m_pWinSprite[static_cast<int>(ePLAYER_ID::PLAYER_1)]->Create(L"Resources/Textures/p1win.png");
	m_pWinSprite[static_cast<int>(ePLAYER_ID::PLAYER_2)]->Create(L"Resources/Textures/p2win.png");

	//�v���C���[���Ƃ̓���̉摜�ǂݍ���
	m_pOverHeadSprite[static_cast<int>(ePLAYER_ID::PLAYER_1)]->Create(L"Resources/Textures/p1Icon.png");
	m_pOverHeadSprite[static_cast<int>(ePLAYER_ID::PLAYER_2)]->Create(L"Resources/Textures/p2Icon.png");


	//���E���h���̉摜�̓ǂݍ���
	for (int i = 0; i < static_cast<int>(PlayScene::eROUND::ROUND_NUM); i++)
	{
		m_pRoundSprite[i] = std::make_unique<Sprite2D>();
	}
	m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_1)]->Create(L"Resources/Textures/Round1.png");
	m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_2)]->Create(L"Resources/Textures/Round2.png");
	m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_3)]->Create(L"Resources/Textures/Round3.png");



	//Fight�摜�̓ǂݍ���
	m_pFightSprite = std::make_unique<Sprite2D>();
	m_pFightSprite->Create(L"Resources/Textures/Fight.png");

	//�^�C���A�b�v�摜�̓ǂݍ���
	m_pTimeUpSprite = std::make_unique<Sprite2D>();
	m_pTimeUpSprite->Create(L"Resources/Textures/TimeUp.png");

	//���������摜�̓ǂݍ���
	m_pDrawSprite = std::make_unique<Sprite2D>();
	m_pDrawSprite->Create(L"Resources/Textures/Draw.png");

	//�������Ԃ̉摜�̓ǂݍ���
	m_pTimeSpriteOne = std::make_unique<Sprite2D>();
	m_pTimeSpriteOne->Create(L"Resources/Textures/Number_mini.png");
	m_pTimeSpriteTen = std::make_unique<Sprite2D>();
	m_pTimeSpriteTen->Create(L"Resources/Textures/Number_mini.png");

	//pushSpace�̉摜�ǂݍ���
	m_pPushSpaceResult = std::make_unique<Sprite2D>();
	m_pPushSpaceResult->Create(L"Resources/Textures/pushSpace_result.png");

}


/////////////////////
//���Z�b�g
//�����F�Ȃ�
//�߂�l�F�Ȃ�
/////////////////////
void PlaySceneUI::Reset()
{
	for (int i = 0; i < PLAYER_NUM; i++)
	{
		//�̗̓o�[�̍��W�̃��Z�b�g
		m_hpBarPos[i] = HP_BAR_POS[i];
		//�u�[�X�g�e�ʃo�[�̃��Z�b�g
		m_boostBarPos[i] = BOOST_BAR_POS[i];
	}

}
