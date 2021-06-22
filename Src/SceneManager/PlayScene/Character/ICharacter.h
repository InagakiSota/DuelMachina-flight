///////////////////////////////
//�L�����N�^�[�̃C���^�[�t�F�[�X�N���X
//�쐬���F2021�N5��4��
//�쐬�ҁFGT2_04_��_�D��
//////////////////////////////

#pragma once

#include <SimpleMath.h>
#include "StepTimer.h"
#include "Src/FrameWork/Collision/Collision.h"

//�O���錾
class AttackManager;
class CharacterBase;
enum class eCHARACTER_STATE;
enum class ePLAYER_ID;
enum class eCHARACTER_ID;
struct AttackStruct;
class FbxModel;
class BoostEffectManager;
class SceneBase;

class ICharacrter
{
public:
	//�f�X�g���N�^
	virtual ~ICharacrter() {}

	//������
	virtual void Initialize() = 0;
	//�X�V
	virtual void Update(DX::StepTimer const& timer) = 0;
	//�`��
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) = 0;
	//�I��
	virtual void Finalize() = 0;
	//���Ƃ̓����蔻��
	virtual void HitFloor(const Collision::BoxCollision& floorColl) = 0;
	//����
	virtual void Ready(DX::StepTimer const& timer) = 0;
	//�s�k
	virtual void Lose(DX::StepTimer const& timer) = 0;

	//���Z�b�g
	virtual void Reset() = 0;

	//�A�j���[�V�����̐؂�ւ�
	virtual void ChangeAnimation(const int& animationStack) = 0;

	//�L�����̃X�e�[�g�Ǘ�
	virtual void StateManager() = 0;
	//�U��
	virtual void Attack() = 0;
	
	//�����蔻��̍X�V
	virtual void CollisionUpdate() = 0;


	////////////////////////////////
	//�Q�b�^�[�A�Z�b�^�[
	////////////////////////////////
	//�v���C�V�[���̃|�C���^�̎擾
	virtual void SetPlayScene(SceneBase* pPlayScene) = 0;
	//3D���f���̃|�C���^�̎擾
	virtual FbxModel* GetFbxModel() = 0;
	//3D���f���̃|�C���^�̐ݒ�
	virtual void SetFbxModel( FbxModel* pFbxModel) = 0;
	//�������W�̐ݒ�
	virtual void SetStartPos(const DirectX::SimpleMath::Vector3& startPos) = 0;
	//�������W�̎擾
	virtual DirectX::SimpleMath::Vector3 GetStartPos() = 0;
	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�̎擾
	virtual DirectX::SimpleMath::Vector3 GetHitEffectPos() = 0;
	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�̐ݒ�
	virtual void SetHitEffectPos(const DirectX::SimpleMath::Vector3& hitEffectPos) = 0;
	//�����̓����蔻��̔��̎擾
	virtual Collision::BoxCollision GetLegCollBox() = 0;
	//�����̓����蔻��̔��̐ݒ�
	virtual void SetLegCollBox(const Collision::BoxCollision& legCollBox) = 0;
	//�̂̓����蔻��̔��̎擾
	virtual Collision::BoxCollision GetBodyCollBox() = 0;
	//�̂̓����蔻��̔��̐ݒ�
	virtual void SetBodyCollBox(const Collision::BoxCollision& bodyCollBox) = 0;
	//���̓����蔻��̔��̎擾
	virtual Collision::BoxCollision GetHeadCollBox() = 0;
	//���̓����蔻��̔��̐ݒ�
	virtual void SetHeadCollBox(const Collision::BoxCollision& headCollBox) = 0;
	//�G�̑̂Ƃ̓����蔻��
	virtual void HitEnemyBody(const Collision::BoxCollision& enemyBodyColl, const Collision::BoxCollision& enemyHeadColl) = 0;
	//�U���}�l�[�W���[�̎擾
	virtual AttackManager* GetAttackManager() = 0;
	//�U���}�l�[�W���[�̐ݒ�
	virtual void SetAttackManager(AttackManager* pAttackManager) = 0;
	//�U���Ƃ̓����蔻��
	virtual void HitAttack() = 0;
	//�G�̍��W�̐ݒ�
	virtual void SetEnemyPos(const DirectX::SimpleMath::Vector3& enemyPos) = 0;
	//�G�̍��W�̎擾
	virtual DirectX::SimpleMath::Vector3 GetEnemyPos() = 0;
	//�G�̃|�C���^�̎擾
	virtual void SetEnemy(CharacterBase* pEnemy) = 0;
	//�G�̃|�C���^�̐ݒ�
	virtual CharacterBase* GetEnemy() = 0;
	//���W�̎擾
	virtual DirectX::SimpleMath::Vector3 GetPos() = 0;
	//���W�̐ݒ�
	virtual void SetPos(const DirectX::SimpleMath::Vector3& pos) = 0;
	//Y���̊p�x�̎擾
	virtual float GetAngleY() = 0;
	//Y���̊p�x�̐ݒ�
	virtual void SetAngleY(const float& angleY) = 0;
	//�ړ��ʂ̎擾
	virtual DirectX::SimpleMath::Vector3 GetVel() = 0;
	//�ړ��ʂ̐ݒ�
	virtual void SetVel(const DirectX::SimpleMath::Vector3& vel) = 0;
	//�L�����N�^�[�̃X�e�[�g�̎擾
	virtual eCHARACTER_STATE GetCharaState() = 0;
	//�L�����N�^�[�̃X�e�[�g�̐ݒ�
	virtual void SetCharaState(const eCHARACTER_STATE& state) = 0;
	//�ڒn�t���O�̎擾
	virtual bool GetLandingFlag() = 0;
	//�ڒn�t���O�̐ݒ�
	virtual void SetLandingFlag(const bool& landingFlag) = 0;
	//�W�����v�t���O�̎擾
	virtual bool GetJumpFlag() = 0;
	//�W�����v�t���O�̐ݒ�
	virtual void SetJumpFlag(const bool& jumpFlag) = 0;
	//�_���[�W�^�C�}�[�̎擾
	virtual float GetDamageTimer() = 0;
	//�_���[�W�^�C�}�[�̐ݒ�
	virtual void SetDamageTimer(const float& damageTimer) = 0;
	//�O�����̃x�N�g���̎擾
	virtual DirectX::SimpleMath::Vector3 GetFrontVector() = 0;
	//�O�����̃x�N�g���̐ݒ�
	virtual void SetFrontVector(const DirectX::SimpleMath::Vector3& frontVector) = 0;
	//�U���p�̑O�����̃x�N�g���̎擾
	virtual DirectX::SimpleMath::Vector3 GetAttackFront() = 0;
	//�U���p�̑O�����̃x�N�g���̐ݒ�
	virtual void SetAttackFront(const DirectX::SimpleMath::Vector3& attackFront) = 0;
	//�̗͂̎擾
	virtual int GetHP() = 0;
	//�̗͂̐ݒ�
	virtual void SetHP(const int& hp) = 0;
	//�̗͂̃o�b�t�@�̎擾
	virtual int GetHPBuffer() = 0;
	//�̗͂̃o�b�t�@�̐ݒ�
	virtual void SetHPBuffer(const int& hpBuffer) = 0;
	//�ő�̗͂̐ݒ�
	virtual void SetHPMax(const int& hpMax) = 0;
	//�ő�̗͂̎擾
	virtual int GetMaxHP() = 0;
	//�u�[�X�g�e�ʂ̎擾
	virtual int GetBoostCap() = 0;
	//�u�[�X�g�e�ʂ̐ݒ�
	virtual void SetBoostCap(const int& boostCap) = 0;
	//�ő�u�[�X�g�e�ʂ̎擾
	virtual int GetMaxBoostCap() = 0;
	//�ő�u�[�X�g�e�ʂ̐ݒ�
	virtual void SetMaxBoostCap(const int& boostCapMax) = 0;
	//�U���\���̂̃|�C���^�̎擾
	virtual AttackStruct* GetAttack() = 0;
	//�U���\���̂̃|�C���^�̐ݒ�
	virtual void SetAttack(AttackStruct* pAttack) = 0;
	//�U���̎g�p���̃t���O�̎擾
	virtual bool GetIsAttackUse(const int& index) = 0;
	//�U���̎g�p���̃t���O�̐ݒ�
	virtual void SetIsAttackUse(const int& index, bool flag) = 0;
	//�U���̓��̓t���O�̎擾
	virtual bool GetIsAttackInput(const int& index) = 0;
	//�U���̓��̓t���O�̐ݒ�
	virtual void SetIsAttackInput(const int& index, bool flag) = 0;
	//�v���C���[ID�̎擾
	virtual ePLAYER_ID GetPlayerID() = 0;
	//�L�����N�^�[��ID�̎擾
	virtual eCHARACTER_ID GetCharacterID() = 0;
	//�L�����N�^�[��ID�̐ݒ�
	virtual void SetCharacterID(const eCHARACTER_ID& characterID) = 0;
	//�U�����̃t���O�̎擾
	virtual bool GetIsAttacking() = 0;
	//�U�����̃t���O�̐ݒ�
	virtual void SetIsAttacking(const bool& isAttacking) = 0;
	//�X�e�b�v�^�C�}�[�̎擾
	virtual DX::StepTimer GetStepTimer() = 0;
	//���[���h�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetWorldMatrix() = 0;
	//���[���h�s��̐ݒ�
	virtual void SetWorldMatrix(const DirectX::SimpleMath::Matrix& worldMatrix) = 0;
	//�V�[���h�̃��[���h�s��̎擾
	virtual DirectX::SimpleMath::Matrix GetShieldWorldMatrix() = 0;
	//�V�[���h�̃��[���h�s��̐ݒ�
	virtual void SetShieldWorldMatrix(const DirectX::SimpleMath::Matrix& shieldWorldMatrix) = 0;
	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�擾
	virtual BoostEffectManager* GetBoostEffectManager() = 0;

	/////////////////////////////////////



};
