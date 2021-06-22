///////////////////////////////////
//�q�b�g�G�t�F�N�g�̃}�l�[�W���[
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��22��
///////////////////////////////////

#include "pch.h"
#include "HitEffectManager.h"

#include "DeviceResources.h" 
#include "StepTimer.h" 
#include <SimpleMath.h> 
#include <Effects.h> 
#include <PrimitiveBatch.h> 
#include <VertexTypes.h> 
#include <WICTextureLoader.h> 
#include <CommonStates.h> 

#include "../../BinaryFile.h"


//�R���X�g���N�^
HitEffectManager::HitEffectManager()
	:m_isPlay(false)
{
}

//�f�X�g���N�^
HitEffectManager::~HitEffectManager()
{
}

///////////////////////////
//�쐬
//����:�f�o�C�X���\�[�X�̃|�C���^,�G�t�F�N�g�̌�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Create(DX::DeviceResources * deviceResources,const int& count)
{
	//D3DDevice���擾����
	auto device = deviceResources->GetD3DDevice();

	//�o�b�`�G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<DirectX::AlphaTestEffect>(device);
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);
	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	//�v���~�e�B�u�o�b�`�̍쐬
	m_batch =
		std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(deviceResources->GetD3DDeviceContext());

	//�e�N�X�`���̃��[�h
	DirectX::CreateWICTextureFromFile(device, L"Resources/Textures/hitEffect.png", nullptr,
		m_texture.GetAddressOf());


	//�G�t�F�N�g�����̉����A���X�g�ɓo�^����B
	for (int i = 0; i < count; i++) 
	{
		std::unique_ptr<HitEffect> effect = std::make_unique<HitEffect>();
		effect->Create(deviceResources, m_texture.Get(), m_inputLayout.Get());
		m_hitEffectList.push_back(std::move(effect));
	}
}

///////////////////////////
//������
//����:�����A���W
//����:�����A���W
//����:�����A���W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Initialize(float life, DirectX::SimpleMath::Vector3 pos, eEFFECT_TYPE type)
{
	switch (type)
	{
		//�����_��
		case HitEffectManager::eEFFECT_TYPE::RANDOM:
		{
			InitializeRandom(life, pos);
			break;

		}

		//�ϓ�
		case HitEffectManager::eEFFECT_TYPE::AVERAGE:
		{
			InitializeAverage(life, pos);

			break;

		}

		//�R�[��
		case HitEffectManager::eEFFECT_TYPE::CONE:
		{
			InitializeCone(life, pos);

			break;
		}

		//�X�e�C
		case HitEffectManager::eEFFECT_TYPE::STAY:
		{
			InitializeStay(life, pos);
			break;
		}


		default:
			break;
	}
}

///////////////////////////
//������(���Ԋu)
//����:�����A���W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::InitializeAverage(float life, DirectX::SimpleMath::Vector3 pos)
{
	const float RAD = DirectX::XM_PI * 2.0f;
	int num = 0;
	for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
	{
		float size = (float)m_hitEffectList.size();
		DirectX::SimpleMath::Vector3 vel =
			DirectX::SimpleMath::Vector3(cosf(RAD * num / size + DirectX::XM_PI / 2.0f), sinf(RAD * num / size + DirectX::XM_PI / 2.0f), 0);
		vel *= 0.1f;
		(*ite)->Initialize(life, pos, vel);
		num++;
	}
}

///////////////////////////
//������(�����_��)
//����:�����A���W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::InitializeRandom(float life, DirectX::SimpleMath::Vector3 pos)
{
	int range = 100;

	//life,pos,vel �̒l��m_effect������������
	for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
	{
		DirectX::SimpleMath::Vector3 vel = 
			DirectX::SimpleMath::Vector3(
			((rand() % (range * 2)) - range) / (float)range * 0.2f, 
			((rand() % (range * 2)) - range) / (float)range * 0.2f, 
			((rand() % (range * 2)) - range) / (float)range * 0.2f);

		while (vel.Length() < 0.03f)
		{
			vel =
				DirectX::SimpleMath::Vector3(
				((rand() % (range * 2)) - range) / (float)range * 0.1f,
				((rand() % (range * 2)) - range) / (float)range * 0.1f, 
				((rand() % (range * 2)) - range) / (float)range * 0.1f);
		}

		(*ite)->Initialize(life, pos, vel);
	}

}

