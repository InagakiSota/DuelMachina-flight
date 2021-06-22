///////////////////////////////////
//�v���C�V�[���̃t�F�[�h�C���X�e�[�g
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#pragma once

#include "../PlayScene.h"

class PlaySceneFadeInState
{
public:
	//�R���X�g���N�^
	PlaySceneFadeInState();
	//�f�X�g���N�^
	~PlaySceneFadeInState();

	//�X�V
	void Update(DX::StepTimer const& timer);

	//�v���C�V�[���̃|�C���^�擾
	void SetPlayScene(PlayScene* pPlayScene)
	{
		m_pPlayScene = pPlayScene;
	}

private:
	//�v���C�V�[���̃|�C���^
	PlayScene* m_pPlayScene;

};

