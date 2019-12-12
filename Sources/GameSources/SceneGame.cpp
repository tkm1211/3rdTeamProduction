#include "SceneGame.h"
#include <FrameWork.h>
#include <string>
#include "Collision.h"
#include "Blender.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "ParticleSystem.h"
#include "CameraSystem.h"
#include "Editer.h"
#include "Shot.h"

void SceneGame::Init()
{
	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();

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
	if (xInput[0].bBt)
	{
		ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos(), 200, 0.1f);
	}


	SceneGame::ImGui();
}

void SceneGame::Render()
{
	CharacterSystem::GetInstance()->Draw();
	ObjectSystem::GetInstance()->Draw();
	if (!Editer::GetInstance()->GetNowEditer())
	{
		ParticleSystem::GetInstance()->Draw();
	}

}

void SceneGame::ImGui()
{
	ImGui::Begin("Game");
	if (ImGui::Button("BuffArea  POP "))
	{
		ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos(), 200, 1);
	}
	if (ImGui::Button("Particle  POP "))
	{
		ParticleSystem::GetInstance()->SetBuffAreaParticle({ 50.0f, 100.0f, 50.0f }, 200);
	}

	ImGui::End();

}

void SceneGame::UnInit() {}