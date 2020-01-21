#pragma once
#include "Collision.h"
#include "SwordLocusSprite.h"
#include "FrameWork.h"

class SwordLocus
{
private:
	struct collisionInfo
	{
		std::unique_ptr<CollisionPrimitive> swordPoint;
		std::unique_ptr<CollisionPrimitive> handPoint;
	};

	std::unique_ptr<SwordLocusSprite> spr;

	collisionInfo ci[11];

	int num;

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	void SetEffectPoint(DirectX::XMFLOAT3 oldSword, DirectX::XMFLOAT3 oldHand, DirectX::XMFLOAT3) 
	{
		if (num > 10) num = 0;
		ci[num].handPoint->SetPos(oldHand);
		ci[num].swordPoint->SetPos(oldSword);
		
		int t = num;
		for (int i = 0; i < 11; i++)
		{
			spr->meshInfo[i].dPos = ci[t].handPoint->GetPos();
			spr->meshInfo[i].uPos = ci[t].swordPoint->GetPos();

			t++;
			if (t > 10) t = 0;

		}
		num++;

		spr->CreateMesh(FrameWork::GetInstance().GetDevice().Get(), {1024, 0, 1024, 1024});

	}

};