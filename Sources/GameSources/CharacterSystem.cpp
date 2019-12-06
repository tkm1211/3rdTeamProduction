#include "CharacterSystem.h"
#include "EnemyManager.h"
#include "Editer.h"
#undef max
#undef min

void CharacterSystem::Init()
{
	player = std::make_unique<Player>();
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
		EnemyManager::GetInstance()->Update();
	}
	else
	{
		EnemyManager::GetInstance()->Update();
		Editer::GetInstance()->Update();
	}
}

void CharacterSystem::Draw()
{
	if (!Editer::GetInstance()->GetNowEditer())
	{
		player->Draw();
	}
	EnemyManager::GetInstance()->Draw();
}