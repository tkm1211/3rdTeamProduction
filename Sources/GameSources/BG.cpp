#include "BG.h"
#include "Shader.h"
#include "Editer.h"

void BGModelManager::Init()
{
	ground = std::make_unique<Model>("Data/Assets/Model/BG/Ground_MDL.fbx", true);
	wall = std::make_unique<Model>("Data/Assets/Model/BG/Wall_MDL.fbx", true);
}

void BG::Init()
{
	wallCollision = std::make_unique<CollisionPrimitive>(0, true, DirectX::XMFLOAT3(980, 200, 2000));
	wallCollision->SetColor({ 1, 0, 0, 1 });


	groundData.Init();
	wallData.Init();

	BGEditor::GetInstance()->LoadFile();

	for (size_t i = 0; i < BGEditor::GetInstance()->bgObject.size(); i++)
	{
		BgData t;
		t.type = BGEditor::GetInstance()->bgObject.at(i).GetType();
		t.obj = BGEditor::GetInstance()->bgObject.at(i).GetOBJ3D();

		if (t.type == ModelType::STONE1 || t.type == ModelType::STONE2 || t.type == ModelType::TREE) continue;

		bgObject.push_back(t);

	}

	for (size_t i = 0; i < bgObject.size(); i++)
	{
		LoadModel(bgObject[i].GetType());
	}

}

void BG::UnInit()
{
}

void BG::Update()
{
}

void BG::Draw()
{
	if (Editer::GetInstance()->GetNowEditer())
	{
		SetRasterizerState(FrameWork::GetInstance().RS_CULL_BACK_FALSE);

		BGModelManager::GetInstance()->ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), true);
		BGModelManager::GetInstance()->ground->Render(groundData.GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), groundData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		BGModelManager::GetInstance()->wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), false);
		BGModelManager::GetInstance()->wall->Render(wallData.GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), wallData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

	}
	else
	{
		SetRasterizerState(FrameWork::GetInstance().RS_CULL_BACK_FALSE);

		BGModelManager::GetInstance()->ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), true);
		BGModelManager::GetInstance()->ground->Render(groundData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), groundData.GetColor(), FrameWork::GetInstance().GetElapsedTime());



		BGModelManager::GetInstance()->wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), false);
		BGModelManager::GetInstance()->wall->Render(wallData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), wallData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

	}
	//wallCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

}

void BG::ImGui()
{
}