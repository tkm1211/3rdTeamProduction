#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "AI.h"
#include "Collision.h"
class Player;

class WarkerKokim:
	public AI
{
public:
	WarkerKokim();
	WarkerKokim(const WarkerKokim&) {};
	~WarkerKokim() {};

	void Update();

	std::shared_ptr<OBJ3D> GetModelData() { return modelData; };
	CollisionPrimitive* GetBodyCollision() { return bodyCol.get(); };

private:

	std::unique_ptr<CollisionPrimitive> bodyCol;
	std::shared_ptr<OBJ3D> modelData;
};

