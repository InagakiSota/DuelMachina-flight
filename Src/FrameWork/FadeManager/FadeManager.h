///////////////////////////////////
//�t�F�[�h�C���A�A�E�g�̊Ǘ��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2021�N1��8��
///////////////////////////////////

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include "../MyEffect/MyEffect.h"
#include "Model.h"
#include <Mouse.h>
#include <PrimitiveBatch.h>
#include <list>
#include <Effects.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "../../SceneManager/BinaryFile.h"


class FadeManager
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

	//�쐬
	void Create(DX::DeviceResources* deviceResources);
	//������
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos);
	//�X�V
	void Update(DX::StepTimer timer,float time);
	//�`��
	void Render();
	//�I������
	void Finalize();
	//�`��
	void Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	//�C���X�^���X�̎擾
	static FadeManager* GetInstance();
	//�C���X�^���X�̔j��
	static void ReleaseInstance();

private:
	//�R���X�g���N�^
	FadeManager();
	//�f�X�g���N�^
	~FadeManager();

	//�G�t�F�N�g�̃��X�g
	std::list<MyEffect*>		m_effectList;
	//�e�N�X�`��1
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	//�e�N�X�`��2(�g�����͂킩��Ȃ�)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;

	//�^�C�}�[
	DX::StepTimer                           m_timer;
	//����
	float m_time;


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

	DirectX::SimpleMath::Matrix m_billboardTranslation;	//�r���{�[�h
	DirectX::SimpleMath::Matrix m_view;					//�r���[�s��
	DirectX::SimpleMath::Matrix m_proj;					//�ˉe�s��

	//���g�̃C���X�^���X
	static FadeManager* m_pMyInstance;

};
