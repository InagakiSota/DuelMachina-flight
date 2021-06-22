///////////////////////////////////
//�L�����N�^�[2�̃u�[�X�g�ړ���Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��16��
///////////////////////////////////

#pragma once
#include <SimpleMath.h>
#include "../../CharacterStateBase.h"

class CharacterBase;

class Character3BoostMoveState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character3BoostMoveState();
	//�f�X�g���N�^
	~Character3BoostMoveState();

	//������
	void Initialize(CharacterBase* pCharacter) override;
	//�X�V
	void Update();

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;
};
