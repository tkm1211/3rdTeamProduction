#include "CharacterSystem.h"

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
	player->Update();
}

void CharacterSystem::Draw()
{
	player->Draw();
}