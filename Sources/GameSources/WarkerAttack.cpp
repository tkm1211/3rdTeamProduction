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

	if (obj->GetEtoPdis() < 50 && warker->GetPlayerDot()> 0.99f)
	{
		return true;
	}
	return false;
}
