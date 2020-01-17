#pragma once
#include "Collision.h"

class SwordLocus
{
private:
	struct collisionInfo
	{
		std::unique_ptr<CollisionPrimitive> swordPoint;
		std::unique_ptr<CollisionPrimitive> handPoint;
	};

	collisionInfo ci[10];

	int num;

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	void SetEffectPoint(DirectX::XMFLOAT3 oldSword, DirectX::XMFLOAT3 oldHand) 
	{
		if (num > 9) num = 0;
		ci[num].handPoint->SetPos(oldHand);
		ci[num].swordPoint->SetPos(oldSword);
		num++;
	}

};