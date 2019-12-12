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
	buffAreaSystem->UnInit();
	bg->UnInit();
}

void ObjectSystem::Update()
{
	buffAreaSystem->Update();
	bg->Update();
}

void ObjectSystem::Draw()
{
	buffAreaSystem->Draw();
	bg->Draw();
}