#include "UiSystem.h"

void UiSystem::Init()
{
	hp = std::make_unique<Hp>();
	hp->Init();
	waveTex = std::make_unique<WaveTex>();
	waveTex->Init();
	operation = std::make_unique<Operation>();
	operation->Init();
	damageEffectsTex = std::make_unique<DamageEffects>();
	damageEffectsTex->Init();
	specialAttackGauge = std::make_unique<SpecialAttackGauge>();
	specialAttackGauge->Init();

}

void UiSystem::Update()
{
	hp->Update();
	waveTex->Update();
	operation->Update();
	damageEffectsTex->Update();
	specialAttackGauge->Update();
}

void UiSystem::Draw()
{
	hp->Draw();
	waveTex->Draw();
	damageEffectsTex->Draw();
	operation->Draw();
	specialAttackGauge->Draw();
}

void UiSystem::UnInit()
{
	hp->UnInit();
	specialAttackGauge->UnInit();
	damageEffectsTex->UnInit();
}