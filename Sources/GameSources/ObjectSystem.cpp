#include "ObjectSystem.h"


void ObjectSystem::Init()
{
	buffarea = std::make_unique<BuffArea>();
	buffarea->Init();
}

void ObjectSystem::UnInit()
{
	buffarea->UnInit();
}

void ObjectSystem::Update()
{
	buffarea->Update();
}

void ObjectSystem::Draw()
{
	buffarea->Draw();
}