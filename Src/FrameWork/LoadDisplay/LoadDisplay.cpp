///////////////////////////////////
//���[�h��ʂ̊Ǘ��N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2021�N3��25��
///////////////////////////////////

#include "pch.h"
#include "LoadDisplay.h"


LoadDisplay* LoadDisplay::m_pMyInstance = nullptr;

///////////////////////////
//������
//����:DeviceResources�̃|�C���^�ACommonStates�̃|�C���^
//�߂�l:�Ȃ�
//////////////////////////
void LoadDisplay::Initialize(DX::DeviceResources * pDeviceResources, DirectX::CommonStates * pStates)
{
	m_pLoadSprite = std::make_unique<Sprite2D>();
	m_pLoadSprite->Create(L"Resources/Textures/Load.png");

	
	m_color = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}

///////////////////////////
//�X�V
//����:���[�h��ʂ̕\���t���O
//�߂�l:�Ȃ�
//////////////////////////
void LoadDisplay::Update(const bool & isLoad, float alpha)
{
	m_isLoadDisplay = isLoad;

	
	m_color = DirectX::SimpleMath::Vector4(1, 1, 1, alpha);
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void LoadDisplay::Render()
{
	if (m_isLoadDisplay == true)
	{
		m_pLoadSprite->Update(m_loadSpritePos);
		m_pLoadSprite->Draw(false,false, m_color);
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void LoadDisplay::Finalize()
{
	m_pLoadSprite->Reset();
}

///////////////////////////
//�C���X�^���X�̎擾
//����:�Ȃ�
//�߂�l:LoadDisplay�̃|�C���^
//////////////////////////
LoadDisplay * LoadDisplay::GetInstance()
{
	if (m_pMyInstance == nullptr)m_pMyInstance = new LoadDisplay();

	return m_pMyInstance;
}

///////////////////////////
//�C���X�^���X�̉��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void LoadDisplay::ReleaseInstance()
{
	if (m_pMyInstance != nullptr)delete m_pMyInstance;
	m_pMyInstance = nullptr;
}

//�R���X�g���N�^
LoadDisplay::LoadDisplay()
	:m_loadSpritePos{},
	m_pLoadSprite(nullptr)
{
	
}

//�f�X�g���N�^
LoadDisplay::~LoadDisplay()
{
	m_pLoadSprite.reset();
}
