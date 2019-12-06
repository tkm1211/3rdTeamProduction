#include "BG.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Shader.h"
#include "CameraSystem.h"


void BG::Init()
{
	wall = std::make_unique<Model>("Data/Assets/Model/val/wall.fbx", false);
	ground = std::make_unique<Model>("Data/Assets/Model/val/ground.fbx", false);

	modelData.Init();
}

void BG::UnInit()
{
	wall = nullptr;
	ground = nullptr;
}

void BG::Update()
{

}

void BG::Draw()
{
	ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::PHONE), false);
	ground->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	wall->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
}