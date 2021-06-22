///////////////////////////////////
//�L�����N�^�[�P�̂����Ԃ̃N���X
//�쐬�ҁF�Ȃ�
//�쐬���F�Ȃ�
///////////////////////////////////
#pragma once

#include "../../CharacterStateBase.h"

class Character1DamageState : public CharacterStateBase
{
public:
	//�R���X�g���N�^
	Character1DamageState();
	//�f�X�g���N�^
	~Character1DamageState();

	//������
	void Initialize(CharacterBase* pCharacterBase) override;
	//�X�V
	void Update() override;

private:
	//�X�e�[�g���߂�܂ł̎���
	static const float STATE_BACK_TIME;
	//�m�b�N�o�b�N�̈ړ��ʂ̏����l
	static const float KNOCK_BACK_VEL_START;
	//�m�b�N�o�b�N�̈ړ���
	static const float KNOCK_BACK_VEL;
	//�L�����N�^�[�̃|�C���^
	CharacterBase* m_pCharacter;

};
