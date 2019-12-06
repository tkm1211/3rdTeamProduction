#pragma once
#include "Scene.h"


class ScenePause : public Scene
{
private:

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};