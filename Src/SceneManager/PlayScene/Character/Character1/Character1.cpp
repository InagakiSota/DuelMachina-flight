///////////////////////////////////
//�L�����N�^�[�P�̃N���X
//�쐬�ҁFGS3_05_��_�D��
//�쐬���F2020�N7��13��
///////////////////////////////////
#include "pch.h"

#include "Character1.h"
#include "GamePad.h"
#include "../../../PlayerID.h"
#include "../../AttackManager/AttackManager.h"
#include "Src\FrameWork\FbxModel\FbxModel.h"
#include "../CharacterState.h"

#include "State\Character1StateManager.h"
#include "Attack\Character1AttackManager.h"
#include "../ChracterAnimationNumber.h"

#include "Adx2.h"

#include "CueSheet_0.h"
#include "../../../../FrameWork/FbxResourceManager/FbxResourceManager.h"
#include "../CharacterID.h"
#include "Src/Cgdi.h"


//�R���X�g���N�^
Character1::Character1(ePLAYER_ID playerID)
	:	
	//���N���X�̃R���X�g���N�^
	CharacterBase::CharacterBase(playerID)
{
	//���g�̃L�����N�^�[��ID��ݒ�
	SetCharacterID(eCHARACTER_ID::CHARACTER_1);
}

//�f�X�g���N�^
Character1::~Character1()
{
	//���N���X�̃f�X�g���N�^
	CharacterBase::~CharacterBase();

}

///////////////////////////
//������
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Initialize()
{
	//���N���X�̏�����
	CharacterBase::Initialize();

	//3D���f���̓ǂݍ���
	SetFbxModel(FbxResourceManager::GetInstance()->GetModel(eCHARACTER_ID::CHARACTER_1));	

	//�L�����N�^�[�̃X�e�[�^�X�f�[�^�̓ǂݍ���
	Character1Params::GetInstance()->LoadStatusData();


	//�����̓����蔻��̔��̐ݒ�
	Collision::BoxCollision legCollBox = GetLegCollBox();
	legCollBox.size_h = Character1Params::LEG_COLL_SIZE;
	legCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 1.0f, GetPos().z);
	SetLegCollBox(legCollBox);

	//�̂̓����蔻��̔��̓ǂݍ���
	Collision::BoxCollision bodyCollBox = GetBodyCollBox();
	bodyCollBox.size_h = Character1Params::BODY_COLL_SIZE_NORMAL;
	bodyCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 0.2f, GetPos().z);
	SetBodyCollBox(bodyCollBox);

	//���̓����蔻��̔��̓ǂݍ���
	Collision::BoxCollision headCollBox = GetBodyCollBox();
	headCollBox.size_h = Character1Params::HEAD_COLL_SIZE;
	headCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y + 0.7f, GetPos().z);
	SetHeadCollBox(headCollBox);

	//�O�����̐ݒ�
	SetFrontVector(Character1Params::FRONT_VECTOR);

	//�̗͂̐ݒ�
	SetHP(Character1Params::GetInstance()->MAX_HP);
	//�̗͂̍ő�l�̐ݒ�
	SetHPMax(Character1Params::GetInstance()->MAX_HP);
	//�u�[�X�g�e�ʂ̏�����
	SetBoostCap(Character1Params::GetInstance()->BOOST_CAP_MAX);
	//�u�[�X�g�e�ʂ̍ő�l�̐ݒ�
	SetMaxBoostCap(Character1Params::GetInstance()->BOOST_CAP_MAX);
	//�̗͂̃o�b�t�@�̐ݒ�
	SetHPBuffer(GetHP());

	//Y���̊p�x�ݒ�
	if (GetPlayerID() == ePLAYER_ID::PLAYER_1)SetAngleY(Character1Params::ANGLE_Y);
	if (GetPlayerID() == ePLAYER_ID::PLAYER_2)SetAngleY(-Character1Params::ANGLE_Y);

	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�ݒ�
	SetHitEffectPos(DirectX::SimpleMath::Vector3(
		GetPos().x, GetPos().y, GetPos().z));


	//���W���s��ɕϊ�
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPos());
	//�T�C�Y���s��ɕϊ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(
		Character1Params::BODY_SIZE, Character1Params::BODY_SIZE, Character1Params::BODY_SIZE);
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
void Character1::Update(DX::StepTimer const& timer)
{
	//�ړ�����
	if(GetPlayerID() == ePLAYER_ID::PLAYER_1 && GetCharaState() != eCHARACTER_STATE::DAMAGE)Move();

	//���N���X�̍X�V
	CharacterBase::Update(timer);
	//�q�b�g�G�t�F�N�g�̔����ʒu�̍��W�ݒ�
	SetHitEffectPos(DirectX::SimpleMath::Vector3(
		GetPos().x, GetPos().y, GetPos().z));

	//�u�[�X�g�ړ��łȂ���΃u�[�X�g�e�ʂ𑝂₷
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		SetBoostCap(GetBoostCap() + 1);
		//�ő�l�ȏ�ɂȂ�����ő�l����
		if (GetBoostCap() >= Character1Params::GetInstance()->BOOST_CAP_MAX)
		{
			SetBoostCap(Character1Params::GetInstance()->BOOST_CAP_MAX);
		}
	}
	//�u�[�X�g�G�t�F�N�g�}�l�[�W���[�̍X�V
	//�L�����N�^�[���E�����̏ꍇ
	if (GetFrontVector().x > 0)
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x - Character1Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character1Params::BOOST_EFFECT_POS_Y,
				0.0f), Character1Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	//�L�����N�^�[���������̏ꍇ
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character1Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character1Params::BOOST_EFFECT_POS_Y,
				0.0f), Character1Params::BOOST_EFFECT_ANGLE_RIGHT);

	}

	//�����蔻��̍X�V
	Character1::CollisionUpdate();

}

