//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <SimpleMath.h>
#include <Model.h>
#include <time.h>


#include <iostream>
#include "Src\SceneManager\SceneManager.h"

#include "Src\FrameWork\FadeManager\FadeManager.h"

#include "Adx2.h"
#include "NewProject_acf.h"

#include "Src/FrameWork/LoadDisplay/LoadDisplay.h"
#include <Thread>
#include "Src\FrameWork\FbxResourceManager\FbxResourceManager.h"
#include "Src/Cgdi.h"


DirectX::SimpleMath::Vector3 v;

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;


Game::Game()
	:
	m_effect(nullptr),
	m_camearPos{},
	m_pos{},
	m_pSceneManager(nullptr)
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
	m_deviceResources->RegisterDeviceNotify(this);
}

Game::~Game()
{
	//リソースの解放
	if (m_effect != nullptr)
	{
		m_effect.reset();
	}
	//if (m_pFbx != nullptr)
	//{
	//	m_pFbx.reset();
	//}


	//シーンの終了処理
	m_pSceneManager->Finalize();
	m_pSceneManager = nullptr;
	SceneManager::ReleaseInstance();
	m_states.reset();

	FadeManager::GetInstance()->Finalize();
	FadeManager::ReleaseInstance();

	FbxResourceManager::GetInstance()->Finalize();
	FbxResourceManager::ReleaseInstance();

	LoadDisplay::GetInstance()->Finalize();
	LoadDisplay::GetInstance()->ReleaseInstance();

	//サウンドの終了処理
	ADX2::GetInstance().Finalize();


	if (m_deviceResources != nullptr)
	{
		m_deviceResources.reset();
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse.reset();
	}

	if(m_pKeyboard != nullptr)
		m_pKeyboard.reset();

	if(m_pGamePad != nullptr)
		m_pGamePad.reset();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	m_deviceResources->SetWindow(window, width, height);

	m_deviceResources->CreateDeviceResources();
	CreateDeviceDependentResources();

	m_deviceResources->CreateWindowSizeDependentResources();
	CreateWindowSizeDependentResources();


	//マウスの作成
	m_pMouse = std::make_unique<Mouse>();
	m_pMouse->SetWindow(window);

	//キーボードの作成
	m_pKeyboard = std::make_unique<Keyboard>();

	//ゲームパッドの作成
	m_pGamePad = std::make_unique<GamePad>();

	//シーンの読み込み
	m_pSceneManager = SceneManager::GetInstance();
	//シーンの初期化
	m_pSceneManager->Initialize();
	//シーンの設定
	m_pSceneManager->SetScene(eSCENE_ID::TITLE_SCENE);

	//フェードマネージャーの読み込み
	FadeManager::GetInstance()->Create(m_deviceResources.get());
	FadeManager::GetInstance()->Initialize(100,DirectX::SimpleMath::Vector3::Zero);

	//ロード画面の読み込み
	LoadDisplay::GetInstance()->Initialize(m_deviceResources.get(), m_states.get());

	//サウンドの初期化
	ADX2::GetInstance().Initialize("Resources/Audio/NewProject.acf", "Resources/Audio/CueSheet_0.acb");

	//Fbxモデル
	FbxResourceManager::GetInstance()->Load(m_deviceResources.get(),window);

	// TODO: Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:
	
	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);

	//乱数の初期化
	srand((unsigned)time(NULL));
	
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
	m_timer.Tick([&]() 
	{
		Game::Update(m_timer);
	});

	Game::Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;

	//シーンの更新
	srand((unsigned)time(NULL));
	
	m_pSceneManager->Update(timer);

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//サウンドの更新
	ADX2::GetInstance().Update();


	//ESC入力で終了
	if (keyState.IsKeyDown(DirectX::Keyboard::Keys::Escape))
	{
		//PostQuitMessage(0);
	}
	
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	m_deviceResources->PIXBeginEvent(L"Render");
	auto context = m_deviceResources->GetD3DDeviceContext();


	// TODO: Add your rendering code here.
	context;

	//シーンの描画
	m_pSceneManager->Render();

	FadeManager::GetInstance()->Render();

	//ロード画面の描画
	//std::thread th_a([]() {LoadDisplay::GetInstance()->Render(); });
	//th_a.join();


	//m_effect->Render();
	m_deviceResources->PIXEndEvent();

	// Show the new frame.
	m_deviceResources->Present();


}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	// Clear the views.
	auto context = m_deviceResources->GetD3DDeviceContext();
	auto renderTarget = m_deviceResources->GetRenderTargetView();
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	// Set the viewport.
	auto viewport = m_deviceResources->GetScreenViewport();
	context->RSSetViewports(1, &viewport);

	m_deviceResources->PIXEndEvent();


}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
	// TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
	// TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
	// TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
	auto r = m_deviceResources->GetOutputSize();
	m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

	// TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 1920;
	height = 1080;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
	auto device = m_deviceResources->GetD3DDevice();

	//// TODO: Initialize device dependent objects here (independent of window size).
	device;

	//auto context = m_deviceResources->GetD3DDeviceContext();

	m_states = std::make_unique<DirectX::CommonStates>(device);

	//ビュー行列を作成する
	m_camearPos = Vector3(0.0f, 0.5f, 4.0f);
	//m_view = Matrix::CreateLookAt(m_camearPos, Vector3::Zero, Vector3::UnitY);

	int w, h;
	GetDefaultSize(w, h);
	gdi->Initialize(m_deviceResources.get(), m_states.get(), w, h);
}


// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
	// TODO: Initialize windows-size dependent objects here.
}


void Game::OnDeviceLost()
{
	// TODO: Add Direct3D resource cleanup here.
	//m_modelObject->Lost();
	DebugFont::GetInstance()->Reset();

	m_effect.reset();

	//シーンの終了処理
	m_pSceneManager->Finalize();
	m_pSceneManager = nullptr;
	SceneManager::ReleaseInstance();
	m_states.reset();

	FadeManager::GetInstance()->Finalize();
	FadeManager::ReleaseInstance();

	FbxResourceManager::GetInstance()->Finalize();
	FbxResourceManager::ReleaseInstance();

	//LoadDisplay::GetInstance()->Finalize();
	//LoadDisplay::GetInstance()->ReleaseInstance();

	//サウンドの終了処理
	ADX2::GetInstance().Finalize();

}

void Game::OnDeviceRestored()
{
	CreateDeviceDependentResources();

	CreateWindowSizeDependentResources();
}
#pragma endregion
