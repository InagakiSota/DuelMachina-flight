///////////////////////////////////
//�L�����N�^�[2�̑O�ړ���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��16��
///////////////////////////////////
#pragma once

#include "../../CharacterStateBase.h"

class CharacterBase;

class Character2MoveFrontState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character2MoveFrontState();
	//�f�X�g���N�^
	~Character2MoveFrontState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;

	//�X�V
	void Update() override;

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;

};