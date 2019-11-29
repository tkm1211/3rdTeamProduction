#include <FrameWork.h>
#include <string>

#include "SceneTitle.h"
#include "Collision.h"
#include "Blender.h"
#include "Particle.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"

void SceneTitle::Init()
{
	bg = std::make_unique<BG>();
	bg->Init();
	CharacterSystem::GetInstance()->Init();
}

void SceneTitle::Update()
{
	bg->Update();
	CharacterSystem::GetInstance()->Update();
	camera.target = DirectX::XMFLOAT3( CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().x, 
		                               CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().y + 60.0f,
		                               CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().z 
		                             );
}

void SceneTitle::Render()
{
	bg->Draw();
	CharacterSystem::GetInstance()->Draw();
}

void SceneTitle::ImGui()
{
	
}

void SceneTitle::UnInit() {}