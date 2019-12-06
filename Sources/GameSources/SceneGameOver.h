#pragma once
#include "Scene.h"


class SceneGameOver : public Scene
{
private:

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};