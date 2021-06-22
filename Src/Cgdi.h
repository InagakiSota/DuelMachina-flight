///////////////////////////////////
//DirectXTK�ŕ`��̍ۂɕK�v�ȃC���X�^���X���Ǘ�����N���X
//�쐬�ҁF2021�N4��30��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////
#pragma once

#include "DeviceResources.h"
#include <CommonStates.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>

// �ȒP�ɌĂяo����悤�ɒ�`���Ă���
#define gdi Cgdi::GetInstance()

class Cgdi
{
public:

	//�f�X�g���N�^
	virtual ~Cgdi();

	//���g�̃C���X�^���X�̎擾
	static Cgdi* GetInstance();

	//������
	void Initialize(DX::DeviceResources* deviceResources, DirectX::CommonStates* commonStates, float width, float height);

	// �X�N���[���T�C�Y��ݒ肷��֐�
	void SetScreenSize(float width, float height);

	// �X�N���[���T�C�Y���擾����֐�
	void GetScreenSize(float& width, float& height);

	// �f�o�C�X���\�[�X���擾����֐�
	DX::DeviceResources* GetDeviceResources() const 
	{
		return m_deviceResources; 
	}

	// �R�����X�e�[�g���擾����֐�
	DirectX::CommonStates* GetStates() const
	{
		return m_states; 
	}

	// �X�v���C�g�o�b�`���擾����֐�
	DirectX::SpriteBatch* GetSprite() 
	{
		return m_spriteBatch.get();
	}



private:

	// �f�o�C�X���\�[�X�Ǘ��C���X�^���X�ւ̃|�C���^
	DX::DeviceResources* m_deviceResources;

	// �R�����X�e�[�g
	DirectX::CommonStates* m_states;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �X�N���[���T�C�Y
	float m_screenW, m_screenH;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	//�X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// �R���X�g���N�^
	Cgdi();

	void operator=(const Cgdi& obj) = delete;	// ������Z�q�폜
	Cgdi(const Cgdi& obj) = delete;				// �R�s�[�R���X�g���N�^�폜




};
