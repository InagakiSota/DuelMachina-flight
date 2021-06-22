///////////////////////////////////
//�L�����N�^�[�R�̎�j���[�g����
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��23��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackBase.h"

class Character3AttackWeakNeutral : public CharacterAttackBase
{
public:
	//�R���X�g���N�^
	Character3AttackWeakNeutral();
	//�f�X�g���N�^
	~Character3AttackWeakNeutral();

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
	//������܂ł̎���
	static const float VANISH_TIME;
	//X���W
	static const float POS_X;
	//Y���W
	static const float POS_Y;
	//X�����̈ړ���
	static const float VEL_X;
	//�����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 COLL_SIZE;
	//�W�I���g���v���~�e�B�u�̃T�C�Y
	static const float GP_SIZE;
};