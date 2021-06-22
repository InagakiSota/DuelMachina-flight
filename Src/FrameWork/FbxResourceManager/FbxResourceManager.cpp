///////////////////////////////////
//Fbx�̃��\�[�X�Ǘ��N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2021�N3��30��
///////////////////////////////////

#include "pch.h"
#include "FbxResourceManager.h"
#include "../FbxModel/FbxModel.h"
#include "../../SceneManager/PlayScene/Character/CharacterID.h"


FbxResourceManager* FbxResourceManager::m_pMyInstance = nullptr;

///////////////////////////
//�C���X�^���X�̎擾
//����:�Ȃ�
//�߂�l:���g�̃|�C���^
//////////////////////////
FbxResourceManager* FbxResourceManager::GetInstance()
{
	if (m_pMyInstance == nullptr)
	{
		m_pMyInstance = new FbxResourceManager();
	}

	return m_pMyInstance;
}

///////////////////////////
//�C���X�^���X�̉��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FbxResourceManager::ReleaseInstance()
{
	if (m_pMyInstance != nullptr)
	{
		delete m_pMyInstance;
	}
	m_pMyInstance = nullptr;
}

///////////////////////////
//���[�h
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FbxResourceManager::Load(DX::DeviceResources* pDeviceResources, HWND window)
{
	//�L�����N�^�[�P�̃��f���ǂݍ���
	m_pCharacter1Model = new FbxModel();
	m_pCharacter1Model->Load(
		window,
		pDeviceResources->GetD3DDevice(),
		pDeviceResources->GetD3DDeviceContext(),
		pDeviceResources->GetRenderTargetView(),
		"Resources/Models/robot1/robot1_animation3.fbx",
		true,
		0
	);

	//�L�����N�^�[�Q�̃��f���ǂݍ���
	m_pCharacter2Model = new FbxModel();
	m_pCharacter2Model->Load(
		window,
		pDeviceResources->GetD3DDevice(),
		pDeviceResources->GetD3DDeviceContext(),
		pDeviceResources->GetRenderTargetView(),
		"Resources/Models/robot2/robot2_animation.fbx",
		true
	);

	//�L�����N�^�[�R�̃��f���ǂݍ���
	m_pCharacter3Model = new FbxModel();
	m_pCharacter3Model->Load(
		window,
		pDeviceResources->GetD3DDevice(),
		pDeviceResources->GetD3DDeviceContext(),
		pDeviceResources->GetRenderTargetView(),
		"Resources/Models/robot3/robot3_animation.fbx",
		true
	);

	//�V�[���h�̃��f���ǂݍ���
	m_pShieldModel = new FbxModel();
	m_pShieldModel->Load(
		window,
		pDeviceResources->GetD3DDevice(),
		pDeviceResources->GetD3DDeviceContext(),
		pDeviceResources->GetRenderTargetView(),
		"Resources/Models/Shield.fbx",
		false
	);

}

///////////////////////////
//���f���̃|�C���^�̎擾
//����:���f����ID
//�߂�l:���f���̃|�C���^
//////////////////////////
FbxModel * FbxResourceManager::GetModel(const eCHARACTER_ID & characterID)
{
	FbxModel* pModel = nullptr;

	switch (characterID)
	{
		//�L�����N�^�[�P
		case eCHARACTER_ID::CHARACTER_1:
		{
			if (m_pCharacter1Model != nullptr)
			{
				pModel = m_pCharacter1Model;
			}
			break;
		}
		//�L�����N�^�[�Q
		case eCHARACTER_ID::CHARACTER_2:
		{
			if (m_pCharacter2Model != nullptr)
			{
				pModel = m_pCharacter2Model;
			}
			break;
		}
		//�L�����N�^�[�R
		case eCHARACTER_ID::CHARACTER_3:
		{
			if (m_pCharacter3Model != nullptr)
			{
				pModel = m_pCharacter3Model;
			}
			break;
		}

		default:
			break;
	}
	return pModel;
}

///////////////////////////
//�V�[���h�̃��f���̎擾
//����:�Ȃ�
//�߂�l:�V�[���h�̃��f���̃|�C���^
//////////////////////////
FbxModel * FbxResourceManager::GetShieldModel()
{
	return m_pShieldModel;
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FbxResourceManager::Finalize()
{
	delete m_pCharacter1Model;
	m_pCharacter1Model = nullptr;

	delete m_pCharacter2Model;
	m_pCharacter2Model = nullptr;

	delete m_pCharacter3Model;
	m_pCharacter3Model = nullptr;

	delete m_pShieldModel;
	m_pShieldModel = nullptr;
}

//�R���X�g���N�^
FbxResourceManager::FbxResourceManager()
	:m_pCharacter1Model(nullptr),
	m_pCharacter2Model(nullptr),
	m_pCharacter3Model(nullptr)
{
}

//�f�X�g���N�^
FbxResourceManager::~FbxResourceManager()
{
	FbxResourceManager::Finalize();
}
