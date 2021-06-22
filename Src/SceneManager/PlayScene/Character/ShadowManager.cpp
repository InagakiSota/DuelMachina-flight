///////////////////////////////////
//�����̉e�̃}�l�[�W���[�N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��7��
///////////////////////////////////
#include "pch.h"
#include "ShadowManager.h"
#include <WICTextureLoader.h>
#include "d3d11.h"
#include "../../BinaryFile.h"
#include <Effects.h>
#include <Model.h>
#include "Src/Cgdi.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> ShadowManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


//Y���W
const float ShadowManager::POS_Y = -1.5f;
//Z���W
const float ShadowManager::POS_Z = 1.0f;
//X���̊p�x
const float ShadowManager::ROT_X = -90.0f;
//�X�P�[��
const float ShadowManager::SCALE = -0.8f;


//�R���X�g���N�^
ShadowManager::ShadowManager()
	:m_effectList{},
	m_texture{},
	m_texture2{},
	m_timer{},
	m_deviceResources{},
	m_CBuffer{},
	m_states{},
	m_VertexShader{},
	m_PixelShader{},
	m_GeometryShader{},
	m_batch{},
	m_inputLayout{},
	m_vertex{},
	m_centerPosition{},
	m_world{},
	m_view{},
	m_proj{},
	m_fxFactory{},
	m_model{},
	m_capture{},
	m_rtv{},
	m_srv{},
	m_pos{},
	m_scale{}
{
}

//�f�X�g���N�^
ShadowManager::~ShadowManager()
{
}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ShadowManager::Initialize(int count, float life, DirectX::SimpleMath::Vector3 pos)
{
	m_deviceResources = gdi->GetDeviceResources();
	auto device = m_deviceResources->GetD3DDevice();

	//const wchar_t* name = L"Resources\\Textures\\image01.png";
	DirectX::CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), L"Resources\\Textures\\shadow.png", nullptr, m_texture.GetAddressOf());
	//DirectX::CreateWICTextureFromFile(deviceResources->GetD3DDevice(), L"Resources\\Textures\\hight.png", nullptr, m_texture2.GetAddressOf());

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ShadowVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ShadowGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ShadowPS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());
	// ���_�V�F�[�_�쐬
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// �v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(m_deviceResources->GetD3DDeviceContext());

	m_states = std::make_unique<DirectX::CommonStates>(device);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
	m_fxFactory = std::make_unique<DirectX::EffectFactory>(device);
	m_fxFactory->SetDirectory(L"Resources");

	//m_model = Model::CreateFromCMO(device, L"Resources/cup.cmo", *m_fxFactory);

	for (int i = 0; i < count; i++) {
		Effect* effect = new Effect();
		m_effectList.push_back(effect);
	}


	for (std::list<Effect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		(*itr)->Initialize(life, pos, DirectX::SimpleMath::Vector3::Zero);
	}
	m_centerPosition = pos;


}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ShadowManager::Update(DX::StepTimer timer, DirectX::SimpleMath::Vector3 pos)
{
	m_timer = timer;
	for (std::list<Effect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		(*itr)->Update(timer);
	}

	m_pos = pos;

	//�L�����N�^�[�̑�����X���W�𓯊�������
	DirectX::SimpleMath::Matrix trans =	DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_pos.x, POS_Y, POS_Z));
	DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(ROT_X));
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(SCALE);

	m_world = rotX * scale * trans;

}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ShadowManager::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_view = view;
	m_proj = proj;

	m_vertex.clear();
	//�}�l�[�W���ŊǗ����Ă���G�t�F�N�g���C�e���[�^����
	for (auto itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		//�G�t�F�N�g�̒��_�̍��W�Ƒ��x���擾����
		DirectX::SimpleMath::Vector3 pos = (*itr)->GetPos();
		DirectX::SimpleMath::Vector3 vel = (*itr)->GetVel();

		{
			//�擾�������W��o�^����
			DirectX::VertexPositionColorTexture vertex;
			//vertex = VertexPositionColorTexture(pos, Vector4(vel.x,vel.y,vel.z,1), Vector2(0.0f,3.0f));
			vertex = DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector4::Zero,
				DirectX::SimpleMath::Vector4::Zero, 
				DirectX::SimpleMath::Vector2::Zero);
			m_vertex.push_back(vertex);
		}
	}

	//��]���郂�f����\��
	//static float rot = 0.0f;
	//rot += 0.1f;
	//m_model->Draw(m_deviceResources->GetD3DDeviceContext(),
	//	*m_states,
	//	Matrix::CreateRotationZ(rot), m_view, m_proj);



	//�S��ʃG�t�F�N�g
	//DirectX::SimpleMath::Matrix  mat = DirectX::SimpleMath::Matrix::Identity;
	//Draw(mat, mat, mat);

	//�|���S���G�t�F�N�g
	Draw(m_world, m_view, m_proj);
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void ShadowManager::Finalize()
{
	for (std::list<Effect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		delete (*itr);
	}
}


///////////////////////////
//�`��
//����:
//�߂�l:
//////////////////////////
void ShadowManager::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	//�萔�o�b�t�@�œn���l�̐ݒ�
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = world.Transpose();
	//Time		x:�o�ߎ���(�g�[�^���b)	y:1F�̌o�ߎ���(�b�j	z:�����i�T�C���J�[�u�j w:���g�p�i�b��łP�j
	cbuff.Time = DirectX::SimpleMath::Vector4((float)m_timer.GetTotalSeconds(), (float)m_timer.GetElapsedSeconds(), sinf((float)m_timer.GetTotalSeconds()), 1.0f);

	//�萔�o�b�t�@�̓��e�X�V
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�͎Q�Ƃ̂�
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);
	// �J�����O�͔����v���
	context->RSSetState(m_states->CullCounterClockwise());

	//�萔�o�b�t�@���V�F�[�_�ɓn���i
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	//context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);


	//�T���v���[�A�V�F�[�_�A�摜�����ꂼ��o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	context->PSSetShaderResources(1, 1, m_texture2.GetAddressOf());

	//���̓��C�A�E�g�𔽉f
	context->IASetInputLayout(m_inputLayout.Get());

	//�o�b�`�ɒ��_����n��
	m_batch->Begin();
	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertex[0], m_vertex.size());
	m_batch->End();


	//���̃��f���ɉe�����o��\��������̂Ŏg���I�������V�F�[�_���O��
	context->VSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
}
