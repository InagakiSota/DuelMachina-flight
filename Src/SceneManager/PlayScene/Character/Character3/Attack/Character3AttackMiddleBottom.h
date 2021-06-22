///////////////////////////////////
//�L�����N�^�[�R�̒����U���N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��23��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackBase.h"

class Character3AttackMiddleBottom : public CharacterAttackBase
{
public:
	//�R���X�g���N�^
	Character3AttackMiddleBottom();
	//�f�X�g���N�^
	~Character3AttackMiddleBottom();

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
	//���˂����t���O
	bool m_isShot;

	//X���W
	static const float POS_X;
	//������܂ł̎���
	static const float VANISH_TIME;
	//�`���[�W�ɗv���鎞��
	static const float CHARAGE_TIME;

};