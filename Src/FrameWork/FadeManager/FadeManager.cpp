///////////////////////////////////
//�t�F�[�h�C���A�A�E�g�̊Ǘ��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2021�N1��8��
///////////////////////////////////

#include "pch.h"
#include "FadeManager.h"

FadeManager* FadeManager::m_pMyInstance = nullptr;

const std::vector<D3D11_INPUT_ELEMENT_DESC> FadeManager::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

///////////////////////////
//�쐬
//����:�f�o�C�X���\�[�X
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::Create(DX::DeviceResources * deviceResources)
{
	m_deviceResources = deviceResources;
	auto device = m_deviceResources->GetD3DDevice();

	//const wchar_t* name = L"Resources\\Textures\\image01.png";
	DirectX::CreateWICTextureFromFile(deviceResources->GetD3DDevice(), L"Resources\\Textures\\Black.png", nullptr, m_texture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(deviceResources->GetD3DDevice(), L"Resources\\Textures\\floor.png", nullptr, m_texture2.GetAddressOf());

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/EffectVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/EffectGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/FadeEffectPS.cso");

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

	//m_model = Model::CreateFromCMO(device, L"Resources/cup.cmo", *m_fxFactory);

	for (int i = 0; i < 1; i++) 
	{
		MyEffect* effect = new MyEffect();
		m_effectList.push_back(effect);
		//delete effect;
	}
}

///////////////////////////
//������
//����:�����A���W
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::Initialize(float life, DirectX::SimpleMath::Vector3 pos)
{
	for (std::list<MyEffect*>::iterator ite = m_effectList.begin(); ite != m_effectList.end(); ite++)
	{
		(*ite)->Initialize(life,DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero);
	}
}


///////////////////////////
//�X�V
//����:�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::Update(DX::StepTimer timer,float time)
{
	m_timer = timer;
	m_time = time;
	for (std::list<MyEffect*>::iterator ite = m_effectList.begin(); ite != m_effectList.end(); ite++)
	{
		(*ite)->Update(timer);
	}

}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	m_vertex.clear();
	//�}�l�[�W���ŊǗ����Ă���G�t�F�N�g���C�e���[�^����
	for (auto itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		//�G�t�F�N�g�̒��_�̍��W�Ƒ��x���擾����
		DirectX::SimpleMath::Vector3 pos = (*itr)->GetPosition();
		DirectX::SimpleMath::Vector3 vel = (*itr)->GetVelocity();

		{
			//�擾�������W��o�^����
			DirectX::VertexPositionColorTexture vertex;
			//vertex = VertexPositionColorTexture(pos, Vector4(vel.x,vel.y,vel.z,1), Vector2(0.0f,3.0f));
			vertex = DirectX::VertexPositionColorTexture(pos, DirectX::SimpleMath::Vector4::Zero, DirectX::SimpleMath::Vector2::Zero);
			m_vertex.push_back(vertex);
		}
	}

	//�S��ʃG�t�F�N�g
	DirectX::SimpleMath::Matrix  mat = DirectX::SimpleMath::Matrix::Identity;
	Draw(mat, mat, mat);

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::Finalize()
{
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		delete (*itr);
	}
	m_effectList.clear();
}

///////////////////////////
//�`��
//����:���[���h�s��A�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	//�萔�o�b�t�@�œn���l�̐ݒ�
	ConstBuffer cbuff;
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = world.Transpose();
	//Time		x:�o�ߎ���(�g�[�^���b)	y:1F�̌o�ߎ���(�b�j	z:�����i�T�C���J�[�u�j w:���g�p�i�b��łP�j
	cbuff.Time = DirectX::SimpleMath::Vector4(static_cast<float>( m_timer.GetTotalSeconds()),static_cast<float>(m_timer.GetElapsedSeconds()), sinf(static_cast<float>(m_timer.GetTotalSeconds())), m_time);

	DirectX::Mouse::State ms = DirectX::Mouse::Get().GetState();

	//�萔�o�b�t�@�̓��e�X�V
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�͎Q�Ƃ̂�
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);
	// �J�����O�͔����v���
	context->RSSetState(m_states->CullCounterClockwise());

	//�萔�o�b�t�@���V�F�[�_�ɓn���i�Ƃ肠����PS�͗v��Ȃ��̂ŃR�����g�A�E�g�j
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

///////////////////////////
//�C���X�^���X�̎擾
//����:�Ȃ�
//�߂�l:���g�̃|�C���^
//////////////////////////
FadeManager * FadeManager::GetInstance()
{
	if (m_pMyInstance == nullptr)
	{
		m_pMyInstance = new FadeManager();
	}

	return m_pMyInstance;
}

///////////////////////////
//�C���X�^���X�̔j��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void FadeManager::ReleaseInstance()
{
	if (m_pMyInstance != nullptr)
	{
		delete m_pMyInstance;
	}
	m_pMyInstance = nullptr;

}

//�R���X�g���N�^
FadeManager::FadeManager()
	:m_time(1.0f)
{
		
}

//�f�X�g���N�^
FadeManager::~FadeManager()
{
	m_VertexShader.Reset();
	m_GeometryShader.Reset();
	m_PixelShader.ReleaseAndGetAddressOf();
	m_PixelShader.Reset();
}
