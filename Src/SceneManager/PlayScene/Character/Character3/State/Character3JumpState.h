///////////////////////////////////
//�L�����N�^�|2�̃W�����v��Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#pragma once

#include "../../CharacterStateBase.h"

class Character3JumpState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character3JumpState();
	//�f�X�g���N�^
	~Character3JumpState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;

	//�X�V
	void Update() override;

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;

};