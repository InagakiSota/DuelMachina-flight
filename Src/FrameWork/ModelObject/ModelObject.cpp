///////////////////////////////////
//���f���`��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N5��21��
///////////////////////////////////

#include  "pch.h"
#include "ModelObject.h"



//�R���X�g���N�^
ModelObject::ModelObject()
	:m_deviceResources(nullptr)
{
}

//�f�X�g���N�^
ModelObject::~ModelObject()
{
	m_deviceResources = nullptr;

	m_states.reset();
	m_fxFactory.reset();
	m_model.reset();

}

//�X�V
void ModelObject::Update(DirectX::SimpleMath::Matrix world)
{
	//Vector3 camPos = Vector3(0.0f, 0.0f, 5.0f);

	//view = Matrix::CreateLookAt(camPos, Vector3::Zero, Vector3::UnitY);

	//Matrix scale = Matrix::CreateScale(Vector3(0.005f, 0.005f,0.005f));
	//Matrix scale2 = Matrix::CreateScale(Vector3(0.5f, 0.5f, 0.5f));

	m_world = world;

}

void ModelObject::Lost()
{
	m_states.reset();
	m_fxFactory.reset();
	m_model.reset();

	//delete m_deviceResources;
	m_deviceResources = nullptr;
}

void ModelObject::Create(DX::DeviceResources* deviceResources, const wchar_t* name)
{
	m_deviceResources = deviceResources;
	ID3D11Device1* device = m_deviceResources->GetD3DDevice();

	m_states = std::make_unique<DirectX::CommonStates>(device);
	//�G�t�F�N�g�t�@�N�g���[�̍쐬
	m_fxFactory = std::make_unique<DirectX::EffectFactory>(device);
	//�e�N�X�`���̓ǂݍ��݃p�X�w��
	m_fxFactory->SetDirectory(L"Resources/Models");
	//���f���f�[�^�ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, name, *m_fxFactory);

	m_world = DirectX::SimpleMath::Matrix::Identity;

	//proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.0f,
	//	float(backBufferWidth) / float(backBufferHeight), 0.1, 10.0f);
	
}

void ModelObject::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	ID3D11DeviceContext1* context = m_deviceResources->GetD3DDeviceContext();
	m_model->Draw(context, *m_states, m_world, view, proj);
}
