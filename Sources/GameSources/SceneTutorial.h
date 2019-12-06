#pragma once
#include "Scene.h"


class SceneTutorial : public Scene
{
private:

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};