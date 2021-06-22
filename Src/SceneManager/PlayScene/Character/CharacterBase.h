///////////////////////////////////
//�L�����N�^�[�̊��N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��13��
///////////////////////////////////
#pragma once

#include <SimpleMath.h>
#include "GeometricPrimitive.h"
#include "Src\FrameWork\ModelObject\ModelObject.h"
#include "Src\FrameWork\Collision\Collision.h"
#include "Keyboard.h"
#include "AttackType.h"
#include "CharacterStateManagerBase.h"
#include "CharacterAttackManagerBase.h"
#include "HitEffectManager.h"
#include "BoostEffectManager.h"
#include "../../../FrameWork/ModelObject/ModelObject.h"
#include "ICharacter.h"
#include  "../../SceneBase.h"

//�O���錾
enum class ePLAYER_ID;
class AttackManager;
struct AttackStruct;
class FbxModel;
enum class eCHARACTER_STATE;
enum class eCHARACTER_ID;


class CharacterBase : public ICharacrter
{
public:

	//�ړ�����
	static const float MOVE_LIMIT_X;

	//�U���̎�ނ̐�
	static const int ATTACK_NUM = 32;
	//�d��
	static const float GRAVITY;
	//�J�����̍��W
	static const DirectX::SimpleMath::Vector3 CAMERA_POS;

	//�R���X�g���N�^
	CharacterBase(ePLAYER_ID playerID);
	//�f�X�g���N�^
	~CharacterBase();
	
	//������
	void Initialize() override;

