#include <FrameWork.h>
#include <string>

#include "SceneTitle.h"
#include "Collision.h"
#include "Blender.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"


void SceneTitle::Init()
{
	bg = std::make_unique<BG>();
	bg->Init();
	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
}

void SceneTitle::Update()
{
	if (GetKeyState('G') < 0)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}

	bg->Update();
	CharacterSystem::GetInstance()->Update();
	ObjectSystem::GetInstance()->Update();
	camera.SetTarget( DirectX::XMFLOAT3( CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().x, 
		                               CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().y + 60.0f,
		                               CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().z 
		                             ) );

	if (xInput[0].bBt)
	{
		ObjectSystem::GetInstance()->GetBuffAreaAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos(), 200, 1);
	}

}

void SceneTitle::Render()
{
	bg->Draw();
	CharacterSystem::GetInstance()->Draw();
	ObjectSystem::GetInstance()->Draw();
}

void SceneTitle::ImGui()
{
	ImGui::Begin("Title");
	if (ImGui::Button("BuffArea  POP "))
	{
		ObjectSystem::GetInstance()->GetBuffAreaAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos(), 200, 1);
	}
	ImGui::End();
}

void SceneTitle::UnInit() {}