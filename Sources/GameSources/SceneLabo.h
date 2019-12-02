#pragma once

#include "Scene.h"
#include "Model.h"
#include "OBJ3D.h"
#include "PlayerTemplate.h"
#include "Collision.h"


class SceneLabo : public Scene
{
private:
	PlayerTemplate player;
	std::unique_ptr<Model> pPlayer;
	OBJ3D playerData;
	float radius;

	std::unique_ptr<Model> pItem;
	OBJ3D itemData;

	std::unique_ptr<CollisionPrimitive> pPlayerCube;
	std::unique_ptr<CollisionPrimitive> pGroundCube;

	std::unique_ptr<CollisionPrimitive> pPlayerCylinder;
	std::unique_ptr<CollisionPrimitive> pGroundCylinder;

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};