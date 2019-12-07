#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "AI.h"
#include "Collision.h"


class EliteWarkerKokim:
	public AI
{
public:
	EliteWarkerKokim();
	EliteWarkerKokim(const EliteWarkerKokim&) {};
	~EliteWarkerKokim() {};

	void Update();

	std::shared_ptr<OBJ3D> GetModelData() { return modelData; };
	CollisionPrimitive* GetBodyCollision() { return bodyCol.get(); };

private:

	std::unique_ptr<CollisionPrimitive> bodyCol;
	std::shared_ptr<OBJ3D> modelData;
};