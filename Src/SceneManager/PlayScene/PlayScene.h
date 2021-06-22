///////////////////////////////////
//�v���C�V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N6��19��
///////////////////////////////////

#pragma once
#include "../SceneBase.h"
#include <SimpleMath.h>
#include "Src\FrameWork\Collision\Collision.h"

#include "GeometricPrimitive.h"
#include "Manual/PlaySceneManual.h"

//�N���X�̑O���錾
class EffectManager;
class FbxModel;
class Sprite2D;
class DebugFont;
class ModelObject;
class Fbx;
class CharacterBase;
class DebugCamera;
class AttackManager;
class PlaySceneUI;

class FbxModel;
class ShadowManager;
class HitEffectManager;
class PlaySceneMenu;
class PlaySceneStateManager;

class PlayScene : public SceneBase
{
////////////////////////////////////
//�֐�
public:

	//�v���C�V�[���̃X�e�[�g
	enum class ePLAY_SCENE_STATE
	{
		NONE = -1,

		COUNT_DOWN,		//�J�E���g�_�E��
		MAIN,			//���C��
		TIME_UP,		//�^�C���A�b�v
		RESULT,			//���U���g

		OVER_ID
	};

	//���E���h
	enum class eROUND
	{
		NONE = -1,

		ROUND_1,		//���E���h�P
		ROUND_2,		//���E���h�Q
		ROUND_3,		//���E���h�R

		ROUND_NUM,		//�S���E���h��
	};

	//��������̉摜�̎��
	enum class eMANUAL_SPRITE_TYPE
	{
		NONE = -1,

		KEYBOARD,		//�L�[�{�[�h
		COMMAND,		//�R�}���h

		SPRITE_NUM,		//�摜����
	};
	//�v���C���[�̐�
	static const int PLAYER_NUM = 2;


	//�R���X�g���N�^
	PlayScene();
	//�f�X�g���N�^
	~PlayScene();			
	//������
	void Initialize() override;	
	//�X�V
	void Update(DX::StepTimer const& timer) override;			
	//�`��
	void Render() override;		
	//�I������
	void Finalize() override;

	//�v���C���[�̃|�C���^�̃Q�b�^�[
	CharacterBase* GetPlayer(const int& index)const
	{
		return m_pPlayer[index];
	}

	//�v���C���[�̏����{���̃Q�b�^�[
	int GetPlayerWinNum(const int& index)const
	{
		return m_playerWinNum[index];
	}
	//�v���C���[�̏����{���̃Z�b�^�[
	void SetPlayerWinNum(const int& index, const int& playerWinNum)
	{
		m_playerWinNum[index] = playerWinNum;
	}


	//���Ԃ̃Q�b�^�[
	float GetTime() const
	{
		return m_time;
	}
	//���Ԃ̃Z�b�^�[
	void SetTime(const float& time)
	{
		m_time = time;
	}
	//�v���C�V�[���̏�Ԃ̃Q�b�^�[
	PlayScene::ePLAY_SCENE_STATE GetPlaySceneState()const
	{
		return m_playSceneState;
	}
	//�v���C�V�[���̏�Ԃ̃Z�b�^�[
	void SetPlaySceneState(const PlayScene::ePLAY_SCENE_STATE& playSceneState)
	{
		m_playSceneState = playSceneState;
	}

	//���U���g��Ԃ��ǂ����̃t���O�̃Q�b�^�[
	bool GetIsResult()const
	{
		return m_isResult;
	}
	//���U���g��Ԃ��ǂ����̃t���O�̃Z�b�^�[
	void SetIsResult(const bool& isResult)
	{
		m_isResult = isResult;
	}
	//�J�E���g�_�E���̃^�C�}�[�̃Q�b�^�[
	float GetCountDownTimer()const
	{
		return m_countdownTimer;
	}
	//�J�E���g�_�E���̃^�C�}�[�̃Z�b�^�[
	void SetCountDownTimer(const float& countDownTimer)
	{
		m_countdownTimer = countDownTimer;
	}

	//���݂̃��E���h�̃Q�b�^�[
	eROUND GetNowRound()const
	{
		return m_nowRound;
	}
	//���݂̃��E���h�̃Z�b�^�[
	void SetNowRound(const eROUND& nowRound)
	{
		m_nowRound = nowRound;
	}
	
