///////////////////////////////////
//�f�o�b�O�t�H���g
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N5��20��
///////////////////////////////////

#pragma once

#include "SpriteBatch.h"
#include "SimpleMath.h"

#include "SpriteFont.h"

#include "AlignedAllocationPolicy.h"



#define DEBUG_FONT_SINGLETON_TYPE 1

class DebugFont : public AlignedAllocationPolicy<16>
{
private:
	//�R���X�g���N�^
	DebugFont();


public:
	//������ő吔�T�C�Y
	static const size_t STRING_SIZE_MAX = 256;

	//�f�X�g���N�^
	~DebugFont();

	//����
	void Create(ID3D11Device1* device, ID3D11DeviceContext1* context);
	//�`��
	void Draw();
	//���Z�b�g
	void Reset();
	//�\�����o�^
	void Print(float posX, float posY, wchar_t const* const format , DirectX::XMVECTOR color, ...);
	void Print(DirectX::SimpleMath::Vector2 pos, wchar_t const* const format, DirectX::XMVECTOR color, ...);

#if DEBUG_FONT_SINGLETON_TYPE == 0


public:
	//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
	static DebugFont* GetInstance()
	{
		if (m_pInstance == nullptr)
		{
			//�I�u�W�F�N�g�𐶐����Am_pInstance�ϐ��Ɋi�[����
			m_pInstance = new DebugFont();
		}
		//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_pInstance;
	}

	//�I�u�W�F�N�g�ւ̎Q�Ƃ�Ԃ�
	static DebugFont& getRefInstance()
	{
		if (m_pInstance == nullptr)
		{
			//�I�u�W�F�N�g�𐶐����Am_pInstance�ϐ��Ɋi�[����
			m_pInstance = new DebugFont();
		}
		//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return *m_pInstance;
	}

	//�I�u�W�F�N�g��j������
	static void Dispose()
	{
		if (m_pInstance != nullptr)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static DebugFont* m_pInstance;


#elif DEBUG_FONT_SINGLETON_TYPE == 1
public:
	//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
	static DebugFont* GetInstance()
	{
		if (m_pInstance.get() == nullptr)
		{
			//�I�u�W�F�N�g�𐶐����Am_pInstance�ϐ��Ɋi�[����
			m_pInstance.reset(new DebugFont());

		}
		//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_pInstance.get();
	}
	//�I�u�W�F�N�g��j������
	static void Dispose()
	{
		if (m_pInstance)m_pInstance.reset();
	}

private:
	//�I�u�W�F�N�g�ւ̃|�C���^
	static std::unique_ptr<DebugFont> m_pInstance;



#else
private:
	//�I�u�W�F�N�g
	static DebugFont m_instance;

public:
	//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
	static DebugFont* GetInstance()
	{
		//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return &m_instance;
	}
	//�I�u�W�F�N�g�̎Q�Ƃ�Ԃ�
	static DebugFont& getRefInstance()
	{
		//�I�u�W�F�N�g�ւ̃|�C���^��Ԃ�
		return m_instance;
	}

#endif
private:
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont>  m_spriteFont;
	wchar_t* m_string;
	DirectX::SimpleMath::Vector2 m_pos;//���W

	DirectX::XMVECTOR m_color;			//�F

	////override the operator new/delete.
	//void* operator new(size_t i) {
	//	return _mm_malloc(i, 16);
	//}
	//void operator delete(void* p) {
	//	_mm_free(p);
	//}

};