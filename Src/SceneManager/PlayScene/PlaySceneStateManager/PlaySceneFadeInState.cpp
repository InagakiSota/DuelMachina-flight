///////////////////////////////////
//�v���C�V�[���̃t�F�[�h�C���X�e�[�g
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#include "pch.h"
#include "PlaySceneFadeInState.h"
#include "Adx2.h"
#include "CueSheet_0.h"
#include "Src/SceneManager/PlayScene/Character/CharacterBase.h"

//�R���X�g���N�^
PlaySceneFadeInState::PlaySceneFadeInState()
	:m_pPlayScene(nullptr)
{
}

//�f�X�g���N�^
PlaySceneFadeInState::~PlaySceneFadeInState()
{
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneFadeInState::Update(DX::StepTimer const& timer)
{
	//�t�F�[�h�̃^�C�}�[�����Z����
	m_pPlayScene->SetFadeTimer(m_pPlayScene->GetFadeTimer() - static_cast<float>(timer.GetElapsedSeconds()) * 2.0f);

	if (m_pPlayScene->GetFadeTimer() <= 0.0f)
	{
		//BGM�̍Đ�
		m_pPlayScene->SetSoundID(ADX2::GetInstance().Play(CRI_CUESHEET_0_PLAYSCENE_BGM));
		//���C����ԂɑJ��
		m_pPlayScene->SetSceneState(eSCENE_STATE::MAIN);
	}

	for (int i = 0; i < m_pPlayScene->PLAYER_NUM; i++)
	{

		//�v���C���[�̏���
		m_pPlayScene->GetPlayer(i)->Ready(timer);

	}

}
