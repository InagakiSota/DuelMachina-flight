///////////////////////////////////
//�V�[���̊��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////

#pragma once
#include "DeviceResources.h"
#include "StepTimer.h"
#include "Keyboard.h"
#include <SimpleMath.h>
#include <CommonStates.h>
#include "IScene.h"

//�V�[���̃X�e�[�g
enum class eSCENE_STATE
{
	NONE = -1,

	FADE_IN,
	MAIN,
	FADE_OUT,

	OVER,
};

class SceneBase : public IScene
{
public:	

	//�R���X�g���N�^
	SceneBase();
	//�f�X�g���N�^
	~SceneBase();

	//������
	void Initialize() override;
	//�X�V
	void Update(DX::StepTimer const& timer) override;
	//�`��
	void Render() override;
	//�I������
	void Finalize() override;

	//�J�����̐U��
	void CameraShake(float duration, float magnitude) override;
	//�J�����̐U�������s
	void DoShake(DX::StepTimer const& timer);

	//�f�o�C�X���\�[�X�̎擾
	DX::DeviceResources* GetDeviceResources() override
	{
		return m_pDeviceResources;
	}
	//�R�����X�e�[�g�̎擾
	DirectX::CommonStates* GetState() override
	{
		return m_pStates;
	}
	//�L�[�g���b�J�[�̎擾
	DirectX::Keyboard::KeyboardStateTracker* GetKeyTracker() override
	{
		return m_pKeyTracker.get();
	}
	//�V�[���̃X�e�[�g�̎擾
	eSCENE_STATE GetSceneState() override
	{
		return m_sceneState;
	}
	//�V�[���̃X�e�[�g�̐ݒ�
	void SetSceneState(const eSCENE_STATE& sceneState) override
	{
		m_sceneState = sceneState;
	}
	//�t�F�[�h�̃^�C�}�[�̎擾
	float GetFadeTimer() override
	{
		return m_fadeTimer;
	}
	//�t�F�[�h�̃^�C�}�[�̐ݒ�
	void SetFadeTimer(const float& fadeTimer) override
	{
		m_fadeTimer = fadeTimer;
	}

	//�r���[�s��̎擾
	DirectX::SimpleMath::Matrix GetView() override
	{
		return m_view;
	}
	//�r���[�s��̐ݒ�
	void SetView(const DirectX::SimpleMath::Matrix& view) override
	{
		m_view = view;
	}
	//�ˉe�s��̎擾
	DirectX::SimpleMath::Matrix GetProj() override
	{
		return m_proj;
	}
	//�ˉe�s��̐ݒ�
	void SetProj(const  DirectX::SimpleMath::Matrix& proj) override
	{
		m_proj = proj;
	}
	//�J�����̍��W�̎擾
	DirectX::SimpleMath::Vector3 GetCameraPos() override
	{
		return m_cameraPos;
	}
	//�J�����̍��W�̐ݒ�
	void SetCameraPos(const DirectX::SimpleMath::Vector3& cameraPos) override
	{
		m_cameraPos = cameraPos;
	}
	//�J�����̒����_�̎擾
	DirectX::SimpleMath::Vector3 GetTargetPos() const override
	{
		return m_targetPos;
	}
	//�J�����̒����_�̐ݒ�
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos) override
	{
		m_targetPos = targetPos;
	}

	//����ID�̎擾
	int GetSoundID() override
	{
		return m_soundID;
	}
	//����ID�̐ݒ�
	void SetSoundID(const int& soundID) override
	{
		m_soundID = soundID;
	}

private:

	//�f�o�C�X���\�[�X
	DX::DeviceResources* m_pDeviceResources;
	//�R�����X�e�[�g
	DirectX::CommonStates* m_pStates;

	//�L�[�g���b�J�[
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_pKeyTracker;
	//�V�[���̃X�e�[�g�ϐ�
	eSCENE_STATE m_sceneState;
	//�t�F�[�h�̃^�C�}�[
	float m_fadeTimer;
	//�r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	//�ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;
	//�J�����̍��W
	DirectX::SimpleMath::Vector3 m_cameraPos;
	//�J�����̒����_
	DirectX::SimpleMath::Vector3 m_targetPos;


	//����ID
	int m_soundID;
	//�J�����U���̃t���O
	bool m_isShake;
	
	//�J�����U���̎���
	float m_shakeDuration;
	//�J�����U���̋���
	float m_shakeMagnitude;


};