///////////////////////////
//�`��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{	
	//���N���X�̕`��
	CharacterBase::Render(view, proj);
}

///////////////////////////
//�I��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Finalize()
{
	//���N���X�̏I������
	CharacterBase::Finalize();

}

///////////////////////////
//���Ƃ̓����蔻��
//����:���̓����蔻��\����
//�߂�l:�Ȃ�
//////////////////////////
void Character1::HitFloor(const Collision::BoxCollision& floorColl)
{
	//���Ƃ̓����蔻��
	CharacterBase::HitFloor(floorColl);
}

///////////////////////////
//�G�̑̂Ƃ̓����蔻��
//����:�G�̑̂̓����蔻��
//�߂�l:�Ȃ�
//////////////////////////
void Character1::HitEnemyBody(const Collision::BoxCollision & enemyBodyColl, const Collision::BoxCollision& enemyHeadColl)
{
	//�G�̑̂Ƃ̓����蔻��
	CharacterBase::HitEnemyBody(enemyBodyColl, enemyHeadColl);
}

///////////////////////////
//�U���Ƃ̓����蔻��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::HitAttack()
{
	//�U���Ƃ̓����蔻��
	CharacterBase::HitAttack();
}


///////////////////////////
//����
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Ready(DX::StepTimer const& timer)
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
				GetPos().x - Character1Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character1Params::BOOST_EFFECT_POS_Y,
				0.0f),Character1Params::BOOST_EFFECT_ANGLE_LEFT);
	}
	else
	{
		GetBoostEffectManager()->Update(timer,
			DirectX::SimpleMath::Vector3(
				GetPos().x + Character1Params::BOOST_EFFECT_POS_X,
				GetPos().y + Character1Params::BOOST_EFFECT_POS_Y,
				0.0f), Character1Params::BOOST_EFFECT_ANGLE_RIGHT);

	}

	//�u�[�X�g�ړ��łȂ���΃u�[�X�g�e�ʂ𑝂₷
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		SetBoostCap(GetBoostCap() + 1);
		//�ő�l�ȏ�ɂȂ�����ő�l����
		if (GetBoostCap() >= Character1Params::GetInstance()->BOOST_CAP_MAX)
		{
			SetBoostCap(Character1Params::GetInstance()->BOOST_CAP_MAX);
		}
	}

	//�����蔻��̍X�V
	Character1::CollisionUpdate();
}

