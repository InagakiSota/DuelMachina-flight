///////////////////////////////////
//�v���C�V�[���̃��C���X�e�[�g
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////
#include "pch.h"
#include "PlaySceneMainState.h"
#include "Adx2.h"
#include "CueSheet_0.h"
#include "../Character/CharacterBase.h"
#include "../../PlayerID.h"
#include "../AttackManager/AttackManager.h"


 //�J�E���g�_�E���̎���
const float PlaySceneMainState::COUNT_DOWN_TIME = 3.0f;
//�������Ԃ̍ő�l
const float PlaySceneMainState::TIME_MAX = 60.0f;
//�^�C���A�b�v�V�[���̐�������
const float PlaySceneMainState::TIME_UP_TIME = 3.0f;
//���E���h�؂�ւ����̎���
const float PlaySceneMainState::ROUND_CHANGE_TIME = 1.0f;


//�R���X�g���N�^
PlaySceneMainState::PlaySceneMainState()
	:m_pPlayScene(nullptr)
{
}

//�f�X�g���N�^
PlaySceneMainState::~PlaySceneMainState()
{
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneMainState::Update(DX::StepTimer const& timer)
{
	switch (m_pPlayScene->GetPlaySceneState())
	{
		//�J�E���g�_�E��
		case PlayScene::ePLAY_SCENE_STATE::COUNT_DOWN:
		{
			CountDown(timer);
			break;
		}
		//���C��
		case PlayScene::ePLAY_SCENE_STATE::MAIN:
		{
			Main(timer);
			break;
		}

		case PlayScene::ePLAY_SCENE_STATE::TIME_UP:
		{
			TimeUp(timer);
			break;
		}


		//���U���g
		case PlayScene::ePLAY_SCENE_STATE::RESULT:
		{
			Result(timer);
			break;
		}
		default:
			break;
	}

}

///////////////////////////
//�J�E���g�_�E��
//����:�X�e�b�v�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneMainState::CountDown(DX::StepTimer const& timer)
{
	for (int i = 0; i < PlayScene::PLAYER_NUM; i++)
	{
		//�v���C���[�̏���
		m_pPlayScene->GetPlayer(i)->Ready(timer);
	}
	//�G�̍��W�̎擾
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->SetEnemyPos(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetPos());
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->SetEnemyPos(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetPos());

	//�v���C���[���m�̑̂̓����蔻��
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->HitEnemyBody(
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetBodyCollBox(),
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHeadCollBox());
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->HitEnemyBody(
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetBodyCollBox(),
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHeadCollBox());

	//�J�E���g�_�E���̃^�C�}�[�����Z
	m_pPlayScene->SetCountDownTimer(m_pPlayScene->GetCountDownTimer() + static_cast<float>(timer.GetElapsedSeconds()));
	//��莞�ԂɂȂ����烁�C����ԂɑJ��
	if (m_pPlayScene->GetCountDownTimer() >= COUNT_DOWN_TIME)
	{
		m_pPlayScene->SetPlaySceneState(PlayScene::ePLAY_SCENE_STATE::MAIN);


		m_pPlayScene->SetCountDownTimer(0.0f);
	}
}

///////////////////////////
//���C��
//����:�X�e�b�v�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneMainState::Main(DX::StepTimer const& timer)
{
	//�U���̃}�l�[�W���[�̍X�V
	AttackManager::GetInstance()->Update();

	//���Ԃ����炷
	m_pPlayScene->SetTime(m_pPlayScene->GetTime() - static_cast<float>(timer.GetElapsedSeconds()));
	//m_time -= static_cast<float>(timer.GetElapsedSeconds());
	//���Ԃ��[���ɂȂ�����^�C���A�b�v�ɑJ��
	if (m_pPlayScene->GetTime() <= 0)
	{
		//m_playSceneState = ePLAY_SCENE_STATE::TIME_UP;
		m_pPlayScene->SetPlaySceneState(PlayScene::ePLAY_SCENE_STATE::TIME_UP);
		//�v���C���[�P�ƂQ�̏������𑝂₷
		if (m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() ==
			m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())
		{
			m_pPlayScene->SetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1),
				m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) + 1);
			m_pPlayScene->SetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2),
				m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) + 1);
		}
	}

	for (int i = 0; i < PlayScene::PLAYER_NUM; i++)
	{
		//�v���C���[�̍X�V
		//m_pPlayScene->GetPlayer(i)->Update(timer);
	}
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->Update(timer);
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->AI();

	//�G�̍��W�̎擾
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->
		SetEnemyPos(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetPos());
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->
		SetEnemyPos(m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetPos());
	//�v���C���[���m�̑̂̓����蔻��
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->HitEnemyBody(
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetBodyCollBox(),
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHeadCollBox());
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->HitEnemyBody(
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetBodyCollBox(),
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHeadCollBox());

	//�v���C���[�P�̗̑͂��[���ɂȂ����烊�U���g�ɑJ��
	if (m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() <= 0)
	{
		//�v���C���[�Q�̏������𑝂₷
		m_pPlayScene->SetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2),
			m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) + 1);
		m_pPlayScene->SetPlaySceneState(PlayScene::ePLAY_SCENE_STATE::RESULT);

	}
	//�v���C���[�Q�̗̑͂��[���ɂȂ����烊�U���g�ɑJ��
	if (m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP() <= 0)
	{
		//�v���C���[�P�̏������𑝂₷
		m_pPlayScene->SetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1),
			m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) + 1);
		m_pPlayScene->SetPlaySceneState(PlayScene::ePLAY_SCENE_STATE::RESULT);
	}
}

