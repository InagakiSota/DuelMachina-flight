///////////////////////////////////
//�L�����N�^�|�P�̂��Ⴊ�ݏ�Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#pragma once

#include "../../CharacterStateBase.h"
#include <SimpleMath.h>

class CharacterBase;

class Character1SquatState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character1SquatState();
	//�f�X�g���N�^
	~Character1SquatState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;
	//�X�V
	void Update() override;

private:
	//Y���̊p�x(�}�C�i�X)
	static const float ANGLE_Y_MINUS;
	//Y���̊p�x(�v���X)
	static const float ANGLE_Y_PLUS;
	//�̂̓����蔻���Y���W
	static const float BODY_COLL_BOX_POS_Y;
	//���̓����蔻���Y���W
	static const float HEAD_COLL_BOX_POS_Y;
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;


};