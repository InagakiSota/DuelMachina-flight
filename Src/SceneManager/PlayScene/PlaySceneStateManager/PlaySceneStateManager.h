///////////////////////////////////
//�v���C�V�[���̃X�e�[�g�}�l�[�W���[
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#pragma once

#include "../../SceneBase.h"
#include <StepTimer.h>

#include "../PlayScene.h"

class PlaySceneFadeInState;
class PlaySceneFadeOutState;
class PlaySceneMainState;

class PlaySceneStateManager
{
public:
	//�R���X�g���N�^
	PlaySceneStateManager();
	//�f�X�g���N�^
	~PlaySceneStateManager();

	//������
	void Initialize(PlayScene* pPlayScene);
	//�X�V
	void Update(DX::StepTimer const& timer, const eSCENE_STATE& sceneState);

private:

	//�v���C�V�[���̊e�X�e�[�g�̃N���X
	//�t�F�[�h�C��
	std::unique_ptr<PlaySceneFadeInState> m_pPlaySceneFadeInState;
	//�t�F�[�h�A�E�g
	std::unique_ptr<PlaySceneFadeOutState> m_pPlaySceneFadeOutState;
	//���C��
	std::unique_ptr<PlaySceneMainState> m_pPlaySceneMainState;


};

