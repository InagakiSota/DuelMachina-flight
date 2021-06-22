///////////////////////////////////
//�V�[���}�l�[�W���[�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////

#pragma once

class SceneBase;

#include "DeviceResources.h"
#include "StepTimer.h"
#include <CommonStates.h>

//�e�V�[����ID
enum class eSCENE_ID
{
	NONE_SCENE = -1,
	TITLE_SCENE,							//�^�C�g��
	CHARA_SELECT_SCENE,						//�L�����N�^�[�Z���N�g
	PLAY_SCENE,								//�v���C
	RESULT_SCENE,							//���U���g

	OVER_ID,
};

class SceneManager
{
public:
	//������
	void Initialize();
	//�X�V
	void Update(DX::StepTimer const& timer);
	//�`��
	void Render();
	//�I������
	void Finalize();
		
	//���݂̃V�[���̎擾
	eSCENE_ID GetScene();	
	//�V�[���̐ݒ�
	void SetScene(const eSCENE_ID scene);

	//�C���X�^���X�̎擾
	static SceneManager* GetInstance();
	//�C���X�^���X�̉��
	static void ReleaseInstance();


private:
	//�V���O���g����
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();

	//�V�[���̃|�C���^
	std::unique_ptr<SceneBase> m_pScene;
	//���݂̃V�[����ID
	eSCENE_ID m_sceneId;
	//���g�̃C���X�^���X
	static SceneManager* pMyInstance;

	//�f�o�C�X
	DX::DeviceResources* m_pDeviceResources;

	DirectX::CommonStates* m_pStates;

	//�E�C���h�E
	HWND m_window;
};	

