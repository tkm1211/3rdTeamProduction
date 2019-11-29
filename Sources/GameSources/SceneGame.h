#pragma once

#include "Scene.h"


class SceneGame : public Scene
{
public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};