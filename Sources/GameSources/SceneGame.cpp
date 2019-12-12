#include "SceneGame.h"
#include <FrameWork.h>
#include <string>
#include "Collision.h"
#include "CollisionJudge.h"
#include "Blender.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "ParticleSystem.h"
#include "Editer.h"
#include "CameraSystem.h"
#include "EnemyManager.h"
#include "SoundLoader.h"
#include "Shot.h"
#include "UiSystem.h"

void SceneGame::Init()
{
	AllSoundStop();
	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();
	UiSystem::GetInstance()->Init();
}

void SceneGame::Update()
{
	CharacterSystem::GetInstance()->Update();
	ObjectSystem::GetInstance()->Update();
	if (!Editer::GetInstance()->GetNowEditer())
	{
		CameraSystem::GetInstance()->mainView.SetTarget(DirectX::XMFLOAT3(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().x,
			CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().y + 60.0f,
			CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().z
		));
		ParticleSystem::GetInstance()->Update();
	}
	else
	{
		CameraSystem::GetInstance()->enemyEditorView.Set(DirectX::XMFLOAT3(0, Editer::GetInstance()->cameraHeight, 0), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -1));
	}

	if (xInput[0].bBt)
	{
		ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos());
	}

	if (Editer::GetInstance()->GetNowEditer())
	{
		Editer::GetInstance()->Update();
	}

	UiSystem::GetInstance()->Update();

	CollisionJudge::AllJudge();

	if (UiSystem::GetInstance()->GetHpAddress()->GetSubHp() >= 610)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}

	if (GetKeyState('A') < 0)
	{
		UiSystem::GetInstance()->GetWaveTexAddress()->Start(10);
	}

#ifdef _DEBUG
	SceneGame::ImGui();
#endif // _DEBUG

}

void SceneGame::Render()
{
	ObjectSystem::GetInstance()->Draw();
	CharacterSystem::GetInstance()->Draw();

	if (!Editer::GetInstance()->GetNowEditer())
	{
		ParticleSystem::GetInstance()->Draw();
	}
	UiSystem::GetInstance()->Draw();

}

void SceneGame::ImGui()
{
	ImGui::Begin("Title");
	if (ImGui::Button("BuffArea  POP "))
	{
		ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos());
		CharacterSystem::GetInstance()->GetPlayerAddress()->SufferDamage(1000);
	}
	if (ImGui::Button("Particle  POP "))
	{
		//ParticleSystem::GetInstance()->SetBuffAreaParticle({50.0f, 100.0f, 50.0f}, 200);
		ParticleSystem::GetInstance()->SetCrystalDestroy({ 0, 100, 0 });
		ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle({ 0, 100, 0 });
		CharacterSystem::GetInstance()->GetPlayerAddress()->SufferDamage(1000);
	}

	if (ImGui::Button("Editer"))
	{
		Editer::GetInstance()->SetNowEditer(Editer::GetInstance()->GetNowEditer() ^ 1);


		if (Editer::GetInstance()->GetNowEditer())
		{
			CameraSystem::GetInstance()->enemyEditorView.Init(DirectX::XMFLOAT3(0, 1000, 0), DirectX::XMFLOAT3(0, 0, 0));
			CameraSystem::GetInstance()->enemyEditorView.Set(DirectX::XMFLOAT3(0, 1000, 0), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));

			CameraSystem::GetInstance()->enemyEditorView.SetPerspectiveMatrix(DirectX::XMConvertToRadians(30.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1000000.0f);
			/*CameraSystem::GetInstance()->enemyEditorView.SetOrthographicMatrix(1920,1080, 0.1f, 1000000.0f);*/
		}
	}
	ImGui::DragInt("CameraHeight", &Editer::GetInstance()->cameraHeight);

	CharacterSystem::GetInstance()->ImGui();
	ObjectSystem::GetInstance()->ImGui();

	ImGui::End();
}

void SceneGame::UnInit() 
{
	CharacterSystem::GetInstance()->UnInit();
	ObjectSystem::GetInstance()->UnInit();
	UiSystem::GetInstance()->UnInit();
}