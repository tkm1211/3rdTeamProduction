#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>
#include "WaveTex.h"
#include "Hp.h"
#include "DamageEffects.h"
#include "SpecialAttackGauge.h"
#include "Operation.h"

class UiSystem
{
private:
	std::unique_ptr<Hp> hp;
	std::unique_ptr<WaveTex> waveTex;
	std::unique_ptr<DamageEffects> damageEffectsTex;
	std::unique_ptr<SpecialAttackGauge> specialAttackGauge;
	std::unique_ptr<Operation> operation;


public:
	Hp* GetHpAddress() { return hp.get(); }
	WaveTex* GetWaveTexAddress() { return waveTex.get(); }
	SpecialAttackGauge* GetSpecialAttackGauge() { return specialAttackGauge.get(); }
	DamageEffects* GetDamageEffectsTexAddress() { return damageEffectsTex.get(); }
public:

	UiSystem() {}
	~UiSystem() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	static UiSystem* GetInstance()
	{
		static UiSystem instance;
		return &instance;
	}
};