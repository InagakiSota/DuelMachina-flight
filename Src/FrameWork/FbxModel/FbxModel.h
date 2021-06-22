///////////////////////////////////
//Fbx�t�@�C���̕\���N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N8��7��
///////////////////////////////////

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

#include <SimpleMath.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <fbxsdk.h>
#include <Windows.h>
#include <map>
#include <CommonStates.h>

#pragma comment(lib, "d3dcompiler.lib")

class FbxModel
{
public:
	//1�̒��_�����i�[����\����
	struct Vertex
	{
		DirectX::SimpleMath::Vector3 pos;
		DirectX::SimpleMath::Vector3 normal;
		DirectX::SimpleMath::Vector3 texturePos;
		int* indexBuffer;
		int uvSetCount;
		
	};

	//�V�F�[�_�[���֑��鐔�l���܂Ƃ߂��\����
	struct ConstantBuffer
	{
		DirectX::XMMATRIX mW;
		DirectX::XMMATRIX mWVP;
		DirectX::XMVECTOR lightPos;
		DirectX::XMVECTOR eyePos;
		DirectX::XMVECTOR color;
		DirectX::XMVECTOR texture;
	};

	FbxModel();
	~FbxModel();

	//�t�@�C���̓ǂݍ���
	bool Load(HWND window, ID3D11Device* pDevice,
		ID3D11DeviceContext* pContext, ID3D11RenderTargetView* pRenderTargetView,
		const char* fileName, bool isAnimation = false, int animStackNumber = 0);

	//�`��
	void Draw(
		DirectX::SimpleMath::Matrix world,
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj,
		DirectX::SimpleMath::Vector4 color = DirectX::SimpleMath::Vector4(1.0f,1.0f,1.0f,1.0f));

	//�A�j���[�V�����̐؂�ւ�
	void ChangeAnimation(const int& animeStack);

private:
	ID3D11RasterizerState* m_pRasterizerState;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer;

	std::vector<Vertex> m_vertices;

	ID3D11Buffer* m_pVerBuffer;
	ID3D11Buffer* m_pIndBuffer;

	int m_AnimStackNumber;
	FbxTime m_frameTime;
	FbxTime m_timeCount;
	FbxTime m_start;
	FbxTime m_stop;

	HWND m_window;

	FbxManager* m_pFbxManager;
	FbxImporter* m_pFbxImporter;
	FbxScene* m_pFbxScene;
	IDXGISwapChain* m_pSwapChain;

	//���b�V���̖��O
	std::vector<std::string> m_fbxMeshNameArray;			
	std::vector<FbxMesh*> m_pfbxMeshArray;

	//�e�N�X�`��
	std::vector<FbxFileTexture*> m_fbxTextureArray;
	//�e�N�X�`���̃t�@�C���p�X
	std::vector<std::string> m_fbxTextureFilePath;
	//�t�@�C���p�X�̃L����
	std::vector<char> m_texturePathChar;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pContext;
	ID3D11RenderTargetView* m_pRenderTargetView;

	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_pStates;
	
	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT m_vp;			

	bool m_isAnimation;

	//�F
	DirectX::SimpleMath::Vector4 m_color;

	//�A�j���[�V�����p�̕`��
	bool DrawAnimation(FbxNode* pNode,
		DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�ʏ�̕`��
	bool DrawModel(FbxNode* pNode,
		DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);




};

