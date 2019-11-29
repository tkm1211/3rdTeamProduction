#include "BG.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Shader.h"


void BG::Init()
{
	ground = std::make_unique<Model>("Data/Assets/Model/val/wall.fbx", false);

	modelData.Init();
}

void BG::UnInit()
{
	ground = nullptr;
}

void BG::Update()
{

}

void BG::Draw()
{
	ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	ground->Render(modelData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
}