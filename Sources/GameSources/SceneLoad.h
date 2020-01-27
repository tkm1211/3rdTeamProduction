#pragma once
#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"
#include "GameTimer.h"

class SceneLoad : public Scene
{
private:


public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};