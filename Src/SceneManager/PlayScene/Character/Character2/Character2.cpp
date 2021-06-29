///////////////////////////////////
//�L�����N�^�[2�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��13��
///////////////////////////////////
#include "pch.h"
#include "Character2.h"
#include "GamePad.h"
#include "../../../PlayerID.h"
#include "../../AttackManager/AttackManager.h"
#include "Src\FrameWork\FbxModel\FbxModel.h"
#include "../CharacterState.h"
#include "State\Character2StateManager.h"
#include "Attack\Character2AttackManager.h"
#include "Character2Params.h"
#include "../ChracterAnimationNumber.h"

#include "Adx2.h"
#include "CueSheet_0.h"
#include "../../../../FrameWork/FbxResourceManager/FbxResourceManager.h"
#include "../CharacterID.h"
#include "Src/Cgdi.h"


//�R���X�g���N�^
Character2::Character2(ePLAYER_ID playerID)
	:	//���N���X�̃R���X�g���N�^
	CharacterBase::CharacterBase(playerID)
{
	//���g�̃L�����N�^�[��ID��ݒ�
	SetCharacterID(eCHARACTER_ID::CHARACTER_2);
}

//�f�X�g���N�^
Character2::~Character2()
{
	//���N���X�̃f�X�g���N�^
	CharacterBase::~CharacterBase();

}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Initialize()
{
	//���N���X�̏�����
	CharacterBase::Initialize();

	SetFbxModel(FbxResourceManager::GetInstance()->GetModel(eCHARACTER_ID::CHARACTER_2));

	//�X�e�[�^�X�̓ǂݍ���
	Character2Params::GetInstance()->LoadStatusData();


	//�����̓����蔻��̔��̐ݒ�
	Collision::BoxCollision legCollBox = GetLegCollBox();
	legCollBox.size_h = Character2Params::LEG_COLL_SIZE;
	legCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.7f, GetPos().z);
	SetLegCollBox(legCollBox);

	//�̂̓����蔻��̔��̓ǂݍ���
	Collision::BoxCollision bodyCollBox = GetBodyCollBox();
	bodyCollBox.size_h = Character2Params::BODY_COLL_SIZE_NORMAL;
	bodyCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 0.9f, GetPos().z);
	SetBodyCollBox(bodyCollBox);

	//���̓����蔻��̔��̓ǂݍ���
	Collision::BoxCollision headCollBox = GetBodyCollBox();
	headCollBox.size_h = Character2Params::HEAD_COLL_SIZE;
	headCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y, GetPos().z);
	SetHeadCollBox(headCollBox);

	//�O�����̐ݒ�
	SetFrontVector(Character2Params::FRONT_VECTOR);

	//�̗͂̐ݒ�
	SetHP(Character2Params::GetInstance()->MAX_HP);
	//�̗͂̍ő�l�̐ݒ�
	SetHPMax(Character2Params::GetInstance()->MAX_HP);
	//�u�[�X�g�e�ʂ̏�����
	SetBoostCap(Character2Params::GetInstance()->BOOST_CAP_MAX);
	//�u�[�X�g�e�ʂ̍ő�l�̐ݒ�
	SetMaxBoostCap(Character2Params::GetInstance()->BOOST_CAP_MAX);
	//�̗͂̃o�b�t�@�̐ݒ�
	SetHPBuffer(GetHP());
	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�ݒ�
	SetHitEffectPos(DirectX::SimpleMath::Vector3(
		GetPos().x, GetPos().y + Character2Params::HIT_EFFECT_POS_Y, GetPos().z));

	//Y���̊p�x�ݒ�
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1)SetAngleY(Character2Params::ANGLE_Y);
	if (GetPlayerID() == ePLAYER_ID::PLAYER_2)SetAngleY(-180.0f + Character2Params::ANGLE_Y);

	//���W���s��ɕϊ�
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPos());
	//�T�C�Y���s��ɕϊ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(Character2Params::MODEL_SIZE);
	//Y���̊p�x���s��ɕϊ�
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(GetAngleY());
	//���[���h�s��ɉ��Z
	SetWorldMatrix(scale * rotY * trans);

}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Update(DX::StepTimer const& timer)
{	
	//�ړ�����
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1 && GetCharaState() != eCHARACTER_STATE::DAMAGE)Move();
	
	//���N���X�̍X�V
	CharacterBase::Update(timer);

	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�ݒ�
	SetHitEffectPos(DirectX::SimpleMath::Vector3(
		GetPos().x, GetPos().y + Character2Params::HIT_EFFECT_POS_Y, GetPos().z));

	//�u�[�X�g�ړ��łȂ���΃u�[�X�g�e�ʂ𑝂₷
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		SetBoostCap(GetBoostCap() + 1);
		//�ő�l�ȏ�ɂȂ�����ő�l����
		if (GetBoostCap() >= Character2Params::GetInstance()->BOOST_CAP_MAX)
		{
			SetBoostCap(Character2Params::GetInstance()->BOOST_CAP_MAX);
		}
	}

	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	if (GetFrontVector().x > 0)
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x - Character2Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character2Params::BOOST_EFFECT_POS_Y,
				0.0f), Character2Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character2Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character2Params::BOOST_EFFECT_POS_Y,
				0.0f), Character2Params::BOOST_EFFECT_ANGLE_RIGHT);

	}

	//�����蔻��̍X�V
	Character2::CollisionUpdate();
}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{	
	//���N���X�̕`��
	CharacterBase::Render(view, proj);
}

