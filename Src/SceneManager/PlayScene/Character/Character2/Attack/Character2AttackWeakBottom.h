///////////////////////////////////
//�L�����N�^�[�Q�̎㉺�U���N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��20��
///////////////////////////////////
#pragma once

#include "../../CharacterAttackBase.h"

class Character2AttackWeakBottom : public CharacterAttackBase
{
public:
	//�R���X�g���N�^
	Character2AttackWeakBottom();
	//�f�X�g���N�^
	~Character2AttackWeakBottom();

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
	//�U����
	static const int POWER;
	//X���W
	static const float POS_X;
	//�����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 COLL_SIZE;
	//������܂ł̎���
	static const float VANISH_TIME;
};