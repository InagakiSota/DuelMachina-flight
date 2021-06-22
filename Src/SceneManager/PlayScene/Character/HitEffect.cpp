///////////////////////////////////
//�q�b�g�G�t�F�N�g�̃N���X
//�쐬�ҁF
//�쐬���F
///////////////////////////////////

#include "pch.h"
#include "HitEffect.h"
#include "../../BinaryFile.h"

const std::vector<D3D11_INPUT_ELEMENT_DESC> HitEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


//�R���X�g���N�^
HitEffect::HitEffect()
{
}

//�f�X�g���N�^
HitEffect::~HitEffect()
{
	Finalize();
}

///////////////////////////
//�쐬
//����:�f�o�C�X���\�[�X�A�e�N�X�`���A�C���v�b�g���C�A�E�g
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Create(DX::DeviceResources * deviceresources, ID3D11ShaderResourceView * texture, ID3D11InputLayout * inputLayout)
{
	m_deviceResources = deviceresources;
	auto device = m_deviceResources->GetD3DDevice();

	// �R���p�C�����ꂽ�V�F�[�_�t�@�C����ǂݍ���
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/HitEffectVS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/HitEffectPS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/HitEffectGS.cso");

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

	// �s�N�Z���V�F�[�_�쐬
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}

	// �W�I���g���V�F�[�_�쐬
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// �G���[
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}


	//const wchar_t* name = L"Resources\\Textures\\shadow.png";
	//DirectX::CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), name, nullptr, m_texture.GetAddressOf());

	//const wchar_t* name2 = L"Resources\\Textures\\ball.png";
	//DirectX::CreateWICTextureFromFile(m_deviceResources->GetD3DDevice(), name2, nullptr, m_texture2.GetAddressOf());

	m_texture = texture;

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

	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_isGravity = false;
}

///////////////////////////
//������
//����:�����A���W�A�ړ���
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity)
{
	m_startPos = pos;
	m_startVel = velocity;
	m_startLife = life;

	//int seed = 100;
	//m_wait = ((rand() % seed) / (float)seed) * m_startLife ;

	Reset();
	m_gravity = DirectX::SimpleMath::Vector3(0, 0.001f, 0);
}

///////////////////////////
//�X�V
//����:�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Update(DX::StepTimer timer)
{
	//�����Ɏg���b���v(1�b��1.0f)���擾����B
	float time = float(m_timer.GetElapsedSeconds());
	m_timer = timer;

	//���W�v�Z
	m_pos += m_vel;

	//�������ԂŃ��Z�b�g����
	m_life--;
	if (m_life < 0)
	{
		//Reset();
	}

	////�����Ń��Z�b�g����
	//Vector3 len = m_position - m_startPosition;
	//if (len.Length() > 3.0f) {
	//	Reset();
	//}



	//�d�͌v�Z
	if (m_isGravity == true)
	{
		m_vel -= m_gravity;
	}
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Render()
{
	//�r���{�[�h��
	m_world =
		DirectX::SimpleMath::Matrix::CreateRotationZ(-atan2f(m_vel.y, m_vel.x))*
		DirectX::SimpleMath::Matrix::CreateBillboard(m_pos, m_camera, DirectX::SimpleMath::Vector3::UnitY);

	ShaderDraw();
}

///////////////////////////
//�`��
//����:Z���̊p�x
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Render(float angleZ, float scale)
{	
	//�r���{�[�h��
	m_world =
		DirectX::SimpleMath::Matrix::CreateRotationZ(angleZ) *
		DirectX::SimpleMath::Matrix::CreateScale(scale) * 
		DirectX::SimpleMath::Matrix::CreateBillboard(m_pos, m_camera, DirectX::SimpleMath::Vector3::UnitY);

	ShaderDraw();

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Reset()
{
	m_pos = m_startPos;
	m_vel = m_startVel;
	m_life = m_startLife;
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::Finalize()
{
	m_CBuffer.Reset();
	m_inputLayout.Reset();
	m_batch.reset();
	m_states.reset();
	m_texture.Reset();
	m_texture2.Reset();
	m_VertexShader.Reset();
	m_PixelShader.Reset();
}

///////////////////////////
//�r���[�s��A�ˉe�s��̐ݒ�
//����:�J�������W�A�r���[�s��A�ˉe�s��
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_camera = camera;
	m_view = view;
	m_proj = proj;
}

///////////////////////////
//�d�͂̐ݒ�
//����:
//�߂�l:
//////////////////////////
void HitEffect::SetGravity(bool isGravity)
{
	m_isGravity = isGravity;
}

///////////////////////////
//�V�F�[�_�[�̕`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffect::ShaderDraw()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	// ���_���(�|���S���̂S���_�̍��W���j
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
			DirectX::SimpleMath::Vector4::One, 
			DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
			DirectX::SimpleMath::Vector4::One,
			DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
			DirectX::SimpleMath::Vector4::One,
			DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
			DirectX::SimpleMath::Vector4::One,
			DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	DirectX::VertexPositionColorTexture l_vertex =
		DirectX::VertexPositionColorTexture(m_pos, DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f));

	//�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.matView = m_view.Transpose();
	cbuff.matProj = m_proj.Transpose();
	cbuff.matWorld = m_world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4(m_pos.x, m_pos.y, m_pos.z, m_life);

	//�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);

	//�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);
	// �J�����O�͍�����
	context->RSSetState(m_states->CullNone());

	//�V�F�[�_���Z�b�g����
	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	//�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	context->PSSetShaderResources(1, 1, m_texture2.GetAddressOf());

	//�C���v�b�g���C�A�E�g�̓o�^
	context->IASetInputLayout(m_inputLayout.Get());

	// �|���S����`��
	m_batch->Begin();
	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);

	m_batch->End();

	//�V�F�[�_�̓o�^���������Ă���
	context->VSSetShader(nullptr, nullptr, 0);
	context->PSSetShader(nullptr, nullptr, 0);
	context->GSSetShader(nullptr, nullptr, 0);

}

void HitEffect::Draw()
{
}
