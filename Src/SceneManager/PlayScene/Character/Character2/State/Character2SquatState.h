///////////////////////////////////
//�L�����N�^�|2�̂��Ⴊ�ݏ�Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#pragma once

#include "../../CharacterStateBase.h"
#include <SimpleMath.h>

class CharacterBase;

class Character2SquatState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character2SquatState();
	//�f�X�g���N�^
	~Character2SquatState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;
	//�X�V
	void Update() override;

private:
	//�̂̓����蔻���Y���W
	static const float BODY_COLL_POS_Y;
	//���̓����蔻���Y���W
	static const float HEAD_COLL_POS_Y;
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;

};