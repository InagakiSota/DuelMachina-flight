///////////////////////////////////
//�L�����N�^�[�R�̍U���Ǘ��N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��22��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackManagerBase.h"

class Character3AttackManager : public CharacterAttackManagerBase
{
public:
	//�R���X�g���N�^
	Character3AttackManager();
	//�f�X�g���N�^
	~Character3AttackManager();

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