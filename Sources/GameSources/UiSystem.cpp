#include "UiSystem.h"

void UiSystem::Init()
{
	hp = std::make_unique<Hp>();
	hp->Init();
	waveTex = std::make_unique<WaveTex>();
	waveTex->Init();
	damageEffectsTex = std::make_unique<DamageEffects>();
	damageEffectsTex->Init();
	specialAttackGauge = std::make_unique<SpecialAttackGauge>();
	specialAttackGauge->Init();

	attackSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/attacksetu.png", 1);
	attackSprData.texPos = { 0, 0 };		//テクスチャの左上
	attackSprData.size = { 131, 51 };	//テクスチャの幅、高さ

}

void UiSystem::Update()
{
	hp->Update();
	waveTex->Update();
	damageEffectsTex->Update();
	specialAttackGauge->Update();
}

void UiSystem::Draw()
{
	hp->Draw();
	waveTex->Draw();
	damageEffectsTex->Draw();
	specialAttackGauge->Draw();
	attackSpr->Begin();
	attackSpr->Draw({ 1920 - 131*4, 900 }, { 131*2, 51*2 }, attackSprData.texPos, attackSprData.size, 0, { 1, 1, 1, 1 });
	attackSpr->End();
}

void UiSystem::UnInit()
{
	hp->UnInit();
	specialAttackGauge->UnInit();
	damageEffectsTex->UnInit();
}