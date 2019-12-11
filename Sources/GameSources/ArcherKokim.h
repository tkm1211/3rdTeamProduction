#pragma once

#include "AI.h"
#include "Kokim.h"

#include "Shot.h"
#define RECAST_MAX 300

class Shot;
class ArcherKokim :
	 public AI, public Kokim
{
public:
	ArcherKokim() {};
	ArcherKokim(int num);
	virtual ~ArcherKokim() {};

	void Init();

	void Update();

	Shot* GetArrow() { return arrow.get(); };
	bool GetNowShot() { return nowShot; };
	int	 GetRecast() { return recast; };
	float GetPlayerDot() { return plDot; };
		
	void SetRecast(int hRecast) { recast = hRecast; };

	void CreateArrow(DirectX::XMFLOAT3 pPos, DirectX::XMFLOAT3 ePos) { arrow = std::make_unique<Shot>(pPos, ePos); };

private:
	std::shared_ptr<Shot> arrow;
	bool nowShot=false;
	int recast = NULL;
	float plDot;

};