///////////////////////////
//�s�k
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Lose(DX::StepTimer const & timer)
{
	//���N���X�̔s�k�֐�
	CharacterBase::Lose(timer);

}

///////////////////////////
//���Z�b�g
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Reset()
{
	//���N���X�̃��Z�b�g�֐�
	CharacterBase::Reset();
	//�u�[�X�g�e�ʂ�)
	SetBoostCap(Character1Params::GetInstance()->BOOST_CAP_MAX);

}

///////////////////////////
//�A�j���[�V�����̐؂�ւ�
//����:�؂�ւ���A�j���[�V�����̔ԍ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::ChangeAnimation(const int & animationStack)
{
	CharacterBase::ChangeAnimation(animationStack);
}

///////////////////////////
//AI
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::AI(DX::StepTimer const& timer)
{		
	CharacterBase::AI(timer);
	//���N���X��AI�֐�
	if (GetPlayerID() == ePLAYER_ID::PLAYER_2 && GetCharaState() == eCHARACTER_STATE::MOVE_AI)
	{
		Character1::MoveAI();
	}
	//�X�V
	//Character1::Update(timer);

}



///////////////////////////
//�ړ�
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Move()
{
	//�L�[�̏�Ԏ擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	//�v���C���[�̈ړ��ʎ擾
	DirectX::SimpleMath::Vector3 vel = GetVel();

	//�K�[�h��Ԃ������ԂłȂ���Έړ�
	if (GetCharaState() != eCHARACTER_STATE::BOOST_MOVE &&
		GetCharaState() != eCHARACTER_STATE::DAMAGE &&
		GetCharaState() != eCHARACTER_STATE::GUARD)
	{
		//����͂��ړ��������ɂ�����ړ�
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) && GetPos().y < Character1Params::MOVE_LIMIT_TOP)
		{
			vel.y = 1;

			//�A�j���[�V�����̐؂�ւ�
			ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::JUMP));

		}
		//�����͂��ړ��������ɂ�����ړ�
		else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) && GetPos().y > Character1Params::MOVE_LIMIT_BOTTOM)
		{
			vel.y = -1;
			//�A�j���[�V�����̐؂�ւ�
			ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::JUMP));

		}
		else vel.y = 0.0f;

		//�E���͂��ړ��������ɂ�����ړ�
		if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) &&
			(GetPos().x <= Character1Params::MOVE_LIMIT_X))
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
			(GetPos().x >= -Character1Params::MOVE_LIMIT_X))
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

		SetVel(vel * Character1Params::GetInstance()->MOVE_FRONT_FORCE);
	}

}

