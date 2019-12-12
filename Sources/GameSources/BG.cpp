#include "BG.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Shader.h"
#include "CameraSystem.h"
#include "Editer.h"

void BG::Init()
{
	wall = std::make_unique<Model>("Data/Assets/Model/val/wall.fbx", false);
	ground = std::make_unique<Model>("Data/Assets/Model/val/ground.fbx", false);

	wallCollision = std::make_unique<CollisionPrimitive>(0, true, DirectX::XMFLOAT3(1100, 200, 1800));
	wallCollision->SetColor({ 1, 0, 0, 1 });

	modelData.Init();
}

void BG::UnInit()
{
	wall = nullptr;
	ground = nullptr;
}

void BG::Update()
{
	ImGui();
}

void BG::Draw()
{
	if (Editer::GetInstance()->GetNowEditer())
	{
		ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::PHONE), false);
		ground->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		wall->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		wallCollision->Render(CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());


	}
	else
	{
		ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::PHONE), false);
		ground->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		wall->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		wallCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	}
}

void BG::ImGui()
{
}