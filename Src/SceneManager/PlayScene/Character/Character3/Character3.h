///////////////////////////////////
//�L�����N�^�[3�̃N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N7��13��
///////////////////////////////////
#pragma once

#include "../CharacterBase.h"
#include "Keyboard.h"
#include "Character3Params.h"

class Character3 : public CharacterBase
{
public:
	//�R���X�g���N�^
	Character3(ePLAYER_ID playerID);
	//�f�X�g���N�^
	~Character3();

	//������
	void Initialize() override;
	//�X�V
	void Update(DX::StepTimer const& timer) override;
	//�`��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) override;
	//�I��
	void Finalize() override;
	//���Ƃ̓����蔻��
	void HitFloor(const Collision::BoxCollision& floorColl) override;
	//�G�̑̂Ƃ̓����蔻��
	void HitEnemyBody(const Collision::BoxCollision& enemyBodyColl, const Collision::BoxCollision& enemyHeadColl) override;
	//�U���Ƃ̓����蔻��
	void HitAttack()override;

	//����
	void Ready(DX::StepTimer const& timer) override;
	//�s�k
	void Lose(DX::StepTimer const& timer) override;
	//���Z�b�g
	void Reset() override;

	//�A�j���[�V�����̐؂�ւ�
	void ChangeAnimation(const int& animationStack) override;

private:
	//�ړ�
	void Move();

	//�U��
	void Attack() override;
	//�L�����̃X�e�[�g�Ǘ�
	void StateManager() override;

	//AI
	void AI();

	//CharacterStateManagerBase* m_pStateManager;
	//�����蔻��̍X�V
	void CollisionUpdate() override;

};