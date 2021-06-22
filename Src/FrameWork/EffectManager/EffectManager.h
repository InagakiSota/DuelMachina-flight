///////////////////////////////////
//�G�t�F�N�g�Ǘ��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��23��
///////////////////////////////////
#pragma once

#include "DeviceResources.h"
#include "../../StepTimer.h"

#include <SimpleMath.h>
#include <list>
#include <WICTextureLoader.h>
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "../MyEffect/MyEffect.h"

class EffectManager
{
public:
	//�R���X�g���N�^
	EffectManager()
	{

	}
	//�f�X�g���N�^
	~EffectManager()
	{
		m_batchEffect.reset();
		m_effectList.clear();
		m_batch.reset();
	}

	void Create(DX::DeviceResources* deviceResources);
	//Create()�őS�������͒����̂ŕ���
	void Initialize(float life,DirectX::SimpleMath::Vector3 pos);

	void Update(DX::StepTimer timer);
	void Render();

	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:
	//�o�b�`�G�t�F�N�g
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	//�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;


	//�G�t�F�N�g�̃|�C���^
	//MyEffect*	m_effect;
	std::list<std::unique_ptr<MyEffect>> m_effectList;

	//�e�N�X�`���f�[�^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;

};