	//���Ԃ̎擾
	float GetTotalTime() const
	{
		return m_totalSeconds;
	}

	//���������ʂ̕\���t���O�̎擾
	bool GetIsManualDisplay()const
	{
		return m_isManualDisplay;
	}
	//���������ʂ̕\���t���O�̐ݒ�
	void SetIsManualDisplay(const bool& isManualDisplay)
	{
		m_isManualDisplay = isManualDisplay;
	}

	//��~�t���O�̎擾
	bool GetIsStop()const
	{
		return m_isStop;
	}
	//��~�t���O�̐ݒ�
	void SetIsStop(const bool& isStop)
	{
		m_isStop = isStop;
	}

	//�v���C���[�̎擾
	CharacterBase* GetPlayer(const int& index)
	{
		return m_pPlayer[index];
	}

	//���Z�b�g
	void Reset();
	//�������
	//���U���g
	void Result(DX::StepTimer const& timer);

////////////////////////////////////
//�ϐ��E�萔�E�񋓑�

private:
	//�v���C�V�[���̃X�e�[�g�ϐ�
	ePLAY_SCENE_STATE m_playSceneState;

	//�������邽�߂̎擾�{��
	static const int WIN_NUM = 2;

	DirectX::SimpleMath::Matrix m_spaceWorld;	//�V���̃��[���h�s��

	//�������Ԃ̍ő�l
	static const float TIME_MAX;
	//�^�C���A�b�v�V�[���̎���
	static const float TIME_UP_TIME;
	//���E���h�؂�ւ��̎���
	static const float ROUND_CHANGE_TIME;
	//�J�E���g�_�E���̎���
	static const float COUNT_DOWN_TIME;

	//std::unique_ptr<DirectX::CommonStates>m_states;
	//std::unique_ptr<DirectX::IEffectFactory>m_fxFactory;
	//std::unique_ptr<DirectX::Model>m_model;
	
	//3d���f��
	//std::unique_ptr<ModelObject>m_modelObject;//�v���C���[(���{)

	//�V��
	std::unique_ptr<ModelObject>m_space;		
	//�X�v���C�g								
	std::unique_ptr<Sprite2D> m_sprite2D;		


	//fbx
	//std::unique_ptr<Fbx> m_pFbx;

	////��
	//std::unique_ptr<DirectX::GeometricPrimitive> m_pFloor;
	////���̃��[���h�s��
	//DirectX::SimpleMath::Matrix m_floorWorld;
	////���̓����蔻��p�̔�
	//Collision::BoxCollision m_floorBox;

	//�v���C���[�̃|�C���^
	CharacterBase* m_pPlayer[PLAYER_NUM];

	//�f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_pDebugCamera;

	//�����̉e�̃G�t�F�N�g
	std::unique_ptr<ShadowManager> m_pShadowManager[PLAYER_NUM];
	
	//�U���̃}�l�[�W���[
	//std::unique_ptr<AttackManager> m_pAttackManager;

	FbxModel* m_pFbxModel;
	DirectX::SimpleMath::Matrix m_fbxModelWorld;

	//���݂̃��E���h
	eROUND m_nowRound;
	//�e�v���C���[�̏�����(���E���h�擾�{��)
	int m_playerWinNum[PLAYER_NUM];

	//��������
	float m_time;

	//�J�E���g�_�E���^�C�}�[
	float m_countdownTimer;

	//�̗͂̃o�b�t�@
	int m_playerHpBuffer[PLAYER_NUM];
	//�Q�[����~�t���O
	bool m_isStop;
	
	//���j���[�\���t���O
	bool m_isMenuDisplay;
	//��������\���t���O
	bool m_isManualDisplay;

	int m_menuCursor;
	//����
	float m_totalSeconds;
	//���U���g�ɑJ�ڂ����t���O
	bool m_isResult;

	//UI�N���X�̃|�C���^
	std::unique_ptr<PlaySceneUI> m_pPlaySceneUI;
	//���j���[�N���X�̃|�C���^
	std::unique_ptr<PlaySceneMenu> m_pPlaySceneMenu;
	//�v���C�V�[���̃X�e�[�g�}�l�[�W���[
	std::unique_ptr<PlaySceneStateManager> m_pPlaySceneStateManager;


};

