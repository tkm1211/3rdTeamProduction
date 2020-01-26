#include "WarkerStrike.h"
#include "WarkerKokim.h"

bool WarkerStrikeJudge::Judgement(AI * obj)
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


	/*if (obj->GetEtoPdis() <= (float)warker->GetAttackDistance() &&
		warker->GetPlayerDot()> 0.99f&&
		warker->GetStrikeRecastMax() <  warker->GetStrikeRecastCnt())
	{

		if (!warker->pWarkerAttack->GetFinishAnimation())
		{
			return true;
		}
		else
		{
			warker->SetStrikeRecastCnt(0);

		}
	}*/

	if (warker->stAttack == WARKER_ATTACK_STATE::STRIKE)
	{
		return true;
	}
	return false;
}

ActionBase::STATE WarkerStrikeAction::Update(AI * obj)
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

	if (!warker->isAttack)
	{
		warker->modelData->SetIsAnimation(true);
		warker->modelData->SetIsLoopAnimation(false);
		warker->isAttack = true;
	}
	if (warker->isAttack && !warker->modelData->GetIsAnimation())
	{
		warker->isAttack = false;
	}

	warker->SetState(WARKER_STATE::STRIKE);

	return ActionBase::STATE::COMPLETE;
}
