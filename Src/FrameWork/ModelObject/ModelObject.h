///////////////////////////////////
//���f���`��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N5��21��
///////////////////////////////////
#pragma once

#include "../../DeviceResources.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <CommonStates.h>
#include <Model.h>

class ModelObject
{
public:
	ModelObject();		//�R���X�g���N�^
	~ModelObject();		//�f�X�g���N�^

	void Update(DirectX::SimpleMath::Matrix world);		//�X�V
	void Lost();
	void Create(DX::DeviceResources* deviceResources , const wchar_t* name);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:
	DX::DeviceResources* m_deviceResources;

	DirectX::SimpleMath::Matrix m_world;
	//DirectX::SimpleMath::Matrix m_view;
	//DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::EffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;

};

