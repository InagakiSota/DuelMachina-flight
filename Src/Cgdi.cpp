///////////////////////////////////
//DirectXTK�ŕ`��̍ۂɕK�v�ȃC���X�^���X���Ǘ�����N���X
//�쐬�ҁF2021�N4��30��
//�쐬���FGT2_04_��_�D��
///////////////////////////////////

#include "pch.h"
#include "Cgdi.h"

// �R���X�g���N�^
Cgdi::Cgdi()
	: m_deviceResources(nullptr), m_screenW(0), m_screenH(0)
{
}

//�f�X�g���N�^
Cgdi::~Cgdi()
{
	m_deviceResources = nullptr;
	m_states = nullptr;

	m_spriteBatch.reset();
}

///////////////////////////
//���g�̃C���X�^���X�̎擾
//����:�Ȃ�
//�߂�l:���g�̃C���X�^���X�̃|�C���^
//////////////////////////
Cgdi* Cgdi::GetInstance()
{
	static Cgdi instance;
	return &instance;
}

///////////////////////////
//������
//����:�f�o�C�X���\�[�X�A��ʂ̕��A����
//�߂�l:�Ȃ�
//////////////////////////
void Cgdi::Initialize(DX::DeviceResources* deviceResources, DirectX::CommonStates* commonStates, float width, float height)
{
	//��ʃT�C�Y�̐ݒ�
	SetScreenSize(width, height);

	assert(m_deviceResources == nullptr);

	m_deviceResources = deviceResources;

	m_states = commonStates;

	auto device = m_deviceResources->GetD3DDevice();
	auto deviceContext = m_deviceResources->GetD3DDeviceContext();

	// �R�����X�e�[�g�̐���
	//m_states = std::make_unique<DirectX::CommonStates>(device);

	//�X�v���C�g�o�b�`�̐���
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);


}

///////////////////////////
//�X�N���[���T�C�Y�̐ݒ�
//����:���A����
//�߂�l:�Ȃ�
//////////////////////////
void Cgdi::SetScreenSize(float width, float height)
{
	m_screenW = width;
	m_screenH = height;
}

///////////////////////////
//�X�N���[���T�C�Y�̎擾
//����:���A����
//�߂�l:�Ȃ�
//////////////////////////
void Cgdi::GetScreenSize(float& width, float& height)
{
	width = m_screenW;
	height = m_screenH;
}
