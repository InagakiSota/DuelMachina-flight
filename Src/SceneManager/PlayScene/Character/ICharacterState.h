///////////////////////////////
//�L�����N�^�[�̏�ԃ}�l�[�W���[�̃C���^�[�t�F�[�X�N���X
//�쐬���F2021�N5��4��
//�쐬�ҁFGT2_04_��_�D��
//////////////////////////////

#pragma once

class CharacterBase;

class ICharacterState
{
public:
	//�f�X�g���N�^
	virtual ~ICharacterState() {}

	//������
	virtual void Initialize(CharacterBase* pCharacter) = 0;
	//�X�V
	virtual void Update() = 0;

};