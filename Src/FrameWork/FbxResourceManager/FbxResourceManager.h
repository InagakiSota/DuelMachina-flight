///////////////////////////////////
//Fbx�̃��\�[�X�Ǘ��N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2021�N3��30��
///////////////////////////////////

#pragma once

class FbxModel;
enum class eCHARACTER_ID :int;

#include "DeviceResources.h"

class FbxResourceManager
{
public:
	//�C���X�^���X�̎擾
	static FbxResourceManager* GetInstance();
	//�C���X�^���X�̉��
	static void ReleaseInstance();

	//���[�h
	void Load(DX::DeviceResources* pDeviceResources, HWND window);
	//���f���̃|�C���^�擾
	FbxModel* GetModel(const eCHARACTER_ID& characterID);
	//�V�[���h�̃��f���̃|�C���^�擾
	FbxModel* GetShieldModel();
	//�I������
	void Finalize();

private:
	//���g�̃C���X�^���X
	static FbxResourceManager* m_pMyInstance;

	//�R���X�g���N�^
	FbxResourceManager();
	//�f�X�g���N�^
	~FbxResourceManager();

	//�L�����N�^�[�P�̃��f��
	FbxModel* m_pCharacter1Model;
	//�L�����N�^�[�Q�̃��f��
	FbxModel* m_pCharacter2Model;
	//�L�����N�^�[�R�̃��f��
	FbxModel* m_pCharacter3Model;
	//�V�[���h�̃��f��
	FbxModel* m_pShieldModel;
};
