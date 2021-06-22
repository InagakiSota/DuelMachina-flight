///////////////////////////////
//�v���C�V�[���̃��j���[�̃N���X
//�쐬���F2021�N5��9��
//�쐬�ҁFGT2_04_��_�D��
///////////////////////////////

#pragma once

#include <SimpleMath.h>
#include "Src/FrameWork/Sprite2D/Sprite2D.h"

class PlayScene;
class PlaySceneManual;

//���j���[�̃J�[�\���̏ꏊ
enum class eMENU_CURSOR
{
	NONE = -1,

	MANUAL,			//�������
	CHARA_SELECT,	//�L�����N�^�[�Z���N�g
	EXIT,			//�Q�[���I��

	OVER_ID
};

class PlaySceneMenu
{
public:
	//�R���X�g���N�^
	PlaySceneMenu();
	//�f�X�g���N�^
	~PlaySceneMenu();

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


private:


	//�v���C�V�[���̃|�C���^
	PlayScene* m_pPlayScene;
	//���j���[�̉摜
	std::unique_ptr<Sprite2D> m_pMenuSprite;
	//���j���[�̃J�[�\���摜
	std::unique_ptr<Sprite2D> m_pMenuCursorSprite;
	//���j���[�\���t���O
	bool m_isMenuDisplay;

	int m_menuCursor;
	//�J�[�\���̍��W
	static const DirectX::SimpleMath::Vector2 MENU_CURSOR_POS[static_cast<int>(eMENU_CURSOR::OVER_ID)];
	//��������N���X�̃|�C���^
	std::unique_ptr<PlaySceneManual> m_pPlaySceneManual;
};

