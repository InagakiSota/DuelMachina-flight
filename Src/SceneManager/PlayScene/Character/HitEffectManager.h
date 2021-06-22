///////////////////////////////////
//�q�b�g�G�t�F�N�g�̃}�l�[�W���[
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N12��22��
///////////////////////////////////

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include <SimpleMath.h>
#include <list>
#include <WICTextureLoader.h>
#include "HitEffect.h"
#include <vector>

class HitEffectManager
{
public:
	enum class eEFFECT_TYPE
	{
		NONE = -1,
		RANDOM,			//�����_��
		AVERAGE,		//�ϓ�
		CONE,			//�R�[��
		STAY,			//��~

		OVER_ID,
	};

	HitEffectManager();
	~HitEffectManager();

	//Create()�őS�������͒����̂ŕ���
	void Create(DX::DeviceResources* deviceResources,const int& count);

	//������
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, eEFFECT_TYPE type = eEFFECT_TYPE::RANDOM);
	//���Ԋu�ŃG�t�F�N�g���΂������̏�����
	void InitializeAverage(float life, DirectX::SimpleMath::Vector3 pos);
	//�����_���ɃG�t�F�N�g���΂������̏�����
	void InitializeRandom(float life, DirectX::SimpleMath::Vector3 pos);
	//�R�[����ɃG�t�F�N�g���΂������̏�����
	void InitializeCone(float life, DirectX::SimpleMath::Vector3 pos);
	//���̏�ɒ�~����G�t�F�N�g�̏�����
	void InitializeStay(float life, DirectX::SimpleMath::Vector3 pos);
	//���̏�ɒ�~����G�t�F�N�g�̏�����
	void InitializeStay(float life, DirectX::SimpleMath::Vector3 pos,int index);

	//�X�V
	void Update(DX::StepTimer timer);
	//�`��
	void Render();
	//�`��
	void Render(float angleZ, float scale = 1.0f);
	//�J�����A�ˉe�A�r���[�̔��f
	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�I������
	void Finalize();
	//�d�͂�ݒ肷��
	void SetGravity(bool gravity);

	//�Đ�
	void Play(float life, DirectX::SimpleMath::Vector3 pos, eEFFECT_TYPE type = eEFFECT_TYPE::RANDOM);
	//�Đ�
	void Play(float life, DirectX::SimpleMath::Vector3 pos,int index,eEFFECT_TYPE type = eEFFECT_TYPE::RANDOM);
	//���Z�b�g
	void Reset();

private:
	//�o�b�`�G�t�F�N�g
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	//�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//�G�t�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<HitEffect>>	m_hitEffectList;
	//�e�N�X�`���f�[�^
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_texture;

	//�Đ��t���O
	bool m_isPlay;
	//Z���̊p�x
	float m_angleZ;

};