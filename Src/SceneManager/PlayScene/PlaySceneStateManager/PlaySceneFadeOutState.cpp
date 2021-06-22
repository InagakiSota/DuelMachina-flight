///////////////////////////////////
//�v���C�V�[���̃t�F�[�h�A�E�g�X�e�[�g
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#include "pch.h"
#include "PlaySceneFadeOutState.h"
#include "Adx2.h"
#include "CueSheet_0.h"
#include "../../PlayerID.h"
#include "../../ResultScene/ResultScene.h"

const int PlaySceneFadeOutState::WIN_NUM = 2;

//�R���X�g���N�^
PlaySceneFadeOutState::PlaySceneFadeOutState()
	:m_pPlayScene(nullptr)
{
}

//�f�X�g���N�^
PlaySceneFadeOutState::~PlaySceneFadeOutState()
{
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneFadeOutState::Update(DX::StepTimer const& timer)
{
	//���U���g�ɑJ�ڂ��Ȃ���΂��̂܂܃t�F�[�h�A�E�g
	if (m_pPlayScene->GetIsResult() == false)
	{
		m_pPlayScene->SetFadeTimer(m_pPlayScene->GetFadeTimer() + static_cast<float>(timer.GetElapsedSeconds()) * 2.0f);
	}
	//�t�F�[�h�A�E�g������v���C�V�[���ɖ߂�
	if (m_pPlayScene->GetFadeTimer() >= 1.0f)
	{
		//�ǂ��炩�̃v���C���[���Q�{��������܂ŌJ��Ԃ�
		if (m_pPlayScene->GetPlayerWinNum(static_cast<int>( ePLAYER_ID::PLAYER_1)) < WIN_NUM &&
			m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) < WIN_NUM)
		{
			//���E���h����؂�ւ���
			switch (m_pPlayScene->GetNowRound())
			{
				//���E���h�P
				case PlayScene::eROUND::ROUND_1:
				{
					//���E���h2�ɂ���
					m_pPlayScene->SetNowRound(PlayScene::eROUND::ROUND_2);
					break;

				}
				//���E���h�Q
				case PlayScene::eROUND::ROUND_2:
				{
					//���E���h3�ɂ���
					m_pPlayScene->SetNowRound(PlayScene::eROUND::ROUND_3);
					break;
				}
				default:
					break;
			}
			//���Z�b�g
			m_pPlayScene->Reset();
		}
		//�ǂ��炩�̃v���C���[���Q�{���������烊�U���g�ɑJ��
		else
		{
			m_pPlayScene->SetIsResult(true);

			//�v���C���[�P�������������Ƃɂ���
			if (m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_1)) >= WIN_NUM)
			{
				ResultScene::m_winPlayerID = ePLAYER_ID::PLAYER_1;
			}
			//�v���C���[�Q�������������Ƃɂ���
			else if (m_pPlayScene->GetPlayerWinNum(static_cast<int>(ePLAYER_ID::PLAYER_2)) >= WIN_NUM)
			{
				ResultScene::m_winPlayerID = ePLAYER_ID::PLAYER_2;
			}


		}
		//BGM��~
		ADX2::GetInstance().Stop(m_pPlayScene->GetSoundID());

	}

}
