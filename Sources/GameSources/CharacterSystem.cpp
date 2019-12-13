#include "CharacterSystem.h"
#include "Editer.h"
#include "UiSystem.h"
#undef max
#undef min

void CharacterSystem::Init()
{
	player = std::make_unique<Player>();
	enmMgr = std::make_unique<EnemyManager>();
	player->Init();
}

void CharacterSystem::UnInit()
{
	player->UnInit();
}

void CharacterSystem::Update()
{
	if (!Editer::GetInstance()->GetNowEditer())
	{
		player->Update();
		enmMgr->Update();
	}
	else
	{
		enmMgr->Update();
	/*	Editer::GetInstance()->Update();*/
	}
}

void CharacterSystem::Draw()
{
	if (!Editer::GetInstance()->GetNowEditer())
	{
		player->Draw();
	}
	enmMgr->Draw();
}

void CharacterSystem::ImGui()
{
	player->ImGui();
}