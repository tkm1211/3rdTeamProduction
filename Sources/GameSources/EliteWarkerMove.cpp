#include "EliteWarkerMove.h"
#include "AI.h"

bool EliteWarkerMoveJudge::Judgement(AI * obj)
{
	if (obj->GetEtoPdis() < 1000)
	{
		return true;
	}

	return false;
}