	//�X�V
	void Update(DX::StepTimer const& timer) override;
	//�`��
	void  Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj) override;
	//�I������
	void Finalize() override;
	//���Ƃ̓����蔻��
	void HitFloor(const Collision::BoxCollision& floorColl) override;
	 //�G�̑̂Ƃ̓����蔻��
	void HitEnemyBody(const Collision::BoxCollision& enemyBodyColl, const Collision::BoxCollision& enemyHeadColl) override;
	 //�U���Ƃ̓����蔻��
	void HitAttack() override;
	//����
	void Ready(DX::StepTimer const& timer) override;
	//�s�k
	void Lose(DX::StepTimer const& timer) override;

	//���Z�b�g
	void Reset() override;


	////////////////////////////////
	//�Q�b�^�[�A�Z�b�^�[
	////////////////////////////////
	//�ړ�
	void Move() override {}

	//�v���C�V�[���̃|�C���^�̎擾
	void SetPlayScene(SceneBase* pPlayScene) override
	{
		m_pPlayScene = pPlayScene;
	}

	//3D���f���̃|�C���^�̎擾
	FbxModel* GetFbxModel() override
	{
		return m_pFbxModel;
	}
	//3D���f���̃|�C���^�̐ݒ�
	void SetFbxModel(FbxModel* pFbxModel) override
	{
		m_pFbxModel = pFbxModel;
	}

	//�������W�̐ݒ�
	 void SetStartPos(const DirectX::SimpleMath::Vector3& startPos) override
	 {
		 m_startPos = startPos;
		 m_pos = m_startPos;
	 }
	 //�������W�̎擾
	 DirectX::SimpleMath::Vector3 GetStartPos()override
	 {
		 return m_startPos;
	 }

	 //�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�̎擾
	 DirectX::SimpleMath::Vector3 GetHitEffectPos() override
	 {
		 return m_hitEffectPos;
	 }
	 //�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�̐ݒ�
	 void SetHitEffectPos(const DirectX::SimpleMath::Vector3& hitEffectPos) override
	 {
		 m_hitEffectPos = hitEffectPos;
	 }


	//�����̓����蔻��̔��̎擾
	 Collision::BoxCollision GetLegCollBox() override
	 {
		 return m_legCollBox;
	 }

	//�����̓����蔻��̔��̐ݒ�
	 void SetLegCollBox(const Collision::BoxCollision& legCollBox) override
	 {
		 m_legCollBox = legCollBox;
	 }

	//�̂̓����蔻��̔��̎擾
	 Collision::BoxCollision GetBodyCollBox() override
	 {
		 return m_bodyCollBox;
	 }

	//�̂̓����蔻��̔��̐ݒ�
	 void SetBodyCollBox(const Collision::BoxCollision& bodyCollBox) override
	 {
		 m_bodyCollBox = bodyCollBox;
	 }

	//���̓����蔻��̔��̎擾
	 Collision::BoxCollision GetHeadCollBox() override
	 {
		 return m_headCollBox;
	 }

	//���̓����蔻��̔��̐ݒ�
	 void SetHeadCollBox(const Collision::BoxCollision& headCollBox) override
	 {
		 m_headCollBox = headCollBox;
	 }

	//�U���}�l�[�W���[�̎擾
	 AttackManager* GetAttackManager() override
	 {
		 return m_pAttackManager;
	 }

	//�U���}�l�[�W���[�̐ݒ�
	 void SetAttackManager(AttackManager* pAttackManager) override
	 {
		 m_pAttackManager = pAttackManager;
	 }

	//�G�̍��W�̐ݒ�
	 void SetEnemyPos(const DirectX::SimpleMath::Vector3& enemyPos) override
	 {
		 m_enemyPos = enemyPos;
	 }

	//�G�̍��W�̎擾
	 DirectX::SimpleMath::Vector3 GetEnemyPos() override
	 {
		 return m_enemyPos;
	 }

	//�G�̃|�C���^�̎擾
	 void SetEnemy(CharacterBase* pEnemy) override
	 {
		 m_pEnemy = pEnemy;
	 }
	 //�G�̃|�C���^�̐ݒ�
	 CharacterBase* GetEnemy() override
	 {
		 return m_pEnemy;
	 }

	//���W�̎擾
	 DirectX::SimpleMath::Vector3 GetPos() override
	 {
		 return m_pos;
	 }

	//���W�̐ݒ�
	 void SetPos(const DirectX::SimpleMath::Vector3& pos) override
	 {
		 m_pos = pos;
	 }

	//Y���̊p�x�̎擾
	 float GetAngleY() override
	 {
		 return m_angleY;
	 }

	//Y���̊p�x�̐ݒ�
	 void SetAngleY(const float& angleY) override
	 {
		 m_angleY = angleY;
	 }
	//�ړ��ʂ̎擾
	 DirectX::SimpleMath::Vector3 GetVel() override
	 {
		 return m_vel;
	 }
	//�ړ��ʂ̐ݒ�
	 void SetVel(const DirectX::SimpleMath::Vector3& vel) override
	 {
		 m_vel = vel;
	 }
	//�L�����N�^�[�̃X�e�[�g�̎擾
	 eCHARACTER_STATE GetCharaState() override
	 {
		 return m_charaState;
	 }
	//�L�����N�^�[�̃X�e�[�g�̐ݒ�
	 void SetCharaState(const eCHARACTER_STATE& state) override
	 {
		 m_charaState = state;
	 }
	//�W�����v�t���O�̎擾
	 bool GetJumpFlag() override
	 {
		 return m_jumpFlag;
	 }
	//�W�����v�t���O�̐ݒ�
	 void SetJumpFlag(const bool& jumpFlag) override
	 {
		 m_jumpFlag = jumpFlag;
	 }
	//�_���[�W�^�C�}�[�̎擾
	 float GetDamageTimer() override
	 {
		 return m_damageTimer;
	 }
	//�_���[�W�^�C�}�[�̐ݒ�
	 void SetDamageTimer(const float& damageTimer) override
	 {
		 m_damageTimer = damageTimer;
	 }
	 //�O�����̃x�N�g���̎擾
	 DirectX::SimpleMath::Vector3 GetFrontVector() override
	 {
		 return m_frontVector;
	 }

	 //�O�����̃x�N�g���̐ݒ�
	 void SetFrontVector(const DirectX::SimpleMath::Vector3& frontVector) override
	 {
		 m_frontVector = frontVector;
	 }

	//�U���p�̑O�����̃x�N�g���̎擾
	 DirectX::SimpleMath::Vector3 GetAttackFront() override
	 {
		 return m_attackFront;
	 }
	//�U���p�̑O�����̃x�N�g���̐ݒ�
	 void SetAttackFront(const DirectX::SimpleMath::Vector3& attackFront) override
	 {
		 m_attackFront = attackFront;
	 }
	//�̗͂̎擾
	 int GetHP() override
	 {
		 return m_hp;
	 }
	//�̗͂̐ݒ�
	 void SetHP(const int& hp) override
	 {
		 m_hp = hp;
	 }
	 //�̗͂̃o�b�t�@�̎擾
	 int GetHPBuffer() override
	 {
		 return m_hpBuffer;
	 }
	 //�̗͂̃o�b�t�@�̐ݒ�
	 void SetHPBuffer(const int& hpBuffer) override
	 {
		 m_hpBuffer = hpBuffer;
	 }

	 //�ő�̗͂̐ݒ�
	 void SetHPMax(const int& hpMax)override
	 {
		 m_hpMax = hpMax;
	 }
	//�ő�̗͂̎擾
	 int GetMaxHP() override
	 {
		 return m_hpMax;
	 }
	//�u�[�X�g�e�ʂ̎擾
	 int GetBoostCap() override
	 {
		 return m_boostCap;
	 }
	//�u�[�X�g�e�ʂ̐ݒ�
	 void SetBoostCap(const int& boostCap) override
	 {
		 m_boostCap = boostCap;
	 }
	//�ő�u�[�X�g�e�ʂ̎擾
	 int GetMaxBoostCap() override
	 {
		 return m_boostCapMax;
	 }
	 //�ő�u�[�X�g�e�ʂ̐ݒ�
	 void SetMaxBoostCap(const int& boostCapMax) override
	 {
		 m_boostCapMax = boostCapMax;
	 }

	//�U���\���̂̃|�C���^�̎擾
	 AttackStruct* GetAttack() override
	 {
		 return m_pAttack;
	 }
	//�U���\���̂̃|�C���^�̐ݒ�
	 void SetAttack(AttackStruct* pAttack) override
	 {
		 m_pAttack = pAttack;
	 }
	//�U���̎g�p���̃t���O�̎擾
	 bool GetIsAttackUse(const int& index) override
	 {
		 return m_isAttackUse[index];
	 }
	//�U���̎g�p���̃t���O�̐ݒ�
	 void SetIsAttackUse(const int& index, bool flag) override
	 {
		 m_isAttackUse[index] = flag;
	 }
	//�U���̓��̓t���O�̎擾
	 bool GetIsAttackInput(const int& index) override
	 {
		 return m_isAttackInput[index];
	 }
	//�U���̓��̓t���O�̐ݒ�
	 void SetIsAttackInput(const int& index, bool flag) override
	 {
		 m_isAttackInput[index] = flag;
	 }
	//�v���C���[ID�̎擾
	 ePLAYER_ID GetPlayerID() override
	 {
		 return m_playerID;
	 }
	 //�L�����N�^�[��ID�̎擾
	 eCHARACTER_ID GetCharacterID() override
	 {
		 return m_characterID;
	 }
	 //�L�����N�^�[��ID�̐ݒ�
	 void SetCharacterID(const eCHARACTER_ID& characterID) override
	 {
		 m_characterID = characterID;
	 }
	 //�U�����̃t���O�̎擾
	 bool GetIsAttacking() override
	 {
		 return m_isAttacking;
	 }
	//�U�����̃t���O�̐ݒ�
	 void SetIsAttacking(const bool& isAttacking) override
	 {
		 m_isAttacking = isAttacking;
	 }
	//�X�e�b�v�^�C�}�[�̎擾
	 DX::StepTimer GetStepTimer() override
	 {
		 return m_stepTimer;
	 }
	 //���[���h�s��̎擾
	 DirectX::SimpleMath::Matrix GetWorldMatrix() override
	 {
		 return m_world;
	 }
	 //���[���h�s��̐ݒ�
	 void SetWorldMatrix(const DirectX::SimpleMath::Matrix& worldMatrix) override
	 {
		 m_world = worldMatrix;
	 }
	 //�V�[���h�̃��[���h�s��̎擾
	 DirectX::SimpleMath::Matrix GetShieldWorldMatrix() override
	 {
		 return m_shieldWorld;
	 }
	 //�V�[���h�̃��[���h�s��̐ݒ�
	 void SetShieldWorldMatrix(const DirectX::SimpleMath::Matrix& shieldWorldMatrix) override
	 {
		 m_shieldWorld = shieldWorldMatrix;
	 }

	 //�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^�擾
	 BoostEffectManager* GetBoostEffectManager() override
	 {
		 return m_pBoostEffectManager.get();
	 }

	/////////////////////////////////////

