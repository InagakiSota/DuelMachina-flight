///////////////////////////////////
//�L�����N�^�[�̍U���Ǘ��N���X�̊��
//�쐬�ҁFGS3_05_��_
//�쐬���F2020�N10��23��
///////////////////////////////////

#pragma once

#include "AttackType.h"
#include <SimpleMath.h>
#include "DeviceResources.h"
#include "ICharacterAttackManager.h"

class CharacterBase;
class CharacterAttackBase;

class CharacterAttackManagerBase : public ICharacterAttackManager
{
public:
	//�f�X�g���N�^
	~CharacterAttackManagerBase() {}

	//������
	void Initialize(CharacterBase* pCharacter) override {}
	//�X�V
	void Update() override {}
	//�`��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)override {}
	//�I������
	void Finalize()override {}
	//���Z�b�g
	void Reset()override {}

};