///////////////////////////
//�^�C���A�b�v
//����:�X�e�b�v�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneMainState::TimeUp(DX::StepTimer const& timer)
{
	//�J�E���g�_�E���̃^�C�}�[�����Z
	m_pPlayScene->SetCountDownTimer(m_pPlayScene->GetCountDownTimer() + static_cast<float>(timer.GetElapsedSeconds()));
	if (m_pPlayScene->GetCountDownTimer() >= PlaySceneMainState::TIME_UP_TIME)
	{
		m_pPlayScene->SetPlaySceneState(PlayScene::ePLAY_SCENE_STATE::RESULT);

		//�v���C���[�P�̗̑͂��v���C���[�Q��葽����΃v���C���[�P�̏������𑝂₷
		if (m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() >
			m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())
		{
			m_pPlayScene->SetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1),
				m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) + 1);
		}
		//�v���C���[�Q�̗̑͂��v���C���[�P��葽����΃v���C���[�Q�̏������𑝂₷
		if (m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() <
			m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())
		{
			m_pPlayScene->SetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2),
				m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) + 1);
		}

		m_pPlayScene->SetCountDownTimer(0.0f);
	}

}

///////////////////////////
//���U���g
//����:�X�e�b�v�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneMainState::Result(DX::StepTimer const& timer)
{
	//�v���C���[�P�̗̑͂��v���C���[�Q��葽����΃v���C���[�P�𓮂���
	if (m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHP() >
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHP())
	{
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->Ready(timer);
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->SetCharaState(eCHARACTER_STATE::LOSE);
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->Lose(timer);
	}
	//�v���C���[�Q�̗̑͂��v���C���[�P��葽����΃v���C���[�Q�𓮂���
	else
	{
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->Ready(timer);
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->SetCharaState(eCHARACTER_STATE::LOSE);
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->Lose(timer);
	}

	//�v���C���[���m�̑̂̓����蔻��
	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->HitEnemyBody(
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetBodyCollBox(),
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->GetHeadCollBox());

	m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_2))->HitEnemyBody(
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetBodyCollBox(),
		m_pPlayScene->GetPlayer(static_cast<int>(ePLAYER_ID::PLAYER_1))->GetHeadCollBox());

	//�J�E���g�_�E���̃^�C�}�[�����Z
	m_pPlayScene->SetCountDownTimer(m_pPlayScene->GetCountDownTimer() + static_cast<float>(timer.GetElapsedSeconds()));
	if (m_pPlayScene->GetCountDownTimer() >= PlaySceneMainState::ROUND_CHANGE_TIME || m_pPlayScene->GetKeyTracker()->IsKeyPressed(DirectX::Keyboard::Keys::Space))
	{
		m_pPlayScene->SetSceneState(eSCENE_STATE::FADE_OUT);
	}

}
