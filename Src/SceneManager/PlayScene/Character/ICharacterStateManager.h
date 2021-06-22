///////////////////////////////
//�L�����N�^�[�̏�ԃ}�l�[�W���[�̃C���^�[�t�F�[�X�N���X
//�쐬���F2021�N5��4��
//�쐬�ҁFGT2_04_��_�D��
//////////////////////////////


#pragma once

class CharacterBase;
enum class eCHARACTER_STATE;

class ICharacterStateManager
{
public:

	//�f�X�g���N�^
	virtual ~ICharacterStateManager() {};

	//������
	virtual void Initialize(CharacterBase* pCharacterBase) = 0;
	//�X�V
	virtual void Update(const eCHARACTER_STATE& charaState) = 0;
	//�I������
	virtual void Finalize() = 0;

};
