///////////////////////////////////
//�L�����N�^�[�Z���N�g�V�[���̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��15��
///////////////////////////////////

#pragma once
#include "../SceneBase.h"
#include "Src\SceneManager\PlayScene\Character\CharacterID.h"
#include "../../FrameWork/FbxModel/FbxModel.h"

class Sprite2D;

class CharaSelectScene :
	public SceneBase
{
public:
	//�R���X�g���N�^
	CharaSelectScene();
	//�f�X�g���N�^
	~CharaSelectScene();

	//������
	void Initialize() override;		
	//�X�V
	void Update(DX::StepTimer const& timer)override;
	//�`��
	void Render()override;
	//�I������
	void Finalize()override;

	//�L�����N�^�[�̐�
	static const int CHARA_NUM = 3;


private:
	//�摜
	std::unique_ptr<Sprite2D> m_pSelectSprite;
	std::unique_ptr<Sprite2D> m_pCharacterSprite[static_cast<int>(eCHARACTER_ID::OVER_ID)];
	std::unique_ptr<Sprite2D> m_pCharaInfoSprite[static_cast<int>(eCHARACTER_ID::OVER_ID)];
	std::unique_ptr<Sprite2D> m_pCursolSprite;

	//�e�L�����N�^�[�̃��f��
	FbxModel* m_pCharacter1Model;
	FbxModel* m_pCharacter2Model;
	FbxModel* m_pCharacter3Model;

	//���f���̃��[���h�s��
	DirectX::SimpleMath::Matrix m_modelWorld[CHARA_NUM];
	//���f���̍��W
	static const DirectX::SimpleMath::Vector3 MODEL_POS;
	//���f���̐F
	static const DirectX::SimpleMath::Vector4 MODEL_COLOR;

	//���f���̉�]�p�x(Y)
	float m_modelAngleY;

	//�e�L�����N�^�[�̃��f���̃T�C�Y
	static const float MODEL_SIZE[CHARA_NUM];


	//�L�����N�^�[�̃A�C�R���̍��W�萔
	static const DirectX::SimpleMath::Vector2 CHARA1_ICON_POS;
	static const DirectX::SimpleMath::Vector2 CHARA2_ICON_POS;
	static const DirectX::SimpleMath::Vector2 CHARA3_ICON_POS;

	//�L�����N�^�[�̏��摜�̍��W
	static const  DirectX::SimpleMath::Vector2 CHARA_INFO_POS;

	//���ݑI�����Ă���L�����N�^�[
	int m_nowSelect;

	//�J�[�\���̍��W
	static const float CURSOL_POS;

	int count;

	//�������
	void Manual();

	//��������摜
	std::unique_ptr<Sprite2D> m_pManualSprite;
	//��������̉摜�̍��W
	DirectX::SimpleMath::Vector2 m_ManualSpritePos;
	//�Q�[����~�t���O
	bool m_isStop;
	//��������㏸�t���O
	bool m_isManualUp;
	//����������~�t���O
	bool m_isManualDown;
	//��������̉摜�̉���
	static const float MANUAL_SPRITE_WIDTH;
	//��������̉摜�̍���
	static const float MANUAL_SPRITE_HEIGHT;
	//�J�[�\���摜�̐F
	DirectX::SimpleMath::Vector4 m_cursorColor;

	//����ID
	int m_soundID;
};

