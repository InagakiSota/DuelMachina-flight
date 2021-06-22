///////////////////////////////////
//�L�����N�^�[�R�̒��j���[�g�����U���N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N11��23��
///////////////////////////////////

#pragma once

#include "../../CharacterAttackBase.h"
#include "../../HitEffectManager.h"


class Character3AttackMiddleNeutral : public CharacterAttackBase
{
public:
	//�R���X�g���N�^
	Character3AttackMiddleNeutral();
	//�f�X�g���N�^
	~Character3AttackMiddleNeutral();

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
	//X�����̈ړ���
	static const float VEL_X;
	//Y�����̈ړ���
	static const float VEL_Y;
	//������܂ł̎���
	static const float VANISH_TIME;
	//�W�I���g���v���~�e�B�u�̃T�C�Y
	static const float GP_SIZE;
	//�e���̐�
	static const int BALLISTIC_NUM = 10;
	//�����蔻��̃T�C�Y
	static const DirectX::SimpleMath::Vector3 COLL_SIZE;
	//�e���̃W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBallisticGPArray[BALLISTIC_NUM];
	//�e���̍��W
	DirectX::SimpleMath::Vector3 m_ballisticPos[BALLISTIC_NUM];
	//�e���̃��[���h�s��
	DirectX::SimpleMath::Matrix m_ballisticWorld[BALLISTIC_NUM];

};