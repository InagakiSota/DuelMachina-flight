///////////////////////////////////
//���[�h��ʂ̊Ǘ��N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2021�N3��25��
///////////////////////////////////

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <CommonStates.h>
#include "../Sprite2D/Sprite2D.h"
#include <memory>

class LoadDisplay
{
public:
	//������
	void Initialize(DX::DeviceResources* pDeviceResources, DirectX::CommonStates* pStates);
	//�X�V
	void Update(const bool& isLoad, float alpha = 1.0f);
	//�`��
	void Render();
	//�I������
	void Finalize();

	//�C���X�^���X�̎擾
	static LoadDisplay* GetInstance();

	//�C���X�^���X�̉��
	static void ReleaseInstance();

private:
	//�R���X�g���N�^
	LoadDisplay();
	//�f�X�g���N�^
	~LoadDisplay();

	//���[�h��ʂ̉摜
	std::unique_ptr<Sprite2D> m_pLoadSprite;
	//���[�h��ʂ̕\���t���O
	bool m_isLoadDisplay;
	//���[�h��ʂ̍��W
	DirectX::SimpleMath::Vector2 m_loadSpritePos;

	//���g�̃C���X�^���X
	static LoadDisplay* m_pMyInstance;

	DirectX::SimpleMath::Vector4 m_color;
};