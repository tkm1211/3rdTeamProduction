#include "ArcherAttack.h"
#include "AI.h"
bool ArcherAttackJudge::Judgement(AI * obj)
{
	if (obj->GetEtoPdis() < 1000)
	{
		return true;
	}
	return false;
}
