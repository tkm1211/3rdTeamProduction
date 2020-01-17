#pragma once
#include "BuffArea.h"
#include "BG.h"

class ObjectSystem
{
private:
	std::unique_ptr<BuffAreaSystem> buffAreaSystem;
	std::unique_ptr<BG>             bg;

public:
	ObjectSystem() {}
	~ObjectSystem() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void ImGui();

	BuffAreaSystem* GetBuffAreaSystemAddress() { return buffAreaSystem.get(); }
	BG* GetBgAddress() { return bg.get(); }

	static ObjectSystem* GetInstance()
	{
		static ObjectSystem instance;
		return &instance;
	}

};