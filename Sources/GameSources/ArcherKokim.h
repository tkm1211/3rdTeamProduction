#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "AI.h"
#include "Shot.h"
#include "directxmath.h"
#include "Collision.h"
#define RECAST_MAX 300

class ArcherKokim :
	public AI
{
public:
	ArcherKokim();
	ArcherKokim(const ArcherKokim&) {};
	virtual ~ArcherKokim() {};

	void Update();

	Shot* GetArrow() { return arrow.get(); };
	std::shared_ptr<OBJ3D> GetModelData() { return modelData; };
	CollisionPrimitive* GetBodyCollision() { return bodyCol.get(); };
	bool GetNowShot() { return nowShot; };
	int	 GetRecast() { return recast; };

		
	void SetRecast(int hRecast) { recast = hRecast; };

	void CreateArrow(DirectX::XMFLOAT3 pPos, DirectX::XMFLOAT3 ePos) { arrow = std::make_unique<Shot>(pPos, ePos); };
private:

	std::shared_ptr<CollisionPrimitive> bodyCol;
	std::unique_ptr<Shot> arrow;
	std::shared_ptr<OBJ3D> modelData = {};
	bool nowShot=false;
	int recast = NULL;
};

