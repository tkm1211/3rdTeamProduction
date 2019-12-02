#include "SceneGame.h"


void SceneGame::Init()
{

}

void SceneGame::Update()
{
	EnemyManager::GetInstance()->Update();
}

void SceneGame::Render()
{
	EnemyManager::GetInstance()->Draw();
}

void SceneGame::ImGui()
{

}

void SceneGame::UnInit() {}