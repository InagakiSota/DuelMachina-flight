///////////////////////////////////
//2D�X�v���C�g
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N5��22��
///////////////////////////////////

#include  "pch.h"
#include "Sprite2D.h"
#include "SimpleMath.h"
#include "WICTextureLoader.h"
#include "Src/Cgdi.h"

//�R���X�g���N�^
Sprite2D::Sprite2D()
	:m_pos(0,0),
	m_pStates(nullptr),
	m_rect{}
{
}

//�f�X�g���N�^
Sprite2D::~Sprite2D()
{
	if (m_spriteBatch != nullptr)
	{
		m_spriteBatch = nullptr;
	}
	m_pStates = nullptr;

	m_texture.Reset();
}

//����
void Sprite2D::Create(const wchar_t* fileName)
{
	
	m_spriteBatch = gdi->GetSprite();
	DirectX::CreateWICTextureFromFile(gdi->GetDeviceResources()->GetD3DDevice(), fileName, NULL, m_texture.ReleaseAndGetAddressOf());
	m_pStates = gdi->GetStates();

	m_rect.top = 0;
	m_rect.left = 0;
	m_rect.bottom = 0;
	m_rect.right = 0;
}

///////////////////////////
//�`��
//����:isAlpa:���߂����邩�ǂ���(true = ���߂�����Afalse = ���߂����Ȃ�)
//     isRect:�؂��邩�ǂ���(true = �؂���Afalse = �؂���Ȃ�)
//�߂�l:
//////////////////////////
void Sprite2D::Draw(bool isAlpha, bool isRect, DirectX::FXMVECTOR color)
{
	//���߂����Ȃ�
	if (isAlpha == false)
	{
		m_spriteBatch->Begin();
		//�؂��肵�Ȃ�
		if (isRect == false)
		{
			m_spriteBatch->Draw(m_texture.Get(), m_pos, color);
		}
		//�؂��肷��
		else if(isRect == true)
		{
			m_spriteBatch->Draw(m_texture.Get(), m_pos, &m_rect, color);
		}
		m_spriteBatch->End();
	}
	//���߂�����
	else
	{
		m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred,m_pStates->NonPremultiplied());
		//�؂��肵�Ȃ�
		if (isRect == false)
		{
			m_spriteBatch->Draw(m_texture.Get(), m_pos, color);
		}
		//�؂��肷��
		else if(isRect == true)
		{
			m_spriteBatch->Draw(m_texture.Get(), m_pos, &m_rect, color);
		}
		m_spriteBatch->End();

	}
}

//���Z�b�g
void Sprite2D::Reset()
{
	m_texture.Reset();
	m_spriteBatch = nullptr;
}

//�X�V
void Sprite2D::Update(const float& posX, const float& posY)
{
	//���W�̐ݒ�
	m_pos.x = posX;
	m_pos.y = posY;
}

void Sprite2D::Update(const DirectX::SimpleMath::Vector2 & pos)
{
	//���W�̐ݒ�
	m_pos = pos;
}

void Sprite2D::Update(const float & posX, const float & posY, const RECT & rect)
{
	//���W�̐ݒ�
	m_pos.x = posX;
	m_pos.y = posY;

	//�摜�؂���ʒu�̐ݒ�
	m_rect = rect;
}

void Sprite2D::Update(const DirectX::SimpleMath::Vector2 & pos, const RECT & rect)
{
	//���W�̐ݒ�
	m_pos = pos;

	//�摜�؂���ʒu�̐ݒ�
	m_rect = rect;

}

