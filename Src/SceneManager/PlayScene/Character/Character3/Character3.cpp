///////////////////////////////////
//�L�����N�^�[3�̃N���X
//�쐬�ҁFGS305_��_�D��
//�쐬���F2020�N7��13��
///////////////////////////////////
#include "pch.h"
#include "Character3.h"
#include "GamePad.h"
#include "../../../PlayerID.h"
#include "../../AttackManager/AttackManager.h"
#include "Src\FrameWork\FbxModel\FbxModel.h"
#include "../CharacterState.h"
#include "State/Character3StateManager.h"
#include "Attack\/Character3AttackManager.h"
#include "../ChracterAnimationNumber.h"

#include "Adx2.h"
#include "CueSheet_0.h"
#include "../../../../FrameWork/FbxResourceManager/FbxResourceManager.h"
#include "../CharacterID.h"
#include "Src/Cgdi.h"


//�R���X�g���N�^
Character3::Character3(ePLAYER_ID playerID)
	:	//���N���X�̃R���X�g���N�^
	CharacterBase::CharacterBase(playerID)
{
	//���g�̃L�����N�^�[��ID��ݒ�
	SetCharacterID(eCHARACTER_ID::CHARACTER_3);
}

//�f�X�g���N�^
Character3::~Character3()
{	
	//���N���X�̃f�X�g���N�^
	CharacterBase::~CharacterBase();
}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Initialize()
{	
	//���N���X�̏�����
	CharacterBase::Initialize();

	//3D���f���̓ǂݍ���
	SetFbxModel(FbxResourceManager::GetInstance()->GetModel(eCHARACTER_ID::CHARACTER_3));

	//�L�����N�^�[�̃X�e�[�^�X�f�[�^�̓ǂݍ���
	Character3Params::GetInstance()->LoadStatusData();

	//�����̓����蔻��̔��̐ݒ�
	Collision::BoxCollision legCollBox = GetLegCollBox();
	legCollBox.size_h = Character3Params::LEG_COLL_SIZE;
	legCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.4f, GetPos().z);
	SetLegCollBox(legCollBox);

	//�̂̓����蔻��̔��̓ǂݍ���
	Collision::BoxCollision bodyCollBox = GetBodyCollBox();
	bodyCollBox.size_h = Character3Params::BODY_COLL_SIZE_NORMAL;
	bodyCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.3f, GetPos().z);
	SetBodyCollBox(bodyCollBox);

	//���̓����蔻��̔��̓ǂݍ���
	Collision::BoxCollision headCollBox = GetBodyCollBox();
	headCollBox.size_h = Character3Params::HEAD_COLL_SIZE;
	headCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y + 0.3f, GetPos().z);
	SetHeadCollBox(headCollBox);

	//�O�����̐ݒ�
	SetFrontVector(Character3Params::FRONT_VECTOR);


	//�̗͂̐ݒ�
	SetHP(Character3Params::GetInstance()->MAX_HP);
	//�̗͂̍ő�l�̐ݒ�
	SetHPMax(Character3Params::GetInstance()->MAX_HP);
	//�u�[�X�g�e�ʂ̏�����
	SetBoostCap(Character3Params::GetInstance()->BOOST_CAP_MAX);
	//�u�[�X�g�e�ʂ̍ő�l�̐ݒ�
	SetMaxBoostCap(Character3Params::GetInstance()->BOOST_CAP_MAX);
	//�̗͂̃o�b�t�@�̐ݒ�
	SetHPBuffer(GetHP());
	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�ݒ�
	SetHitEffectPos(DirectX::SimpleMath::Vector3(
		GetPos().x, GetPos().y + Character3Params::HIT_EFFECT_POS_Y, GetPos().z));
	//Y���̊p�x�ݒ�
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1)SetAngleY(Character3Params::ANGLE_Y);
	if (GetPlayerID() == ePLAYER_ID::PLAYER_2)SetAngleY(-180.0f+Character3Params::ANGLE_Y);

	//���W���s��ɕϊ�
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPos());
	//�T�C�Y���s��ɕϊ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(
		Character3Params::BODY_SIZE, Character3Params::BODY_SIZE, Character3Params::BODY_SIZE);
	//Y���̊p�x���s��ɕϊ�
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(GetAngleY());
	//���[���h�s��ɉ��Z
	SetWorldMatrix(scale * rotY* trans);


}