///////////////////////////
//������(�R�[��)
//����:�����A���W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::InitializeCone(float life, DirectX::SimpleMath::Vector3 pos)
{
	//�G�t�F�N�g�̒��S��
	DirectX::SimpleMath::Vector3 dir = DirectX::SimpleMath::Vector3(-3, 1, -5);

	//���̒l�𐳋K������
	dir.Normalize();

	//�O�ςɎg�����߂̃J�����ʒu�i�{���͊O����󂯓n����Ɨǂ��j
	DirectX::SimpleMath::Vector3 camera = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 6.0f);

	//life,pos,vel �̒l��m_effect������������
	for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
	{
		//���ƃJ��������O�ς����߂�
		DirectX::SimpleMath::Vector3 d = dir.Cross(camera);
		//�O�ς𐳋K������
		d.Normalize();
		//�O�ς̒l�ƒ��S�������Z����
		d = dir + d * (float)sin(rand())*0.3f;
		//�l���傫���̂�0.1�{
		d *= 0.1f;
		(*ite)->Initialize(life, pos, d);
	}

}

///////////////////////////
//������(�X�e�C)
//����:�����A�������W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::InitializeStay(float life, DirectX::SimpleMath::Vector3 pos)
{
	for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end();ite++)
	{
		(*ite)->Initialize(life, pos, DirectX::SimpleMath::Vector3::Zero);
	}
}

///////////////////////////
//������(�X�e�C)
//����:�����A�������W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::InitializeStay(float life, DirectX::SimpleMath::Vector3 pos, int index)
{
	m_hitEffectList[index]->Initialize(life,pos,DirectX::SimpleMath::Vector3::Zero);
}

///////////////////////////
//�X�V
//����:�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Update(DX::StepTimer timer)
{
	if(m_isPlay == true)
	{
		for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
		{
			(*ite)->Update(timer);

			//�G�t�F�N�g�̎�����0�ɂȂ�����Đ�����߂�
			//if ((*ite)->GetLife() < 0)m_isPlay = false;
		}
	}
}


///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Render()
{
	if (m_isPlay == true)
	{
		for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
		{
			(*ite)->Render();
		}
	}
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Render(float angleZ, float scale)
{
	if (m_isPlay == true)
	{
		for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
		{
			(*ite)->Render(angleZ, scale);
		}
	}

}

///////////////////////////
//�r���[�s��A�ˉe�s��̐ݒ�
//����:
//�߂�l:
//////////////////////////
void HitEffectManager::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
	{
		(*ite)->SetRenderState(camera,view,proj);
	}
}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Finalize()
{
	//m_hitEffectList.clear();
	//m_inputLayout.Reset();
	//m_texture.Reset();
}

///////////////////////////
//�d�͂̐ݒ�
//����:�d�͂̃t���O
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::SetGravity(bool gravity)
{
	for (std::vector<std::unique_ptr<HitEffect>>::iterator ite = m_hitEffectList.begin(); ite != m_hitEffectList.end(); ite++)
	{
		(*ite)->SetGravity(gravity);
	}
}

///////////////////////////
//�Đ�
//����:�����A�������W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Play(float life, DirectX::SimpleMath::Vector3 pos, eEFFECT_TYPE type)
{
	switch (type)
	{
		//�����_��
		case HitEffectManager::eEFFECT_TYPE::RANDOM:
		{
			InitializeRandom(life, pos);
			break;

		}

		//�ϓ�
		case HitEffectManager::eEFFECT_TYPE::AVERAGE:
		{
			InitializeAverage(life, pos);

			break;

		}

		//�R�[��
		case HitEffectManager::eEFFECT_TYPE::CONE:
		{
			InitializeCone(life, pos);

			break;
		}

		//�X�e�C
		case HitEffectManager::eEFFECT_TYPE::STAY:
		{
			InitializeStay(life, pos);
			break;
		}

		default:
			break;
	}
	//�Đ��t���O�𗧂Ă�
	m_isPlay = true;
}

///////////////////////////
//�Đ�
//����:�����A�������W
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Play(float life, DirectX::SimpleMath::Vector3 pos, int index, eEFFECT_TYPE type)
{
	//�Đ��t���O�𗧂Ă�
	m_isPlay = true;

	switch (type)
	{
		//�����_��
		case HitEffectManager::eEFFECT_TYPE::RANDOM:
		{
			InitializeRandom(life, pos);
			break;

		}

		//�ϓ�
		case HitEffectManager::eEFFECT_TYPE::AVERAGE:
		{
			InitializeAverage(life, pos);

			break;

		}

		//�R�[��
		case HitEffectManager::eEFFECT_TYPE::CONE:
		{
			InitializeCone(life, pos);

			break;
		}

		//�X�e�C
		case HitEffectManager::eEFFECT_TYPE::STAY:
		{
			InitializeStay(life, pos, index);
			break;
		}

		default:
			break;
	}

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void HitEffectManager::Reset()
{
	m_isPlay = false;
}

