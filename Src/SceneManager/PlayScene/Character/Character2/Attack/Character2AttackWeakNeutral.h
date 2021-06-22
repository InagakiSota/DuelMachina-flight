///////////////////////////////////
//�L�����N�^�[�Q�̎�j���[�g�����U��
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��20��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackBase.h"

class Character2AttackWeakNeutral : public CharacterAttackBase
{
public:
	//�R���X�g���N�^
	Character2AttackWeakNeutral();
	//�f�X�g���N�^
	~Character2AttackWeakNeutral();

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
	//Y���W
	static const float POS_Y;
	//�����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 COLL_SIZE;
	//������܂ł̎���
	static const float VANISH_TIME;

};
