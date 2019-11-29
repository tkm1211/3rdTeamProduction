#pragma once

#include "Scene.h"
#include "Model.h"
#include "OBJ3D.h"
#include "PlayerTemplate.h"


class SceneLabo : public Scene
{
private:
	PlayerTemplate player;
	std::unique_ptr<Model> pBack;
	OBJ3D backData;

	std::unique_ptr<Model> pItem;
	OBJ3D itemData;

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};