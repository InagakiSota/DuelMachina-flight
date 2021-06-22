///////////////////////////////
//�v���C�V�[���̑�������̃N���X
//�쐬���F2021�N5��9��
//�쐬�ҁFGT2_04_��_�D��
///////////////////////////////

#pragma once

#include <SimpleMath.h>
#include "Src/FrameWork/Sprite2D/Sprite2D.h"

class PlayScene;

class PlaySceneManual
{
public:
	//�R���X�g���N�^
	PlaySceneManual();
	//�f�X�g���N�^
	~PlaySceneManual();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Render();
	//�I������
	void Finalize();
	//�v���C�V�[���̃|�C���^�ݒ�
	void SetPlayScene(PlayScene* pPlayScene)
	{
		m_pPlayScene = pPlayScene;
	}

	//���~�t���O�̐ݒ�
	void SetIsManualDown(const bool& isManualDown)
	{
		m_isManualDown = isManualDown;
	}

private:
	//��������̉摜�̉���
	static const float MANUAL_SPRITE_WIDTH;
	//��������̉摜�̍���
	static const float MANUAL_SPRITE_HEIGHT;

	//��������̉摜�̎��
	enum class eMANUAL_SPRITE_TYPE
	{
		NONE = -1,

		KEYBOARD,		//�L�[�{�[�h
		COMMAND,		//�R�}���h

		SPRITE_NUM,		//�摜����
	};

	//��������摜
	std::unique_ptr<Sprite2D> m_pManualSprite[static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM)];
	//��������̉摜�̍��W
	DirectX::SimpleMath::Vector2 m_ManualSpritePos[static_cast<int>(eMANUAL_SPRITE_TYPE::SPRITE_NUM)];
	//��������㏸�t���O
	bool m_isManualUp;
	//����������~�t���O
	bool m_isManualDown;
	//��������E�ړ��t���O
	bool m_isManualRight;
	//����������ړ��t���O
	bool m_isManualLeft;
	//��������̃J�[�\���̉摜(�E)
	std::unique_ptr<Sprite2D> m_pManualCursorSpriteRight;
	//��������̃J�[�\���̉摜(��)
	std::unique_ptr<Sprite2D> m_pManualCursorSpriteLeft;

	//�v���C�V�[���̃|�C���^
	PlayScene* m_pPlayScene;
};

