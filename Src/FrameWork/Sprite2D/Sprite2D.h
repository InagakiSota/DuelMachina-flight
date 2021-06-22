///////////////////////////////////
//2D�X�v���C�g
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N5��22��
///////////////////////////////////

#pragma once

#include "SpriteBatch.h"
#include "SimpleMath.h"
#include <CommonStates.h>

class Sprite2D
{
public:
	Sprite2D();
	~Sprite2D();

	//����
	void Create(const wchar_t* fileName);
	//�`��
	void Draw(bool isAlpha = false, bool isRect = false, DirectX::FXMVECTOR color = DirectX::SimpleMath::Vector4(1,1,1,1));
	//���Z�b�g
	void Reset();
	//�X�V
	void Update(const float& posX = 0, const float& posY = 0);
	void Update(const DirectX::SimpleMath::Vector2& pos);
	void Update(const float& posX, const float& posY,const RECT& rect);
	void Update(const DirectX::SimpleMath::Vector2& pos, const RECT& rect);

private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	DirectX::SpriteBatch* m_spriteBatch;
	//�摜�̍��W
	DirectX::SimpleMath::Vector2 m_pos;
	//�摜�؂���ʒu
	RECT m_rect;
	DirectX::CommonStates* m_pStates;
};

