///////////////////////////////////
//�V�[���}�l�[�W���[�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////
#include "pch.h"
#include "SceneManager.h"
#include "TitleScene\TitleScene.h"
#include "PlayScene\PlayScene.h"
#include "CharaSelectScene\CharaSelectScene.h"
#include "ResultScene\ResultScene.h"

SceneManager* SceneManager::pMyInstance = nullptr;

//�R���X�g���N�^
SceneManager::SceneManager()
	:m_pScene(nullptr),
	m_sceneId(eSCENE_ID::PLAY_SCENE)
{

}

//�f�X�g���N�^
SceneManager::~SceneManager()
{
	Finalize();
	if (m_pScene != nullptr)
	{
		m_pScene.reset();
	}
	m_pStates = nullptr;
}

///////////////////////////
//������
//����:�f�o�C�X���\�[�X�̃|�C���^,�E�C���h�E
//�߂�l:�Ȃ�
//////////////////////////
void SceneManager::Initialize()
{
	//m_pDeviceResources = pDeviceResources;
	//m_window = window;
	//m_pStates = pStates;
	//if(m_pScene != nullptr)
	//	m_pScene->Initialize();
}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneManager::Update(DX::StepTimer const& timer)
{
	if (m_pScene != nullptr)
		m_pScene->Update(timer);

}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneManager::Render()
{
	if (m_pScene != nullptr)
		m_pScene->Render();

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneManager::Finalize()
{
	if (m_pScene != nullptr)
		m_pScene->Finalize();

	m_pScene.reset();

}

///////////////////////////
//���݂̃V�[���̎擾
//����:�Ȃ�
//�߂�l:���݂̃V�[����ID
//////////////////////////
eSCENE_ID SceneManager::GetScene()
{
	return m_sceneId;
}

///////////////////////////
//�V�[���̐ݒ�
//����:�ݒ肵�����V�[����ID
//�߂�l:�Ȃ�
//////////////////////////
void SceneManager::SetScene(const eSCENE_ID scene)
{
	//���݂̃V�[���̏I������
	if (m_pScene != nullptr)
	{
		m_pScene->Finalize();
	}

	m_sceneId = scene;

	m_pScene.reset();

	//�e�V�[���̓ǂݍ���
	switch (m_sceneId)
	{
		//�^�C�g��
		case eSCENE_ID::TITLE_SCENE:
		{
			m_pScene = std::make_unique<TitleScene>();

			break;
		}

		//�L�����N�^�[�Z���N�g
		case eSCENE_ID::CHARA_SELECT_SCENE:
		{
			m_pScene = std::make_unique<CharaSelectScene>();
			break;
		}
			
		//�v���C�V�[��
		case eSCENE_ID::PLAY_SCENE:
		{
			m_pScene = std::make_unique<PlayScene>();

			break;
		}

		//���U���g
		case eSCENE_ID::RESULT_SCENE:
		{
			m_pScene = std::make_unique<ResultScene>();
			break;
		}
		default:
			break;
	}
	//�V�[���̏�����
	if (m_pScene != nullptr)
		m_pScene->Initialize();
}

///////////////////////////
//�C���X�^���X�̎擾
//����:�Ȃ�
//�߂�l:���g�̃|�C���^
//////////////////////////
SceneManager * SceneManager::GetInstance()
{
	if (pMyInstance == nullptr)
	{
		pMyInstance = new SceneManager();
	}

	return pMyInstance;
}

///////////////////////////
//�C���X�^���X�̉��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneManager::ReleaseInstance()
{
	if (pMyInstance != nullptr)
	{
		delete pMyInstance;
	}
	pMyInstance = nullptr;
}


