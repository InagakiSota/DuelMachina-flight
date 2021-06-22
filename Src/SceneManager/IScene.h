///////////////////////////////////
//�V�[���̃C���^�[�t�F�[�X�N���X
//�쐬�ҁFGT2_04_��_�D��
//�쐬���F2021�N5��6��
///////////////////////////////////

#pragma once

#include <StepTimer.h>
#include "DeviceResources.h"
#include <CommonStates.h>

enum class eSCENE_STATE;

class IScene
{
public:
	//�f�X�g���N�^
	virtual ~IScene() {}

	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update(DX::StepTimer const& timer) = 0;
	//�`��
	virtual void Render() = 0;
	//�I������
	virtual void Finalize() = 0;

	//�J�����̐U��
	virtual void CameraShake(float duration, float magnitude) = 0;

	///////////////////////////////
	//�Q�b�^�[�A�Z�b�^�[
	//////////////////////////////
	//�f�o�C�X���\�[�X�̎擾
	virtual DX::DeviceResources* GetDeviceResources() = 0;
	//�R�����X�e�[�g�̎擾
	virtual DirectX::CommonStates* GetState() = 0;
	//�L�[�g���b�J�[�̎擾
	virtual DirectX::Keyboard::KeyboardStateTracker* GetKeyTracker() = 0;
	//�V�[���̃X�e�[�g�̎擾
	virtual eSCENE_STATE GetSceneState() = 0;
	//�V�[���̃X�e�[�g�̐ݒ�
	virtual void SetSceneState(const eSCENE_STATE& sceneState) = 0;
	//�t�F�[�h�̃^�C�}�[�̎擾
	virtual float GetFadeTimer() = 0;
	//�t�F�[�h�̃^�C�}�[�̐ݒ�
	virtual void SetFadeTimer(const float& fadeTimer) = 0;
	//�r���[�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetView() = 0;
	//�r���[�s��̐ݒ�
	virtual void SetView(const DirectX::SimpleMath::Matrix& view) = 0;
	//�ˉe�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetProj() = 0;
	//�ˉe�s��̐ݒ�
	virtual void SetProj(const  DirectX::SimpleMath::Matrix& proj) = 0;
	//�J�����̍��W�̎擾
	virtual DirectX::SimpleMath::Vector3 GetCameraPos() = 0;
	//�J�����̍��W�̐ݒ�
	virtual void SetCameraPos(const DirectX::SimpleMath::Vector3& cameraPos) = 0;
	//�J�����̒����_�̎擾
	virtual DirectX::SimpleMath::Vector3 GetTargetPos() const = 0;
	//�J�����̒����_�̐ݒ�
	virtual void SetTargetPos(const DirectX::SimpleMath::Vector3& targetPos) = 0;

	//����ID�̎擾
	virtual int GetSoundID() = 0;
	//����ID�̐ݒ�
	virtual void SetSoundID(const int& soundID) = 0;

};
