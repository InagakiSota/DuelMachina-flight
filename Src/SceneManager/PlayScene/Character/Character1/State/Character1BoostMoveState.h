///////////////////////////////////
//�L�����N�^�[�P�̃u�[�X�g�ړ���Ԃ̃N���X
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��16��
///////////////////////////////////

#pragma once
#include <SimpleMath.h>
#include "../../CharacterStateBase.h"

class CharacterBase;

class Character1BoostMoveState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character1BoostMoveState();
	//�f�X�g���N�^
	~Character1BoostMoveState();

	//������
	void Initialize(CharacterBase* pCharacter) override;
	//�X�V
	void Update();

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;
};
