#pragma once

#include "Collision.h"
#include "SwordLocusSprite.h"
#include "FrameWork.h"
#include "MathFunction.h"


class SwordLocus
{
private:
	struct collisionInfo
	{
		std::unique_ptr<CollisionPrimitive> swordPoint;
		std::unique_ptr<CollisionPrimitive> handPoint;
	};

	std::unique_ptr<SwordLocusSprite> spr;

	collisionInfo ci[9 * 11 + 1];

	int num;

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	void SetEffectPoint(DirectX::XMFLOAT3 oldSword, DirectX::XMFLOAT3 oldHand, DirectX::XMFLOAT3 originPos);
};