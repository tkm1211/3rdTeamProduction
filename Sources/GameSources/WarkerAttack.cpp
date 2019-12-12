#include "WarkerAttack.h"
#include "WarkerKokim.h"

bool WarkerAttackJudge::Judgement(AI * obj)
{
#if defined(_DEBUG)
	WarkerKokim* warker = dynamic_cast<WarkerKokim*>(obj);
	if (warker == nullptr)
	{
		assert(0);
	}
#else
	WarkerKokim* warker = reinterpret_cast<WarkerKokim*>(job);
#endif

	if (obj->GetEtoPdis() < warker->GetAttackDistance() &&
		warker->GetPlayerDot()> 0.99f&&
		warker->GetStrikeRecastMax() <  warker->GetStrikeRecastCnt())
	{

		if (!pWarkerAttack->GetFinishAnimation())
		{
			return true;
		}
		else
		{
			warker->SetStrikeRecastCnt(0);
			
		}
	}

	warker->SetStrikeRecastCnt(warker->GetStrikeRecastCnt() + 1);
	return false;
}
