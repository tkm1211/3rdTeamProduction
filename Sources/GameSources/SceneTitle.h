#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Collision.h"


class SceneTitle : public Scene
{
public:

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};