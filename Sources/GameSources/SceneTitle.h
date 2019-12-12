#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"


class SceneTitle : public Scene
{
private:
	std::unique_ptr<SpriteBatch> titleBgSpr;
	TexData titleBgSprData;
	std::unique_ptr<SpriteBatch> startSpr;
	TexData startSprData;

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};