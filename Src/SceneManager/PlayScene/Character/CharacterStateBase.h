///////////////////////////////////
//�L�����N�^�[�̍U���̊��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��13��
///////////////////////////////////

#pragma once

#include "ICharacterState.h"

class CharacterBase;

class CharacterStateBase : public ICharacterState
{
public:
	~CharacterStateBase() {};
	//������
	void Initialize(CharacterBase* pCharacter) override {}
	//�X�V
	void Update() override {}

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;


};