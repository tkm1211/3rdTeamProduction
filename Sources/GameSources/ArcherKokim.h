#pragma once
#include "Job.h"
#include "Model.h"
#include "OBJ3D.h"
#include "AI.h"
#include "Shot.h"
#include "directxmath.h"

#define RECAST_MAX 300

class ArcherKokim :
	public AI
{
public:
	ArcherKokim();
	ArcherKokim(const ArcherKokim&) 
	{
	
	};
	virtual ~ArcherKokim() {};

	void Update();

	Shot* GetArrow() { return arrow.get(); };
	OBJ3D *GetModelData() { return &modelData; };
	bool GetNowShot() { return nowShot; };
	int	 GetRecast() { return recast; };

	void SetRecast(int hRecast) { recast = hRecast; };

	void CreateArrow(DirectX::XMFLOAT3 pPos, DirectX::XMFLOAT3 ePos) { arrow = std::make_unique<Shot>(pPos, ePos); };
private:

	std::unique_ptr<Shot> arrow;
	OBJ3D modelData = {};
	bool nowShot=false;
	int recast = NULL;
};

