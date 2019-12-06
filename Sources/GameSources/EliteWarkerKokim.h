#pragma once
#include "Job.h"
#include "Model.h"
#include "OBJ3D.h"
#include "AI.h"

class EliteWarkerKokim:
	public AI
{
public:
	EliteWarkerKokim();
	~EliteWarkerKokim() {};

	void Update();

	OBJ3D* GetModelData() { return &modelData; };
private:

	/*AI brain;*/
	OBJ3D modelData = {};
};