///////////////////////////////////
//�f�o�b�O�t�H���g
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N5��20��
///////////////////////////////////

#include  "pch.h"

#include "DebugFont.h"

#if DEBUG_FONT_SINGLETON_TYPE == 0
DebugFont* DebugFont::m_pInstance = nullptr;
#elif DEBUG_FONT_SINGLETON_TYPE == 1
std::unique_ptr<DebugFont>DebugFont::m_pInstance = nullptr;
#else
DebugFont DebugFont::m_instance;
#endif

//�R���X�g���N�^
DebugFont::DebugFont()
	:m_pos(0, 0),
	m_string(nullptr),
	m_color()
{
	m_string = new wchar_t[STRING_SIZE_MAX];
}

//�f�X�g���N�^
DebugFont::~DebugFont()
{
	delete[] m_string;

	m_spriteBatch.reset();
	m_spriteFont.reset();
}

///////////////////////////
//�X�V
//����:device,context
//�߂�l:�Ȃ�
//////////////////////////
void DebugFont::Create(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	
	if (m_spriteBatch == nullptr)m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	if (m_spriteFont == nullptr)m_spriteFont = std::make_unique<DirectX::SpriteFont>(device, L"Resources/Font/SegoeUI_18.spritefont");

}


///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void DebugFont::Draw()
{
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(), m_string, m_pos, m_color);
	m_spriteBatch->End();

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void DebugFont::Reset()
{
	m_spriteBatch.reset();
	m_spriteFont.reset();
}

///////////////////////////
//�\�����o�^
//����:���W�A������A�F
//�߂�l:�Ȃ�
//////////////////////////
void DebugFont::Print(float posX, float posY, wchar_t const * const format, DirectX::XMVECTOR color, ...)
{
	m_pos.x = posX;
	m_pos.y = posY;


	m_color = color;

	va_list arg_ptr;

	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
	

}

///////////////////////////
//�\�����o�^
//����:���W�A������A�F
//�߂�l:�Ȃ�
//////////////////////////
void DebugFont::Print(DirectX::SimpleMath::Vector2 pos, wchar_t const * const format, DirectX::XMVECTOR color, ...)
{
	m_pos = pos;

	m_color = color;


	va_list arg_ptr;

	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);

}

