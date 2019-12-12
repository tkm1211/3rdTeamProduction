#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"

class BG
{

private:
	std::unique_ptr<Model> wall;
	std::unique_ptr<Model> ground;

	OBJ3D modelData;

public:
	std::unique_ptr<CollisionPrimitive> wallCollision;

public:
	BG() {}
	~BG() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void ImGui();

};


