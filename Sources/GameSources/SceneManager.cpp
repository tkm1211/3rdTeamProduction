#include <InputDevice.h>

#include "SceneManager.h"
#include "AssetLoader.h"
#include "FrameWork.h"
#include "Shader.h"
#include "Light.h"


void SceneManager::Init()
{
	// ����������
	SetScene(new SceneTitle());
	ShaderSystem::GetInstance()->Init();
	Light::GetInstance()->Init();
	//Fade�̏���������
	Fade::GetInstance()->Init();
}

void SceneManager::Update()
{
	GetXInputState(&xInput[0], 0);
	GetDInputState(&dInput[0], 0);

#if DEBUG_MODE

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#endif // DEBUG_MODE

#if DEBUG_MODE

	assetLoader.Update();

#endif // DEBUG_MODE

	camera.Update();
	Light::GetInstance()->Update();
	GoToSceneLaboCommand();

	// �X�V����
	if (pStackScene)
	{
		pStackScene->Update();
	}
	if (pNext)
	{
		pScene = pNext;
		pNext = nullptr;
		pScene->Init();
	}
	pScene->Update();

	//Fade�̍X�V����
	Fade::GetInstance()->Update();
}

void SceneManager::Render()
{
	float elapsedTime = FrameWork::GetInstance().GetElapsedTime();

	// �`�揈��
#if DEBUG_MODE

	assetLoader.Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), elapsedTime);

#endif // DEBUG_MODE

	if (pStackScene)
	{
		pStackScene->Render();
	}
	pScene->Render();

	//Fade�̕`�揈��
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

	pScene->ImGui();
	Light::GetInstance()->ImGui();

#endif // DEBUG_MODE
}

// �V�[���̐؂芷��
void SceneManager::SetScene(Scene* scene, bool nowSceneStack)
{
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
	
	//Fade�̉������
	Fade::GetInstance()->UnInit();
	
}