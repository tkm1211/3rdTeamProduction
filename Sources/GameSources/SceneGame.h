#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Collision.h"

#include "BuffArea.h"
#include "BG.h"
#include "Billboard.h"
#include "Sprite.h"
#include "WaveTex.h"


class SceneGame : public Scene
{
private:
	WaveTex waveTex;

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};
