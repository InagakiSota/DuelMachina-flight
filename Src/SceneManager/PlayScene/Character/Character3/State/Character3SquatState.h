///////////////////////////////////
//�L�����N�^�|2�̂��Ⴊ�ݏ�Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#pragma once

#include "../../CharacterStateBase.h"
#include <SimpleMath.h>

class CharacterBase;

class Character3SquatState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character3SquatState();
	//�f�X�g���N�^
	~Character3SquatState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;
	//�X�V
	void Update() override;

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;
};