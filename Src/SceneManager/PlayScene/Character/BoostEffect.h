///////////////////////////////////
//�u�[�X�g�G�t�F�N�g�̃N���X
//�쐬�ҁF
//�쐬���F
///////////////////////////////////
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

class BoostEffect
{
public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//�R���X�g���N�^
	BoostEffect();
	//�f�X�g���N�^
	~BoostEffect();

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	//static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_SHADER_LAYOUT;

	//�쐬
	void Create(DX::DeviceResources* deviceresources, ID3D11ShaderResourceView* texture, ID3D11InputLayout* inputLayout);
	//������
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity);
	//�X�V
	void Update(DX::StepTimer timer);
	//�`��
	void Render();
	//���Z�b�g
	void Reset();
	//�I������
	void Finalize();
	//�r���[�s��A�ˉe�s��̐ݒ�
	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�d�͂̐ݒ�
	void SetGravity(bool isGravity);
	//�����̎擾
	float GetLife()
	{
		return m_life;
	}

private:
	//�V�F�[�_�[�̕`��
	void ShaderDraw();
	//�`��
	void Draw();

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	DX::StepTimer                           m_timer;
	DX::DeviceResources*	m_deviceResources;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputShaderLayout;

	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	//�W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;


	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	//�J�����̍��W
	DirectX::SimpleMath::Vector3		m_camera;
	//�d��
	DirectX::SimpleMath::Vector3		m_gravity;
	//���W
	DirectX::SimpleMath::Vector3		m_pos;
	//�ړ���
	DirectX::SimpleMath::Vector3		m_vel;
	//��������
	float								m_life;

	//�������W
	DirectX::SimpleMath::Vector3		m_startPos;
	//�����ړ���
	DirectX::SimpleMath::Vector3		m_startVel;
	//�������C�t
	float								m_startLife;
	//�ҋ@����
	float								m_wait;
	//�d�͂���p���邩�ǂ���
	bool								m_isGravity;
};