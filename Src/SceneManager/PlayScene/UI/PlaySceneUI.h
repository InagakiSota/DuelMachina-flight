//////////////////////////
//�v���C�V�[����UI�N���X
//�쐬���F2021�N4��30��
//�쐬�ҁFGT2_04_��_�D��
/////////////////////////

#pragma once

#include <SimpleMath.h>
#include "../PlayScene.h"
#include "Src/FrameWork/Sprite2D/Sprite2D.h"

class PlayScene;

class PlaySceneUI
{
public:
	//�R���X�g���N�^
	PlaySceneUI();
	//�f�X�g���N�^
	~PlaySceneUI();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Render();
	//�I������
	void Finalize();
	//�摜�̓ǂݍ���
	void Load();
	//���Z�b�g
	void Reset();

	//�v���C�V�[���̎擾
	void SetPlayScene(PlayScene* pPlayScene)
	{
		m_pPlayScene = pPlayScene;
	}

private:
	//�v���C���[�̐�
	static const int PLAYER_NUM = 2;
	//�������邽�߂̎擾�{��
	static const int WIN_NUM = 2;

	//�̗̓o�[�̉���
	static const float HP_BAR_WIDTH;
	//�̗̓o�[�̍���
	static const float HP_BAR_HEIGHT;
	//�̗̓o�[�̃}�[�W��
	static const float HP_BAR_MARGIN;
	//�u�[�X�g�e�ʃo�[�̉���
	static const float BOOST_BAR_WIDTH;
	//�u�[�X�g�e�ʃo�[�̍���
	static const float BOOST_BAR_HEIGHT;
	//�J�E���g�_�E���̎���
	static const float COUNT_DOWN_TIME;
	//�J�E���g�_�E���摜�̍��W
	static const DirectX::SimpleMath::Vector2 COUNT_DOWN_SPRITE_POS;
	//�������Ԃ̍ő�l
	static const float TIME_MAX;
	//�����{���̉摜�̉���
	static const float WIN_NUM_SPRITE_WIDTH;
	//�����{���̉摜�̍���
	static const float WIN_NUM_SPRITE_HEIGHT;
	//�������Ԃ̉摜�̉���
	static const float TIME_SPRITE_WIDTH;
	//�������Ԃ̉摜�̍���
	static const float TIME_SPRITE_HEIGHT;
	//�������Ԃ̉摜��X���W
	static const float TIME_SPRITE_POS_X;
	//�̗̓o�[�̏������W
	static const DirectX::SimpleMath::Vector2 HP_BAR_POS[PLAYER_NUM];
	//�u�[�X�g�e�ʃo�[�̏������W
	static const DirectX::SimpleMath::Vector2 BOOST_BAR_POS[PLAYER_NUM];

	//�̗̓o�[
	std::unique_ptr<Sprite2D> m_pHPBar[PLAYER_NUM];
	//�̗̓o�[(�̗͒�)	
	std::unique_ptr <Sprite2D> m_pHPBarDanger[PLAYER_NUM];
	//�̗̓o�[�̔w�i
	std::unique_ptr<Sprite2D> m_pHPBarBack[PLAYER_NUM];

	//�̗̓o�[�̍��W
	DirectX::SimpleMath::Vector2 m_hpBarPos[PLAYER_NUM];
	//�̗̓o�[�̐؂���ʒu
	RECT m_hpBarRect[PLAYER_NUM];

	//�u�[�X�g�e�ʃo�[
	std::unique_ptr<Sprite2D> m_pBoostBar[PLAYER_NUM];
	//�u�[�X�g�e�ʃo�[(�I�[�o�[�q�[�g)
	std::unique_ptr<Sprite2D> m_pBoostOverHeatBar[PLAYER_NUM];
	//�u�[�X�g�e�ʃo�[�̔w�i
	std::unique_ptr<Sprite2D> m_pBoostBack[PLAYER_NUM];
	//�u�[�X�g�e�ʃo�[�̍��W
	DirectX::SimpleMath::Vector2 m_boostBarPos[PLAYER_NUM];
	//�u�[�X�g�e�ʃo�[�̐؂���ʒu
	RECT m_boostBarRect[PLAYER_NUM];

	//�����摜
	std::unique_ptr<Sprite2D> m_pWinSprite[PLAYER_NUM];
	//�����摜�̍��W
	DirectX::SimpleMath::Vector2 m_winSpritePos;

	//���E���h���̉摜
	std::unique_ptr<Sprite2D> m_pRoundSprite[static_cast<int>(PlayScene::eROUND::ROUND_NUM)];
	//FIGHT�̉摜
	std::unique_ptr<Sprite2D> m_pFightSprite;
	//�^�C���A�b�v�̉摜
	std::unique_ptr<Sprite2D> m_pTimeUpSprite;
	//�����������̉摜
	std::unique_ptr<Sprite2D> m_pDrawSprite;
	//�������Ԃ̉摜(��̈�)
	std::unique_ptr<Sprite2D> m_pTimeSpriteOne;
	//�������Ԃ̉摜(�\�̈�)
	std::unique_ptr<Sprite2D> m_pTimeSpriteTen;

	//�����{���̉摜
	std::unique_ptr<Sprite2D> m_pWinNumSprtie[PLAYER_NUM][WIN_NUM];
	//�����{���̉摜�̐؂���ʒu
	RECT m_winNumSpriteRect[PLAYER_NUM][WIN_NUM];
	//�����{���̉摜�̍��W
	DirectX::SimpleMath::Vector2 m_winNumSpritePos[PLAYER_NUM][WIN_NUM];
	//�v���C���[�̓���̃J�[�\��
	std::unique_ptr<Sprite2D> m_pOverHeadSprite[PLAYER_NUM];
	//�v���C���[�̓���̃J�[�\���̍��W
	DirectX::SimpleMath::Vector2 m_overHeadSpritePos[PLAYER_NUM];
	//�������Ԃ̉摜�̐؂���ʒu�@��̈�
	RECT m_timeSpriteOneRect;
	//�������Ԃ̉摜�̐؂���ʒu�@�\�̈�
	RECT m_timeSpriteTenRect;
	//�v���C�V�[���̃|�C���^
	PlayScene* m_pPlayScene;
	//���U���g��pushSpace�̉摜
	std::unique_ptr<Sprite2D> m_pPushSpaceResult;
	//���U���g��pushSpace�̉摜�̍��W
	static const DirectX::SimpleMath::Vector2 PUSH_SPACE_RESULT_POS;

};