///////////////////////////
//�I��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Finalize()
{
	//���N���X�̏I������
	CharacterBase::Finalize();
}

///////////////////////////
//���Ƃ̓����蔻��
//����:���̓����蔻��\����
//�߂�l:�Ȃ�
//////////////////////////
void Character2::HitFloor(const Collision::BoxCollision& floorColl)
{
	//���Ƃ̓����蔻��
	CharacterBase::HitFloor(floorColl);
}


///////////////////////////
//�G�̑̂Ƃ̓����蔻��
//����:�G�̑̂̓����蔻��
//�߂�l:�Ȃ�
//////////////////////////
void Character2::HitEnemyBody(const Collision::BoxCollision & enemyBodyColl, const Collision::BoxCollision& enemyHeadColl)
{
	//�G�̑̂Ƃ̓����蔻��
	CharacterBase::HitEnemyBody(enemyBodyColl, enemyHeadColl);
}

///////////////////////////
//�U���Ƃ̓����蔻��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::HitAttack()
{
	//�U���Ƃ̓����蔻��
	CharacterBase::HitAttack();
}

///////////////////////////
//����
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Ready(DX::StepTimer const& timer)
{
	//�ړ�����
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1 && GetCharaState() != eCHARACTER_STATE::DAMAGE)Move();
	//���N���X�̏����֐�
	CharacterBase::Ready(timer);

	//�u�[�X�g�ړ��łȂ���΃u�[�X�g�e�ʂ𑝂₷
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		SetBoostCap(GetBoostCap() + 1);
		//�ő�l�ȏ�ɂȂ�����ő�l����
		if (GetBoostCap() >= Character2Params::GetInstance()->BOOST_CAP_MAX)
		{
			SetBoostCap(Character2Params::GetInstance()->BOOST_CAP_MAX);
		}
	}
	
	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	if (GetFrontVector().x > 0)
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x - Character2Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character2Params::BOOST_EFFECT_POS_Y,
				0.0f), Character2Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character2Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character2Params::BOOST_EFFECT_POS_Y,
				0.0f), Character2Params::BOOST_EFFECT_ANGLE_RIGHT);

	}


	//�����蔻��̍X�V
	Character2::CollisionUpdate();

}

///////////////////////////
//�s�k
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Lose(DX::StepTimer const & timer)
{
	//���N���X�̔s�k�֐�
	CharacterBase::Lose(timer);

	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	if (GetFrontVector().x > 0)
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x - Character2Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character2Params::BOOST_EFFECT_POS_Y,
				0.0f), Character2Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character2Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character2Params::BOOST_EFFECT_POS_Y,
				0.0f), Character2Params::BOOST_EFFECT_ANGLE_RIGHT);

	}

	//�����蔻��̍X�V
	Character2::CollisionUpdate();

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Reset()
{	
	//���N���X�̃��Z�b�g�֐�
	CharacterBase::Reset();
	//�u�[�X�g�e�ʂ�)
	SetBoostCap(Character2Params::GetInstance()->BOOST_CAP_MAX);

}

///////////////////////////
//�A�j���[�V�����̐؂�ւ�
//����:�؂�ւ���A�j���[�V�����̔ԍ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::ChangeAnimation(const int & animationStack)
{
	//�A�j���[�V�����̐؂�ւ�
	GetFbxModel()->ChangeAnimation(animationStack);
}


