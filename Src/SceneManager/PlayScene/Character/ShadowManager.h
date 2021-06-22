///////////////////////////////////
//�����̉e�̃}�l�[�W���[�N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��7��
///////////////////////////////////

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include "Effect.h"
#include "Model.h"

#include <list>

class ShadowManager
{
public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	Time;
	};
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	//Y���W
	static const float POS_Y;
	//Z���W
	static const float POS_Z;
	//X���̊p�x
	static const float ROT_X;
	//�X�P�[��
	static const float SCALE;

	//�R���X�g���N�^
	ShadowManager();
	//�f�X�g���N�^
	~ShadowManager();

	//������
	void Initialize(int count, float life, DirectX::SimpleMath::Vector3 pos);
	//�X�V
	void Update(DX::StepTimer timer,DirectX::SimpleMath::Vector3 pos);
	//�`��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�I������
	void Finalize();
	
	//�`��
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

private:
	//MyEffect*					m_myEffect[10];
	std::list<Effect*>		m_effectList;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;


	DX::StepTimer                           m_timer;


	DX::DeviceResources*			m_deviceResources;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;
	std::unique_ptr<DirectX::CommonStates> m_states;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	std::vector<DirectX::VertexPositionColorTexture>  m_vertex;

	DirectX::SimpleMath::Vector3 m_centerPosition;

	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	std::unique_ptr<DirectX::EffectFactory> m_fxFactory;
	std::unique_ptr<DirectX::Model> m_model;


	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_capture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;

	//���W
	DirectX::SimpleMath::Vector3 m_pos;
	//�X�P�[��
	float m_scale;

};

