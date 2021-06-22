///////////////////////////////////
//�L�����N�^�[�Q�̒����U��
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N11��22��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackBase.h"

class Character2AttackMiddleBottom : public CharacterAttackBase
{
public:
	//�R���X�g���N�^
	Character2AttackMiddleBottom();
	//�f�X�g���N�^
	~Character2AttackMiddleBottom();

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
	//�v���C���[��X�����̈ړ���(�㏸)
	static const float PLAYER_VEL_X_UP;
	//�v���C���[��X�����̈ړ���(���~)
	static const float PLAYER_VEL_X_DOWN;

};