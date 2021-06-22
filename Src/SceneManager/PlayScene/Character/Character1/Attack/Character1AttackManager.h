///////////////////////////////////
//�L�����N�^�[�P�̍U���}�l�[�W���[�N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��13��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackManagerBase.h"

class CharacterAttackBase;

class Character1AttackManager : public CharacterAttackManagerBase
{
public:
	//�R���X�g���N�^
	Character1AttackManager();
	//�f�X�g���N�^
	~Character1AttackManager();

	//������
	void Initialize(CharacterBase* pCharacter) override;
	//�X�V
	void Update() override;
	//�`��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) override;
	//�I������
	void Finalize() override;
	//���Z�b�g
	void Reset() override;

private:
	std::unique_ptr<CharacterAttackBase> m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM)];


};


