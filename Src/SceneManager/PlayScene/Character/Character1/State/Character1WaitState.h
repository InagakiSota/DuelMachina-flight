///////////////////////////////////
//�L�����N�^�[�P�̑҂���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#pragma once

#include "../../CharacterStateBase.h"

class Character1WaitState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character1WaitState();
	//�f�X�g���N�^
	~Character1WaitState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;
	//�X�V
	void Update() override;

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;

};

