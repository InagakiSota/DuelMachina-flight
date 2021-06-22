//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include <SimpleMath.h>
#include <Effects.h>
#include <CommonStates.h>
#include <Model.h>

#include "Src\FrameWork\ModelObject\ModelObject.h"
#include "Src\FrameWork\Sprite2D\Sprite2D.h"
#include "Src\FrameWork\DebugFont\DebugFont.h"

#include "Mouse.h"
#include "Keyboard.h"
#include <GamePad.h>

#include "Src\FrameWork\EffectManager\EffectManager.h"
#include "fbxsdk.h"
#include "stdafx.h"

#include "Src\SceneManager\PlayScene\Character\HitEffectManager.h"


//#include "Fbx.h"

//#include "Src\SceneManager\SceneManager.h"
class SceneManager;

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	//コンストラクタ
	Game();
	//デストラクタ
	~Game();

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// IDeviceNotify
	virtual void OnDeviceLost() override;
	virtual void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize( int& width, int& height ) const;

private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	// Device resources.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	DirectX::SimpleMath::Matrix m_world;		//プレイヤーのワールド行列
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;

	DirectX::SimpleMath::Matrix cupWorld;		//カップのワールド行列

	DirectX::SimpleMath::Matrix m_spaceWorld;	//天球のワールド行列

	std::unique_ptr<DirectX::CommonStates>m_states;
	//std::unique_ptr<DirectX::IEffectFactory>m_fxFactory;
	//std::unique_ptr<DirectX::Model>m_model;

	//3dモデル
	//std::unique_ptr<ModelObject>m_modelObject;//プレイヤー(ロボ)

	//スプライト


	//マウス
	std::unique_ptr<DirectX::Mouse> m_pMouse;
	//キーボード
	std::unique_ptr<DirectX::Keyboard> m_pKeyboard;
	//ゲームパッド
	std::unique_ptr<DirectX::GamePad> m_pGamePad;
	//プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_pos;
	//エフェクトのポインタ
	std::unique_ptr<EffectManager> m_effect;
	//カメラの座標
	DirectX::SimpleMath::Vector3 m_camearPos;

	////fbx
	//std::unique_ptr<Fbx> m_pFbx;

	//シーンマネージャー
	//std::unique_ptr<SceneManager> m_pSceneManager;
	SceneManager* m_pSceneManager;

	std::unique_ptr<Sprite2D> m_pLoadSprite;
	bool m_isLoad;
	DirectX::SimpleMath::Vector2 m_loadSpritePos;

};