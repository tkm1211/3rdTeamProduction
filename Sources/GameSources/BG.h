#pragma once
#include "Model.h"
#include "OBJ3D.h"

class BG
{

private:
	std::unique_ptr<Model> ground;

	OBJ3D modelData;

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

};