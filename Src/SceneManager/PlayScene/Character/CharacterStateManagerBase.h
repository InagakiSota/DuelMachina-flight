///////////////////////////////////
//�L�����N�^�[�̃X�e�[�g�Ǘ��N���X�̊��
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��17��
///////////////////////////////////

#pragma once
#include "CharacterState.h"
#include "CharacterStateBase.h"
#include "ICharacterStateManager.h"

class CharacterBase;

class CharacterStateManagerBase : public ICharacterStateManager
{
public:
	~CharacterStateManagerBase() {};

	//������
	void Initialize(CharacterBase* pCharacterBase) override {}
	//�X�V
	void Update(const eCHARACTER_STATE& charaState) override {}
	//�I������
	void Finalize() override {}


};
