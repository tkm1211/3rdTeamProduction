#include "ObjectSystem.h"


void ObjectSystem::Init()
{
	buffAreaSystem = std::make_unique<BuffAreaSystem>();
	buffAreaSystem->Init();
	bg = std::make_unique<BG>();
	bg->Init();

}

void ObjectSystem::UnInit()
{
	bg->UnInit();
	buffAreaSystem->UnInit();
}

void ObjectSystem::Update()
{
	bg->Update();
	buffAreaSystem->Update();
}

void ObjectSystem::Draw()
{
	bg->Draw();
	buffAreaSystem->Draw();
}

void ObjectSystem::ImGui()
{
	bg->ImGui();
	buffAreaSystem->ImGui();
}