///////////////////////////
//�X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Update(DX::StepTimer const& timer)
{
	//�ړ�����
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1 && GetCharaState() != eCHARACTER_STATE::DAMAGE)Move();
	
	//���N���X�̍X�V
	CharacterBase::Update(timer);

	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�ݒ�
	SetHitEffectPos(DirectX::SimpleMath::Vector3(
		GetPos().x, GetPos().y + Character3Params::HIT_EFFECT_POS_Y, GetPos().z));

	//�u�[�X�g�ړ��łȂ���΃u�[�X�g�e�ʂ𑝂₷
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		SetBoostCap(GetBoostCap() + 1);
		//�ő�l�ȏ�ɂȂ�����ő�l����
		if (GetBoostCap() >= Character3Params::GetInstance()->BOOST_CAP_MAX)
		{
			SetBoostCap(Character3Params::GetInstance()->BOOST_CAP_MAX);
		}
	}

	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	//�v���C���[���E����
	if (GetFrontVector().x > 0)
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x - Character3Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character3Params::BOOST_EFFECT_POS_Y,
				0.0f), Character3Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	//�v���C���[��������
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character3Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character3Params::BOOST_EFFECT_POS_Y,
				0.0f), Character3Params::BOOST_EFFECT_ANGLE_RIGHT);

	}

	//�����蔻��̍X�V
	Character3::CollisionUpdate();


}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{	
	//���N���X�̕`��
	CharacterBase::Render(view, proj);

}

///////////////////////////
//�I��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Finalize()
{
	//���N���X�̏I������
	CharacterBase::Finalize();
}

///////////////////////////
//���Ƃ̓����蔻��
//����:���̓����蔻��\����
//�߂�l:�Ȃ�
//////////////////////////
void Character3::HitFloor(const Collision::BoxCollision& floorColl)
{
	CharacterBase::HitFloor(floorColl);
}


///////////////////////////
//�G�̑̂Ƃ̓����蔻��
//����:�G�̑̂̓����蔻��
//�߂�l:�Ȃ�
//////////////////////////
void Character3::HitEnemyBody(const Collision::BoxCollision & enemyBodyColl, const Collision::BoxCollision& enemyHeadColl)
{
	//�G�̑̂Ƃ̓����蔻��
	CharacterBase::HitEnemyBody(enemyBodyColl, enemyHeadColl);
}


///////////////////////////
//�U���Ƃ̓����蔻��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::HitAttack()
{
	//�U���Ƃ̓����蔻��
	CharacterBase::HitAttack();
}

///////////////////////////
//����
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Ready(DX::StepTimer const& timer)
{	
	//�ړ�����
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1 && GetCharaState() != eCHARACTER_STATE::DAMAGE)Move();
	//���N���X�̏����֐�
	CharacterBase::Ready(timer);

	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	if (GetFrontVector().x > 0)
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x - Character3Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character3Params::BOOST_EFFECT_POS_Y,
				0.0f), Character3Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character3Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character3Params::BOOST_EFFECT_POS_Y,
				0.0f), Character3Params::BOOST_EFFECT_ANGLE_RIGHT);

	}


	//�u�[�X�g�ړ��łȂ���΃u�[�X�g�e�ʂ𑝂₷
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		SetBoostCap(GetBoostCap() + 1);
		//�ő�l�ȏ�ɂȂ�����ő�l����
		if (GetBoostCap() >= Character3Params::GetInstance()->BOOST_CAP_MAX)
		{
			SetBoostCap(Character3Params::GetInstance()->BOOST_CAP_MAX);
		}
	}


	//�����蔻��̍X�V
	Character3::CollisionUpdate();

}

///////////////////////////
//�s�k
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Lose(DX::StepTimer const & timer)
{
	//���N���X�̔s�k�֐�
	CharacterBase::Lose(timer);


	//�����蔻��̍X�V
	Character3::CollisionUpdate();


}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Reset()
{
	//���N���X�̃��Z�b�g�֐�
	CharacterBase::Reset();
	//�u�[�X�g�e�ʂ�)
	SetBoostCap(Character3Params::GetInstance()->BOOST_CAP_MAX);
}

///////////////////////////
//�A�j���[�V�����̐؂�ւ�
//����:�؂�ւ���A�j���[�V�����̔ԍ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::ChangeAnimation(const int & animationStack)
{
	CharacterBase::ChangeAnimation(animationStack);
}

