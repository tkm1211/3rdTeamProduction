#include <InputDevice.h>

#include "SceneManager.h"
#include "AssetLoader.h"
#include "FrameWork.h"
#include "Shader.h"
#include "Light.h"
#include "CameraSystem.h"
#include "CameraControl.h"
#include "Editer.h"
#include "SoundLoader.h"
#include "BGEditor.h"
#include "ParticleSystem.h"


void SceneManager::Init()
{
	// 初期化処理
	SetScene(new SceneTitle());
	ShaderSystem::GetInstance()->Init();
	Light::GetInstance()->Init();
	//Fadeの初期化処理
	Fade::GetInstance()->Init();
	CameraSystem::GetInstance()->Init();
	//Soundのロード
	SoundLoader::GetInstance()->load();
	commandOn = false;
}

void SceneManager::Update()
{
	GetXInputState(&xInput[0], 0);
	GetDInputState(&dInput[0], 0);

#if DEBUG_MODE

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

#endif // DEBUG_MODE

#if DEBUG_MODE

	//assetLoader.Update();

#endif // DEBUG_MODE

	Light::GetInstance()->Update();

	CommandCheck();
	GoToSceneLaboCommand();

	if (!Editer::GetInstance()->GetNowEditer() && !BGEditor::GetInstance()->GetOn())
	{
		CameraControl::MouseControlUpdate(&CameraSystem::GetInstance()->mainView);
	}
	else if (BGEditor::GetInstance()->GetOn())
	{
		CameraControl::MouseControlUpdate(&CameraSystem::GetInstance()->bgEditorView);
	}
	else
	{
		CameraControl::MouseControlUpdate(&CameraSystem::GetInstance()->enemyEditorView);
	}

	// 更新処理
	if (pStackScene)
	{
		//pStackScene->Update();
	}
	if (pNext)
	{
		pScene = pNext;
		pNext = nullptr;
		pScene->Init();
	}
	pScene->Update();
	//Soundの更新処理
	SoundLoader::GetInstance()->Update();
	//Fadeの更新処理
	Fade::GetInstance()->Update();
}

void SceneManager::Render()
{
	float elapsedTime = FrameWork::GetInstance().GetElapsedTime();

	// 描画処理
#if DEBUG_MODE

	//assetLoader.Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), elapsedTime);

#endif // DEBUG_MODE

	if (pStackScene)
	{
		pStackScene->Render();
	}
	pScene->Render();

	//Fadeの描画処理
	Fade::GetInstance()->Draw();
	
// IMGUI *************************************************************************
#if DEBUG_MODE

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

#endif // DEBUG_MODE
// *******************************************************************************
}

void SceneManager::ImGui()
{
#if DEBUG_MODE
	if (Fade::GetInstance()->loading) return;

	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (GetKeyState(VK_SHIFT) < 0)
		{
			if (GetKeyState('F') < 0)
			{
				commandOn = false;
			}
		}
		else if (GetKeyState('F') < 0)
		{
			commandOn = true;
		}
	}
	if (commandOn)
	{
		ImGui::Begin("Command");
		char _com[256] = "";
		ImGui::InputText(u8"入力してください", _com, sizeof(_com));
		com = std::string(_com);
		ImGui::End();
	}
	if (commandFlg & useImGui)
	{
	}

	pScene->ImGui();
	Light::GetInstance()->ImGui();

	static DirectX::XMFLOAT3 pos = { 0,0,0 };
	ImGui::Begin("Particle");
	ImGui::DragFloat3("pos", &pos.x, 1.0f);
	//if (ImGui::Button("emit"))
	{
	}
	ImGui::End();

	ImGui::Begin("Scene ");
	if (ImGui::Button("Pause"))
	{
		SetScene(new ScenePause(), true);
	}
	ImGui::End();

#endif
}

// シーンの切り換え
void SceneManager::SetScene(Scene* scene, bool nowSceneStack)
{
	if (pStackScene)
	{
		pStackScene = nullptr;
	}
	if (nowSceneStack)
	{
		pStackScene = pScene;
	}
	pNext = scene;
}

void SceneManager::ReSetStackScene()
{
	pScene = pStackScene;
	pStackScene = nullptr;
}

void SceneManager::UnInit()
{
	pScene->UnInit();
	if (pScene)
	{
		//		delete nowScene;
	}
	if (pNext)
	{
		delete pNext;
	}
	if (pStackScene)
	{
		delete pStackScene;
	}

	pScene = nullptr;
	pNext = nullptr;
	pStackScene = nullptr;
	
	//Soundの解放処理
	SoundLoader::GetInstance()->Release();
	//Fadeの解放処理
	Fade::GetInstance()->UnInit();
	
}