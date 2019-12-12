#pragma once

#include "Hp.h"
#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>
#include "WaveTex.h"

class UiSystem
{
private:
	std::unique_ptr<Hp> hp;
	std::unique_ptr<WaveTex> waveTex;

public:
	Hp* GetHpAddress() { return hp.get(); }
	WaveTex* GetWaveTexAddress() { return waveTex.get(); }
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