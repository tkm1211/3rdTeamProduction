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
	WarkerKokim* warker = reinterpret_cast<WarkerKokim*>(obj);
#endif

	if (!warker->pWarkerAttack->GetAnimatingFlg()&& !warker->pWarkerJumpAttack->GetAnimatingFlg())
	{
		if (obj->GetEtoPdis() <= (float)warker->GetAttackDistance() &&
			warker->GetPlayerDot() > 0.99f&&
			warker->GetStrikeRecastMax() < warker->GetStrikeRecastCnt())
		{
			int atRand = rand() % 10;
			if (atRand > 6)
			{
				warker->stAttack = WARKER_ATTACK_STATE::JUMP_ATTACK;
			}
			else
			{
				warker->stAttack = WARKER_ATTACK_STATE::STRIKE;
			}
			warker->SetStrikeRecastCnt(0);
			return true;

		}
	}
	else
	{

		return true;
	}
	warker->SetStrikeRecastCnt(warker->GetStrikeRecastCnt() + 1);

	return false;
}
