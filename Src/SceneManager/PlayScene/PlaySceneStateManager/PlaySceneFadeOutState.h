///////////////////////////////////
//�v���C�V�[���̃t�F�[�h�A�E�g�X�e�[�g
//�쐬�ҁF2021�N5��10��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#pragma once

#include "../PlayScene.h"

class PlaySceneFadeOutState
{
public:
	//�R���X�g���N�^
	PlaySceneFadeOutState();
	//�f�X�g���N�^
	~PlaySceneFadeOutState();

	//�X�V
	void Update(DX::StepTimer const& timer);

	//�v���C�V�[���̃|�C���^�擾
	void SetPlayScene(PlayScene* pPlayScene)
	{
		m_pPlayScene = pPlayScene;
	}


private:
	//�������邽�߂̎擾�{��
	static const int WIN_NUM;

	//�v���C�V�[���̃|�C���^
	PlayScene* m_pPlayScene;


};

