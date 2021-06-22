///////////////////////////////
//�L�����N�^�[�̍U���̃C���^�[�t�F�[�X�N���X
//�쐬���F2021�N5��4��
//�쐬�ҁFGT2_04_��_�D��
//////////////////////////////
#pragma once

#include "pch.h"
#include <SimpleMath.h>

class CharacterBase;

class ICharacterAttack
{
public:
	virtual ~ICharacterAttack() {}
	//������
	virtual void Initialize(CharacterBase* pCharacter) = 0;
	//�X�V
	virtual void Update() = 0;
	//�`��
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) = 0;
	//�I������
	virtual void Finalize() = 0;
	//���Z�b�g
	virtual void Reset() = 0;

};