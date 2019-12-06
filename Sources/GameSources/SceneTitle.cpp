#include <FrameWork.h>
#include <string>

#include "SceneTitle.h"
#include "Collision.h"
#include "Blender.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "ParticleSystem.h"
#include "Editer.h"
#include "CameraSystem.h"


void SceneTitle::Init()
{
	bg = std::make_unique<BG>();
	bg->Init();
	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();

}

void SceneTitle::Update()
{
	if (GetKeyState('G') < 0)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
		//SetScene(new SceneLabo(), false);
	}

	bg->Update();
	CharacterSystem::GetInstance()->Update();
	ObjectSystem::GetInstance()->Update();
	ParticleSystem::GetInstance()->Update();

	if (!Editer::GetInstance()->GetNowEditer())
	{
		CameraSystem::GetInstance()->mainView.SetTarget(DirectX::XMFLOAT3(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().x,
			CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().y + 60.0f,
			CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().z
		));
	}
	if (xInput[0].bBt)
	{
		ObjectSystem::GetInstance()->GetBuffAreaAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos(), 200, 0.1f);
	}

	if (Editer::GetInstance()->GetNowEditer())
	{
		Editer::GetInstance()->Update();
	}

}

void SceneTitle::Render()
{
	bg->Draw();
	CharacterSystem::GetInstance()->Draw();
	ObjectSystem::GetInstance()->Draw();
	ParticleSystem::GetInstance()->Draw();

}

void SceneTitle::ImGui()
{
	ImGui::Begin("Title");
	if (ImGui::Button("BuffArea  POP "))
	{
		ObjectSystem::GetInstance()->GetBuffAreaAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos(), 200, 1);
	}
	if (ImGui::Button("Particle  POP "))
	{
		ParticleSystem::GetInstance()->SetBuffAreaParticle({50.0f, 100.0f, 50.0f}, 200);
	}

	if (ImGui::Button("Editer"))
	{
		Editer::GetInstance()->SetNowEditer(true);

		CameraSystem::GetInstance()->mainView.Set(DirectX::XMFLOAT3(0, 500, 0), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));

	}

	ImGui::End();
}

void SceneTitle::UnInit() {}