///////////////////////////
//AI�̈ړ�
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::MoveAI()
{
	//�v���C���[�̈ړ��ʎ擾
	DirectX::SimpleMath::Vector3 vel = GetVel();

	//�ړ������؂�ւ��̃^�C�}�[
	static float moveTimerX = 0.0f;
	static float moveTimerY = 0.0f;

	//�ړ�����
	static CharacterBase::eMOVE_STATE_X moveStateX = CharacterBase::eMOVE_STATE_X::NONE;
	static CharacterBase::eMOVE_STATE_Y moveStateY = CharacterBase::eMOVE_STATE_Y::NONE;

	//X�����̈ړ�
	if (moveTimerX <= 0.0f)
	{
		moveStateX = static_cast<eMOVE_STATE_X>(rand() % 3);
		
		moveTimerX = 60.0f;
	}
	switch (moveStateX)
	{
		//�ړ����Ȃ�
		case CharacterBase::eMOVE_STATE_X::NONE:
		{
			vel.x = 0.0f;
			break;
		}
		//�E�ړ�
		case CharacterBase::eMOVE_STATE_X::RIGHT:
		{
			if (GetPos().x <= Character1Params::MOVE_LIMIT_X)
			{
				//�ړ��ʐݒ�
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
			break;
		}
		//���ړ�
		case CharacterBase::eMOVE_STATE_X::LEFT:
		{
			if (GetPos().x >= -Character1Params::MOVE_LIMIT_X)
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
			break;
		}
		default:
			break;
	}
	//�ړ��ʂ̐��K��
	vel.Normalize();

	//�^�C�}�[�����炷
	moveTimerX -= static_cast<float>(GetStepTimer().GetElapsedSeconds());
	
	//�ړ���
	SetVel(vel * Character1Params::GetInstance()->MOVE_FRONT_FORCE);

}

///////////////////////////
//�U��
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::Attack()
{
	//���N���X�̍U���Ǘ��֐�
	CharacterBase::Attack();
}

///////////////////////////
//�X�e�[�g�̊Ǘ�
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::StateManager()
{
	//���N���X�̃X�e�[�g�Ǘ��֐�
	CharacterBase::StateManager();
}

///////////////////////////
//�����蔻��̍X�V
//����:�Ȃ�
//�߂�l:�Ȃ�
//////////////////////////
void Character1::CollisionUpdate()
{
	//�v���C���[��Y���̊p�x
	if (GetPos().x < GetEnemyPos().x )
	{
		//�����Ă��������ς���
		SetAngleY(Character1Params::ANGLE_Y);
		//�O�����̃x�N�g����ς���
		DirectX::SimpleMath::Vector3 frontVector = GetFrontVector();
		frontVector.x = 1.0f;
		SetFrontVector(frontVector);
	}
	else if (GetPos().x > GetEnemyPos().x)
	{
		//�����Ă��������ς���
		SetAngleY(-Character1Params::ANGLE_Y);
		//�O�����̃x�N�g����ς���
		DirectX::SimpleMath::Vector3 frontVector = GetFrontVector();
		frontVector.x = -1.0f;
		SetFrontVector(frontVector);

	}

	//��]�s����쐬
	DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(GetAngleY()));
	//���W���s��ɕϊ�
	DirectX::SimpleMath::Matrix trans = DirectX::SimpleMath::Matrix::CreateTranslation(GetPos());
	//�T�C�Y���s��ɕϊ�
	DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(
		Character1Params::BODY_SIZE, Character1Params::BODY_SIZE, Character1Params::BODY_SIZE);
	//���[���h�s��ɉ��Z
	SetWorldMatrix(scale * rotY * trans);

	//�V�[���h�̃T�C�Y�A���W�̍X�V
	DirectX::SimpleMath::Matrix Scale = DirectX::SimpleMath::Matrix::CreateScale(1);
	DirectX::SimpleMath::Matrix pos = DirectX::SimpleMath::Matrix::CreateTranslation(GetPos());
	SetShieldWorldMatrix(Scale * pos);

	//�����̔��̍��W�̍X�V
	Collision::BoxCollision legCollBox = GetLegCollBox();
	legCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y - 0.85f, GetPos().z);
	SetLegCollBox(legCollBox);

	if (GetCharaState() != eCHARACTER_STATE::SQUAT && GetCharaState() != eCHARACTER_STATE::BOOST_MOVE)
	{
		//�̂̔��̍��W�̍X�V
		Collision::BoxCollision bodyCollBox = GetBodyCollBox();
		bodyCollBox.size_h = Character1Params::BODY_COLL_SIZE_NORMAL;
		bodyCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y, GetPos().z);
		SetBodyCollBox(bodyCollBox);
		//���̔��̍��W�̍X�V
		Collision::BoxCollision headCollBox = GetHeadCollBox();
		headCollBox.pos = DirectX::SimpleMath::Vector3(GetPos().x, GetPos().y + 0.9f, GetPos().z);
		SetHeadCollBox(headCollBox);
	}
}