public:
	//�A�j���[�V�����̐؂�ւ�
	 void ChangeAnimation(const int& animationStack) override;

	 //�L�����̃X�e�[�g�Ǘ�
	 void StateManager() override;
	 //�U��
	 void Attack() override;

	 //CPU�̋���
	 void AI();

	 //�����蔻��̍X�V
	 void CollisionUpdate() {}



private:
	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;						
	//���W
	DirectX::SimpleMath::Vector3 m_pos;
	//�������W
	DirectX::SimpleMath::Vector3 m_startPos;
	//�q�b�g�G�t�F�N�g�̍��W
	DirectX::SimpleMath::Vector3 m_hitEffectPos;
	//�ړ���
	DirectX::SimpleMath::Vector3 m_vel;
	//3D���f��
	std::unique_ptr<ModelObject> m_pModel;
	//�����̔�
	std::unique_ptr<DirectX::GeometricPrimitive> m_pLegBox;		
	//�����̓����蔻��p�̍\����
	Collision::BoxCollision m_legCollBox;						
	//�����̔��̃��[���h�s��
	DirectX::SimpleMath::Matrix m_legBoxWorld;
	//�̂̔�
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBodyBox;
	//�̂̔�(���Ⴊ��)
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBodySquatBox;
	//�̂̓����蔻��p�̍\����
	Collision::BoxCollision m_bodyCollBox;
	//�̂̔��̃��[���h�s��
	DirectX::SimpleMath::Matrix m_bodyBoxWorld;
	//���̔�
	std::unique_ptr<DirectX::GeometricPrimitive> m_pHeadBox;
	//���̔��̓����蔻��\����
	Collision::BoxCollision m_headCollBox;
	//���̔��̃��[���h�s��
	DirectX::SimpleMath::Matrix m_headBoxWorld;
	//�O�����̃x�N�g��
	DirectX::SimpleMath::Vector3 m_frontVector;
	//�U���p�̑O�����̃x�N�g��
	DirectX::SimpleMath::Vector3 m_attackFront;
	//�G�̑̂Ɠ����������̃t���O
	bool m_isHitEnemyBody;
	//���W�̃o�b�t�@
	DirectX::SimpleMath::Vector3 m_posBuf;
	//�U���̃}�l�[�W���[�̃|�C���^
	AttackManager* m_pAttackManager;
	//�U���̍\���̂̃|�C���^
	AttackStruct* m_pAttack;
	//�G�̍��W
	DirectX::SimpleMath::Vector3 m_enemyPos;
	//�G�̃|�C���^
	CharacterBase* m_pEnemy;

	DirectX::SimpleMath::Vector4 m_bodyColor;
	//�e��Ԃ̃��f���̃|�C���^
	//FBX���f��
	FbxModel* m_pFbxModel;
	//�V�[���h�̃��f��
	FbxModel* m_pShieldModel;
	//�V�[���h�̃��f���̃��[���h�s��
	DirectX::SimpleMath::Matrix m_shieldWorld;
	//�W�����v�t���O
	bool m_jumpFlag;					
	//�v���C���[��ID(�v���C���[�P���Q��)
	ePLAYER_ID m_playerID;
	//�L�[�g���b�J�[�̃|�C���^
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_pKeyTracker;
	//�̗�
	int m_hp;
	//�̗͂̍ő�l
	int m_hpMax;
	//�̗͂̃o�b�t�@
	int m_hpBuffer;
	//�����Ԃ̃^�C�}�[
	float m_damageTimer;
	//Y���̊p�x
	float m_angleY;
	//AI�̃X�e�[�g�^�C�}�[
	float m_aiStateTiemer;
	//AI�̍U���^�C�}�[
	float m_aiAttackTimer;
	//AI�̃X�e�[�g
	int m_aiState;
	//�U�����g�p���Ă���t���O
	bool m_isAttackUse[static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM)];
	//�U���̓��̓t���O
	bool m_isAttackInput[static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM)];
	//�U�����̃t���O
	bool m_isAttacking;

	//�u�[�X�g�e��
	int m_boostCap;
	//�u�[�X�g�e�ʂ̍ő�l
	int m_boostCapMax;

	//�L�����̃X�e�[�g�ϐ�
	eCHARACTER_STATE m_charaState;
	//�v���C�V�[���̃|�C���^
	SceneBase* m_pPlayScene;
	//�X�e�[�g�}�l�[�W���[�̃|�C���^
	std::unique_ptr<CharacterStateManagerBase> m_pStateManager;
	//�U���}�l�[�W���[�̃|�C���^
	std::unique_ptr<CharacterAttackManagerBase> m_pCharacterAttackManager;
	//�q�b�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	std::unique_ptr<HitEffectManager> m_pHitEffectManager;
	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̃|�C���^
	std::unique_ptr<BoostEffectManager> m_pBoostEffectManager;

	//�e�̃W�I���g���v���~�e�B�u
	std::unique_ptr<DirectX::GeometricPrimitive> m_pBulletGP;
	//�e�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_bulletWorld;
	//�e�L�����N�^�[��ID
	eCHARACTER_ID m_characterID;
	//�^�C�}�[
	DX::StepTimer m_stepTimer;

};
