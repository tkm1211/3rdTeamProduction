#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "AI.h"
class Player;

class WarkerKokim
{
public:
	WarkerKokim();
	~WarkerKokim() {};

	void Update();

	OBJ3D GetModelData() { return modelData; };
private:

	AI brain;
	OBJ3D modelData = {};
};

