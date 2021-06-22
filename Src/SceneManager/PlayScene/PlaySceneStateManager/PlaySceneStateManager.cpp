///////////////////////////////////
//�v���C�V�[���̃X�e�[�g�}�l�[�W���[
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#include "pch.h"
#include "PlaySceneStateManager.h"

#include "PlaySceneFadeInState.h"
#include "PlaySceneFadeOutState.h"
#include "PlaySceneMainState.h"



PlaySceneStateManager::PlaySceneStateManager()
{
}

PlaySceneStateManager::~PlaySceneStateManager()
{
}

///////////////////////////
//������
//����:�v���C�V�[���̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneStateManager::Initialize(PlayScene* pPlayScene)
{
	//�v���C�V�[���̊e�X�e�[�g�N���X�̓ǂݍ���
	//�t�F�[�h�C��
	m_pPlaySceneFadeInState = std::make_unique<PlaySceneFadeInState>();
	m_pPlaySceneFadeInState->SetPlayScene(pPlayScene);
	//�t�F�[�h�A�E�g
	m_pPlaySceneFadeOutState = std::make_unique<PlaySceneFadeOutState>();
	m_pPlaySceneFadeOutState->SetPlayScene(pPlayScene);
	//���C��
	m_pPlaySceneMainState = std::make_unique<PlaySceneMainState>();
	m_pPlaySceneMainState->SetPlayScene(pPlayScene);

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void PlaySceneStateManager::Update(DX::StepTimer const& timer, const eSCENE_STATE& sceneState)
{
	//�e�X�e�[�g�̃N���X�̍X�V
	switch (sceneState)
	{
		//�t�F�[�h�C��
		case eSCENE_STATE::FADE_IN:
		{
			m_pPlaySceneFadeInState->Update(timer);

			break;
		}
		//�t�F�[�h�A�E�g
		case eSCENE_STATE::FADE_OUT:
		{
			m_pPlaySceneFadeOutState->Update(timer);

			break;
		}

		//���C��
		case eSCENE_STATE::MAIN:
		{
			m_pPlaySceneMainState->Update(timer);

			break;
		}


		default:
			break;
	}
}
