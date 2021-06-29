///////////////////////////////////
//�V�[���̊��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////
#include "pch.h"
#include "SceneBase.h"
#include "Src/Cgdi.h"
#include <random>

//�R���X�g���N�^
SceneBase::SceneBase()
	:m_pDeviceResources(nullptr),
	m_pStates(nullptr),
	m_pKeyTracker(nullptr),
	m_fadeTimer(1.0f),
	m_sceneState(eSCENE_STATE::FADE_IN),
	m_view{},
	m_proj{},
	m_cameraPos{},
	m_targetPos{},
	m_isShake(false),
	m_soundID(0),
	m_shakeDuration(0.0f),
	m_shakeMagnitude(0.0f)
{
}

//�f�X�g���N�^
SceneBase::~SceneBase()
{
	m_pKeyTracker.reset();
	m_pDeviceResources = nullptr;
	m_pStates = nullptr;

}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneBase::Initialize()
{
	m_pDeviceResources = gdi->GetDeviceResources();
	m_pStates = gdi->GetStates();

	auto device = m_pDeviceResources->GetD3DDevice();
	auto context = m_pDeviceResources->GetD3DDeviceContext();

	//�L�[�g���b�J�[�̍쐬
	m_pKeyTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	//�V�[���̃X�e�[�g�ݒ�
	m_sceneState = eSCENE_STATE::FADE_IN;

	//�r���[�s����쐬
	m_cameraPos = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 6.0f);
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_cameraPos, m_targetPos, DirectX::SimpleMath::Vector3::UnitY);

	//��ʃT�C�Y���擾����
	RECT outputSize = m_pDeviceResources->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);

	//�ˉe�s����쐬
	m_proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(DirectX::XM_PI / 4.0f, float(backBufferWidth) / float(backBufferHeight), 0.01f, 1000.0f);

}

///////////////////////////
//�X�V
//����:�X�e�b�v�^�C�}�[
//�߂�l:�Ȃ�
//////////////////////////
void SceneBase::Update(DX::StepTimer const& timer)
{
	//�L�[�{�[�h�̏�Ԃ̎擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	m_pKeyTracker->Update(keyState);


	//if(m_isShake == false)
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_cameraPos, m_targetPos, DirectX::SimpleMath::Vector3::UnitY);
	DoShake(timer);
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneBase::Render()
{

}

///////////////////////////
//�I������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void SceneBase::Finalize()
{

}

///////////////////////////
//�J�����̐U��
//����:�X�e�b�v�^�C�}�[�A�U�����鎞�ԁA�U�����鋭��
//�߂�l:�Ȃ�
//////////////////////////
void SceneBase::CameraShake(float duration, float magnitude)
{
	if (m_isShake == false)
	{
		//�J�����̐U�������s
		//DoShake(timer, duration, magnitude);
		m_isShake = true;

		//�U�����鎞�Ԃ̐ݒ�
		m_shakeDuration = duration;
		//�U�����鋭���̐ݒ�
		m_shakeMagnitude = magnitude;
	}
}

///////////////////////////
//�J�����̐U�������s
//����:�X
//�߂�l:
//////////////////////////
void SceneBase::DoShake(DX::StepTimer const& timer)
{
	////�������W���擾
	//DirectX::SimpleMath::Vector3 pos = m_cameraPos;
	//DirectX::SimpleMath::Vector3 targetPos = m_targetPos;
	
	if (m_isShake == true)
	{
		//�o�ߎ���
		static float elapsed = 0.0f;
		//�I�����ԂɂȂ�܂ŌJ��Ԃ�

		//X��Y�����Ƀ����_���Ɉړ�������
		std::random_device rnd;
		
		float x = ((rnd() % 3) - 1.0f) * m_shakeMagnitude;
		float y = ((rnd() % 3) - 1.0f) * m_shakeMagnitude;
		
		//�J�������W�����炷
		DirectX::SimpleMath::Vector3 pos = DirectX::SimpleMath::Vector3(x, y, 0.0f);
		////�J�����̒����_�����炷
		DirectX::SimpleMath::Vector3 targetPos = DirectX::SimpleMath::Vector3(x, y, 0.0f);
		//m_targetPos = DirectX::SimpleMath::Vector3(targetPos.x + 0.1, targetPos.y, targetPos.z);
		//�r���[�s����쐬
		m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
			m_cameraPos + pos, 
			m_targetPos + targetPos, 
			DirectX::SimpleMath::Vector3::UnitY);

		
		//�o�ߎ��Ԃ����Z����
		elapsed += static_cast<float>(timer.GetElapsedSeconds());

		if (elapsed > m_shakeDuration)
		{
			//�������W�ɖ߂�
			m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
				m_cameraPos,
				m_targetPos,
				DirectX::SimpleMath::Vector3::UnitY);
		 
			//�J�����̐U���t���O������
			m_isShake = false;
			elapsed = 0.0f;

			m_shakeDuration = 0.0f;
			m_shakeMagnitude = 0.0f;
		}
	}
}


