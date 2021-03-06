///////////////////////////////////
//キャラクター３の攻撃管理クラス
//作成者：GS305_稲垣颯太
//作成日：2020年11月22日
///////////////////////////////////
#include "pch.h"
#include "Character3AttackManager.h"
#include "../../CharacterAttackBase.h"

#include "Character3AttackWeakNeutral.h"
#include "Character3AttackWeakSide.h"
#include "Character3AttackWeakBottom.h"
#include "Character3AttackMiddleNeutral.h"
#include "Character3AttackMiddleSide.h"
#include "Character3AttackMiddleBottom.h"

//コンストラクタ
Character3AttackManager::Character3AttackManager()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		m_pCharacterAttackArray[i] = nullptr;
	}
}

//デストラクタ
Character3AttackManager::~Character3AttackManager()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr) m_pCharacterAttackArray[i].reset();
		m_pCharacterAttackArray[i] = nullptr;
	}
}

///////////////////////////
//初期化
//引数:キャラクターのポインタ、デバイスリソース
//戻り値:なし
//////////////////////////
void Character3AttackManager::Initialize(CharacterBase * pCharacter)
{
	//各攻撃の読み込み
	//弱ニュートラル
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)] = std::make_unique<Character3AttackWeakNeutral>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_NEUTRAL)]->Initialize(pCharacter);
	//弱横
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)] = std::make_unique<Character3AttackWeakSide>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_SIDE)]->Initialize(pCharacter);
	//弱下
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)] = std::make_unique<Character3AttackWeakBottom>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::WEAK_BOTTOM)]->Initialize(pCharacter);
	//中ニュートラル
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)] = std::make_unique<Character3AttackMiddleNeutral>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_NEUTRAL)]->Initialize(pCharacter);
	//中横
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)] = std::make_unique<Character3AttackMiddleSide>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_SIDE)]->Initialize(pCharacter);
	//中下
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)] = std::make_unique<Character3AttackMiddleBottom>();
	m_pCharacterAttackArray[static_cast<int>(eATTACK_TYPE::MIDDLE_BOTTOM)]->Initialize(pCharacter);
}

///////////////////////////
//更新
//引数:なし
//戻り値:なし
//////////////////////////
void Character3AttackManager::Update()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//攻撃の配列の更新
			m_pCharacterAttackArray[i]->Update();
		}
	}
}

///////////////////////////
//描画
//引数:ビュー行列、射影行列
//戻り値:なし
//////////////////////////
void Character3AttackManager::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//攻撃の配列の描画
			m_pCharacterAttackArray[i]->Render(view, proj);
		}
	}
}

///////////////////////////
//終了処理
//引数:なし
//戻り値:なし
//////////////////////////
void Character3AttackManager::Finalize()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//攻撃の配列の終了処理
			m_pCharacterAttackArray[i]->Finalize();
		}

		m_pCharacterAttackArray[i].reset();
		m_pCharacterAttackArray[i] = nullptr;
	}
}

///////////////////////////
//リセット
//引数:なし
//戻り値:なし
//////////////////////////
void Character3AttackManager::Reset()
{
	for (int i = 0; i < static_cast<int>(eATTACK_TYPE::ATTACK_TYPE_NUM); i++)
	{
		if (m_pCharacterAttackArray[i] != nullptr)
		{
			//攻撃の配列のリセット関数
			m_pCharacterAttackArray[i]->Reset();
		}
	}
}
