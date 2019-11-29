#include "SceneLabo.h"
#include "FrameWork.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SkinnedMesh.h"


void SceneLabo::Init()  
{
	//player.Init();
	pBack = std::make_unique<Model>("Data/Assets/Model/danbo_fbx/danbo_atk.fbx", false);
	backData.Init();

	pItem = std::make_unique<Model>("Data/Assets/Model/Life.fbx", false);
	itemData.Init();
	itemData.SetScale({ 10.0f,10.0f,10.0f });
}
void SceneLabo::Update()
{
	if (GetKeyState('N') < 0)
	{
		SceneManager::GetInstance()->SetScene(new SceneTitle());
	}

	//player.Update();
}
void SceneLabo::Render()
{
	//player.Draw();
	pBack->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	pBack->Render(backData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), backData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

	pItem->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	pItem->Render(itemData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), itemData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
}
void SceneLabo::ImGui()
{
	ImGui::Begin("Scene");

	ImGui::End();

	static DirectX::XMFLOAT3 _pos = { 0.0f, 1.0f, 0.0f };
	DirectX::XMFLOAT3 addModelPos = _pos;
	DirectX::XMFLOAT3 modelPos = backData.GetPos();

	ImGui::Begin("Test Model");
	ImGui::DragFloat3("pos", &_pos.x);
	ImGui::DragFloat3("model pos", &modelPos.x);

	if (ImGui::Button("Anim Start"))
	{
		pBack->StartAnimation(0, true);
	}
	if (ImGui::Button("Anim ReStart"))
	{
		pBack->ReStartAnimation();
	}
	if (ImGui::Button("Anim Stop"))
	{
		pBack->PauseAnimation();
	}
	ImGui::End();

	pBack->GetBoneTransform(std::string("pCube1"), addModelPos);
	backData.SetPos(modelPos);

	DirectX::XMMATRIX M = DirectX::XMMatrixTranslation(addModelPos.x, addModelPos.y, addModelPos.z);
	DirectX::XMFLOAT4X4 _M;
	DirectX::XMStoreFloat4x4(&_M, M * backData.GetWorldMatrix());

	itemData.SetPos({ _M._41, _M._42, _M._43 });

	//player.ImGui();
}



void SceneLabo::UnInit() {}