///////////////////////////
//�ړ�
//����:0
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Move()
{
	//�L�[�̏�Ԏ擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Vector3 vel = GetVel();

	//�K�[�h��Ԃ������ԂłȂ���Έړ�
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE &&
		GetCharaState() != eCHARACTER_STATE::DAMAGE &&
		GetCharaState() != eCHARACTER_STATE::GUARD)
	{
		//�E���͂��ړ��������ɂ�����ړ�
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) &&
			(GetPos().x <= Character2Params::MOVE_LIMIT_X))
		{
			vel.x = 1;
		}
		//�����͂��ړ��������ɂ�����ړ�
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) &&
			(GetPos().x >= -Character2Params::MOVE_LIMIT_X))
		{
			vel.x = -1;
		}
		else vel.x = 0.0f;

		//����͂��ړ��������ɂ�����ړ�
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) && GetPos().y < Character2Params::MOVE_LIMIT_TOP)
		{
			vel.y = 1;
		}
		//�����͂��ړ��������ɂ�����ړ�
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) && GetPos().y > Character2Params::MOVE_LIMIT_BOTTOM)
		{
			vel.y = -1;
		}
		else vel.y = 0.0f;

		vel.Normalize();

		SetVel(vel * Character2Params::GetInstance()->MOVE_FRONT_FORCE);
	}

}

///////////////////////////
//�U��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::Attack()
{
	//���N���X�̍U���Ǘ��֐�
	CharacterBase::Attack();
}

///////////////////////////
//�X�e�[�g�̊Ǘ�
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::StateManager()
{
	//���N���X�̃X�e�[�g�Ǘ��֐�
	CharacterBase::StateManager();
}

///////////////////////////
//AI�̏���
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::AI()
{
	//���N���X��AI�֐�
	CharacterBase::AI();
}


///////////////////////////
//�����蔻��̍X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character2::CollisionUpdate()
{
	//�v���C���[��Y���̊p�x
//�G���������E�ɉE�ɂ�����E������
	if (GetPos().x < GetEnemyPos().x )
	{
		//�����Ă��������ς���
		SetAngleY(Character2Params::ANGLE_Y);
		//�O�����̃x�N�g����ς���
		DirectX::SimpleMath::Vector3 frontVector = GetFrontVector();
		frontVector.x = 1.0f;
		SetFrontVector(frontVector);
	}
	//�G��������荶�ɂ����獶������
	else if (GetPos().x > GetEnemyPos().x)
	{
		//�����Ă��������ς���
		SetAngleY(-180.0f + Character2Params::ANGLE_Y);
		//�O�����̃x�N�g����ς���
		DirectX::SimpleMath::Vector3 frontVector = GetFrontVector();
		frontVector.x = -1.0f;
		SetFrontVector(frontVector);

	}

	//��]�s����쐬
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(GetAngleY()));
	//���W���s��ɕϊ�
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.0f, GetPos().z));
	//�T�C�Y���s��ɕϊ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(Character2Params::MODEL_SIZE);
	//���[���h�s��ɉ��Z
	SetWorldMatrix(scale * rotY * trans);

	//�V�[���h�̃T�C�Y�A���W�̍X�V
	DirectX::SimpleMath::Matrix Scale = DirectX::SimpleMath::Matrix::CreateScale(1);
	DirectX::SimpleMath::Matrix pos = DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - Character2Params::SHIELD_POS_Y, GetPos().z));
	SetShieldWorldMatrix(Scale * pos);



	//�����̔��̍��W�̍X�V
	Collision::BoxCollision legCollBox = GetLegCollBox();
	legCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.8f, GetPos().z);
	SetLegCollBox(legCollBox);

	//�̂̔��̍��W�̍X�V
	if (GetCharaState() != eCHARACTER_STATE::SQUAT && GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		Collision::BoxCollision bodyCollBox = GetBodyCollBox();
		bodyCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 0.9f, GetPos().z);
		SetBodyCollBox(bodyCollBox);
	}

	//���̔��̍��W�̍X�V
	if (GetCharaState() != eCHARACTER_STATE::SQUAT)
	{
		Collision::BoxCollision headCollBox = GetHeadCollBox();
		headCollBox.pos = GetPos();
		SetHeadCollBox(headCollBox);
	}

}

