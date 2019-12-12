#include "UiSystem.h"

void UiSystem::Init()
{
	hp = std::make_unique<Hp>();
	hp->Init();
	waveTex = std::make_unique<WaveTex>();
	waveTex->Init();
}

void UiSystem::Update()
{
	hp->Update();
	waveTex->Update();
}

void UiSystem::Draw()
{
	hp->Draw();
	waveTex->Draw();
}

void UiSystem::UnInit()
{
	hp->UnInit();
}