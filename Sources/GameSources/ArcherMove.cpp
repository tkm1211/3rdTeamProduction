#include "ArcherMove.h"
#include "AI.h"


bool ArcherMoveJudge::Judgement(AI * obj)
{
	
	if (obj->GetEtoPdis() < 1000)
	{
		return true;
	}
	return false;
}
