#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Collision.h"

#include "BuffArea.h"
#include "Billboard.h"
class SceneTitle : public Scene
{
private:
	
public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};