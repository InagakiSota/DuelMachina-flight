///////////////////////////////////
//�L�����N�^�|2�̌�ړ���Ԃ̃N���X
//�쐬�ҁFGS305_��_
//�쐬���F2020�N10��22��
///////////////////////////////////

#pragma once

#include "../../CharacterStateBase.h"

class CharacterBase;
enum class eCHARACTER_STATE;

class Character3MoveBackState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character3MoveBackState();
	//�f�X�g���N�^
	~Character3MoveBackState();

	//������
	void Initialize(CharacterBase* pCharacter) override;
	//�X�V
	void Update() override;

private:
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;
};