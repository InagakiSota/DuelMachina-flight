///////////////////////////////////
//�L�����N�^�[2�̂����Ԃ̃N���X
//�쐬�ҁF�Ȃ�
//�쐬���F�Ȃ�
///////////////////////////////////
#pragma once

#include "../../CharacterStateBase.h"

class Character3DamageState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character3DamageState();
	//�f�X�g���N�^
	~Character3DamageState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;
	//�X�V
	void Update() override;

private:
	//�X�e�[�g���߂�܂ł̎���
	static const float STATE_BACK_TIME;
	//�m�b�N�o�b�N�̈ړ��ʂ̏����l
	static const float KNOCK_BACK_VEL_START;
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;

};