///////////////////////////
//�A�j���[�V�����̐؂�ւ�
//����:�؂�ւ���A�j���[�V�����̔ԍ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Move()
{
	//�L�[�̏�Ԏ擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Vector3 vel = GetVel();

	//�K�[�h��Ԃ������ԂłȂ���Έړ�
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE &&
		GetCharaState() != eCHARACTER_STATE::DAMAGE &&
		GetCharaState() != eCHARACTER_STATE::GUARD)
	{
		//����͂��ړ��������ɂ�����ړ�
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) && GetPos().y < Character3Params::MOVE_LIMIT_TOP)
		{
			vel.y = 1;

			//�A�j���[�V�����̐؂�ւ�
			ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::JUMP));


		}
		//�����͂��ړ��������ɂ�����ړ�
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) && GetPos().y > Character3Params::MOVE_LIMIT_BOTTOM)
		{
			vel.y = -1;
			//�A�j���[�V�����̐؂�ւ�
			ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::JUMP));


		}
		else vel.y = 0.0f;

		//�E���͂��ړ��������ɂ�����ړ�
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) &&
			(GetPos().x <= Character3Params::MOVE_LIMIT_X))
		{
			vel.x = 1;

			//�A�j���[�V�����̐؂�ւ�
			if (GetFrontVector().x > 0)
			{
				ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_FRONT));
			}
			else
			{
				ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
			}

		}
		//�����͂��ړ��������ɂ�����ړ�
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) &&
			(GetPos().x >= -Character3Params::MOVE_LIMIT_X))
		{
			vel.x = -1;

			//�A�j���[�V�����̐؂�ւ�
			if (GetFrontVector().x > 0)
			{
				ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
			}
			else
			{
				ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_FRONT));
			}

		}
		else vel.x = 0.0f;


		vel.Normalize();

		SetVel(vel * Character3Params::GetInstance()->MOVE_FRONT_FORCE);
	}

}

void Character3::MoveAI()
{
}

///////////////////////////
//�U��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::Attack()
{
	//���N���X�̍U���Ǘ��֐�
	CharacterBase::Attack();

}

///////////////////////////
//�X�e�[�g�̊Ǘ�
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::StateManager()
{
	//���N���X�̃X�e�[�g�Ǘ��֐�
	CharacterBase::StateManager();
}

///////////////////////////
//CPU����
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::AI(DX::StepTimer const& timer)
{
	//���N���X��AI�֐�
	CharacterBase::AI(timer);
}

///////////////////////////
//�����蔻��̍X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character3::CollisionUpdate()
{
	//�v���C���[��Y���̊p�x
	if (GetPos().x < GetEnemyPos().x )
	{
		//�����Ă��������ς���
		SetAngleY(Character3Params::ANGLE_Y);
		//�O�����̃x�N�g����ς���
		DirectX::SimpleMath::Vector3 frontVector = GetFrontVector();
		frontVector.x = 1.0f;
		SetFrontVector(frontVector);
	}
	if (GetPos().x > GetEnemyPos().x )
	{
		//�����Ă��������ς���
		SetAngleY(-180.0f + Character3Params::ANGLE_Y);
		//�O�����̃x�N�g����ς���
		DirectX::SimpleMath::Vector3 frontVector = GetFrontVector();
		frontVector.x = -1.0f;
		SetFrontVector(frontVector);

	}
	//��]�s����쐬
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(GetAngleY()));


	//���W���s��ɕϊ�
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.0f, GetPos().z));
	//�T�C�Y���s��ɕϊ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(
		Character3Params::BODY_SIZE, Character3Params::BODY_SIZE, Character3Params::BODY_SIZE);
	//���[���h�s��ɉ��Z
	SetWorldMatrix(scale * rotY * trans);

	//�V�[���h�̃T�C�Y�A���W�̍X�V
	DirectX::SimpleMath::Matrix Scale = DirectX::SimpleMath::Matrix::CreateScale(1);
	DirectX::SimpleMath::Matrix pos = DirectX::SimpleMath::Matrix::CreateTranslation(
		DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - Character3Params::SHIELD_POS_Y, GetPos().z));
	SetShieldWorldMatrix(Scale * pos);


	//�����̔��̍��W�̍X�V
	Collision::BoxCollision legCollBox = GetLegCollBox();
	legCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 2.2f, GetPos().z);
	SetLegCollBox(legCollBox);

	if (GetCharaState() != eCHARACTER_STATE::SQUAT)
	{
		//�̂̔��̍��W�̍X�V
		Collision::BoxCollision bodyCollBox = GetBodyCollBox();
		bodyCollBox.size_h = Character3Params::BODY_COLL_SIZE_NORMAL;
		bodyCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.4f, GetPos().z);
		SetBodyCollBox(bodyCollBox);

		//���̔��̍��W�̍X�V
		Collision::BoxCollision headCollBox = GetHeadCollBox();
		headCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 0.5f, GetPos().z);
		SetHeadCollBox(headCollBox);
	}

}
