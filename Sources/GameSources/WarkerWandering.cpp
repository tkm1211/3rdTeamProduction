#include "WarkerWandering.h"
#include "AI.h"
#include "OBJ3D.h"
#include "EnemyManager.h"
#include "CharacterSystem.h"

bool WarkerWanderingJudge::Judgement(AI* obj)
{
#if defined(_DEBUG)
	WarkerKokim* warker = dynamic_cast<WarkerKokim*>(obj);
	if (warker == nullptr)
	{
		assert(0);
	}
#else
	WarkerKokim* warker = reinterpret_cast<WarkerKokim*>(obj);
#endif

	if (warker->wanderingRct > warker->wanderingRctMax && obj->GetEtoPdis() > 150)
	{
		return true;
	}

	return false;
}

ActionBase::STATE WarkerWanderingAction::Update(AI*obj)
{
#if defined(_DEBUG)
	WarkerKokim* warker = dynamic_cast<WarkerKokim*>(obj);
	if (warker == nullptr)
	{
		assert(0);
	}
#else
	WarkerKokim* warker = reinterpret_cast<WarkerKokim*>(obj);
#endif
	
	OBJ3DInstance &o = *warker->GetModelData();
	switch (warker->stWandering)
	{
	case 0:
		warker->randAng = ((float)(rand() % (314159))/10000.f) * 2;
		o.SetSpeed(DirectX::XMFLOAT3(sinf(warker->randAng)*warker->velocity, 0, cosf(warker->randAng)*warker->velocity));
		o.SetAngleY(atan2(sinf(warker->randAng), cosf(warker->randAng)));
		warker->wanderingCnt = 0;
		warker->SetState(WARKER_STATE::RUN);
		warker->stWandering++;
	case 1:
		DirectX::XMFLOAT3 lPos;
		DirectX::XMStoreFloat3(&lPos,
			DirectX::XMVectorAdd(
				DirectX::XMLoadFloat3(&o.GetPos()),
				DirectX::XMLoadFloat3(&o.GetSpeed())));

		o.SetPos(lPos);

		
		if (warker->wanderingCnt > 60)
		{
			warker->wanderingRct = 0;
			warker->stWandering = 0;
		}
		else
		{
			warker->wanderingCnt++;
		}
		break;
	}

	return ActionBase::STATE::COMPLETE;
}