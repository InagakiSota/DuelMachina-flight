///////////////////////////////////
//キャラクター１のブースト移動状態のクラス
//作成者：GS305_稲垣
//作成日：2020年10月16日
///////////////////////////////////
#include "pch.h"
#include "Character3BoostMoveState.h"
#include "Keyboard.h"
#include "../../CharacterBase.h"
#include "../../CharacterState.h"
#include "../Character3Params.h"
#include "../../ChracterAnimationNumber.h"

//コンストラクタ
Character3BoostMoveState::Character3BoostMoveState()
{
	m_pCharacter = nullptr;
}

//デストラクタ
Character3BoostMoveState::~Character3BoostMoveState()
{
	m_pCharacter = nullptr;
}

///////////////////////////
//初期化
//引数:キャラクタークラスのポインタ
//戻り値:なし
//////////////////////////
void Character3BoostMoveState::Initialize(CharacterBase * pCharacter)
{
	m_pCharacter = pCharacter;
}

///////////////////////////
//更新
//引数:なし
//戻り値:なし
//////////////////////////
void Character3BoostMoveState::Update()
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	DirectX::SimpleMath::Vector3 vel = m_pCharacter->GetVel();

	//ブースト容量を減らす
	int boostCap = m_pCharacter->GetBoostCap();
	boostCap--;
	m_pCharacter->SetBoostCap(boostCap);

	//ブースト容量が0以下になったら0代入
	if (m_pCharacter->GetBoostCap() <= 0)
	{
		m_pCharacter->SetBoostCap(0);
	}
	//上入力
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Up) && m_pCharacter->GetPos().y < Character3Params::MOVE_LIMIT_TOP)
	{
		vel.y = 1;
		//アニメーションの切り替え
		m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));

	}
	//下入力
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Down) && m_pCharacter->GetPos().y > Character3Params::MOVE_LIMIT_BOTTOM)
	{
		vel.y = -1;
		//アニメーションの切り替え
		m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
	}
	else vel.y = 0.0f;

	//右入力
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Right) && m_pCharacter->GetPos().x <Character3Params::MOVE_LIMIT_X)
	{
		vel.x = 1;
		//アニメーションの切り替え
		if (m_pCharacter->GetFrontVector().x > 0)
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
		}
		else
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
		}

	}
	//左入力
	else if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Left) && m_pCharacter->GetPos().x > -Character3Params::MOVE_LIMIT_X)
	{
		vel.x = -1;
		//アニメーションの切り替え
		if (m_pCharacter->GetFrontVector().x > 0)
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BACK));
		}
		else
		{
			m_pCharacter->ChangeAnimation(static_cast<int>(eCHARACTER_ANIMATION_NUMBER::MOVE_BOOST));
		}

	}
	else vel.x = 0.0f;


	//移動量を正規化
	vel.Normalize();

	m_pCharacter->SetVel(vel * Character3Params::GetInstance()->MOVE_BOOST_FORCE);

	//スペースキーを放すかブースト容量が0になったら元のステートに戻る
	if (keyState.IsKeyUp(DirectX::Keyboard::Keys::Space) || m_pCharacter->GetBoostCap() <= 0)
	{
		m_pCharacter->SetCharaState(eCHARACTER_STATE::WAIT);
	}
}

