#include "BG.h"
#include "Shader.h"
#include "Editer.h"

void BG::Init()
{
	wallCollision = std::make_unique<CollisionPrimitive>(0, true, DirectX::XMFLOAT3(1100, 200, 2100));
	wallCollision->SetColor({ 1, 0, 0, 1 });

	ground = std::make_unique<Model>("Data/Assets/Model/BG/Ground_MDL.fbx", true);
	wall = std::make_unique<Model>("Data/Assets/Model/BG/Wall_MDL.fbx", true);

	groundData.Init();
	wallData.Init();

	BGEditor::GetInstance()->LoadFile();

	for (size_t i = 0; i < BGEditor::GetInstance()->bgObject.size(); i++)
	{
		BgData t;
		t.type = BGEditor::GetInstance()->bgObject.at(i).GetType();
		t.obj = BGEditor::GetInstance()->bgObject.at(i).GetOBJ3D();

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

		ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), true);
		ground->Render(groundData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), groundData.GetColor(), FrameWork::GetInstance().GetElapsedTime());



		wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), false);
		wall->Render(wallData.GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), wallData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		for (size_t i = 0; i < bgObject.size(); i++)
		{
			bgModel[i]->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), false);
			bgModel[i]->Render(bgObject[i].GetOBJ3D().GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), bgObject[i].GetOBJ3D().GetColor(), FrameWork::GetInstance().GetElapsedTime());
		}
	}
	else
	{
		SetRasterizerState(FrameWork::GetInstance().RS_CULL_BACK_FALSE);

		ground->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), true);
		ground->Render(groundData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), groundData.GetColor(), FrameWork::GetInstance().GetElapsedTime());



		wall->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), false);
		wall->Render(wallData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), wallData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

		for (size_t i = 0; i < bgObject.size(); i++)
		{
			bgModel[i]->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::NORMAL_MAP), false);
			bgModel[i]->Render(bgObject[i].GetOBJ3D().GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), bgObject[i].GetOBJ3D().GetColor(), FrameWork::GetInstance().GetElapsedTime());
		}

	}
	wallCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

}

void BG::ImGui()
{
}