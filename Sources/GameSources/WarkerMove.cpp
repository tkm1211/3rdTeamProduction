#include "WarkerMove.h"
#include "OBJ3D.h"
#include "AI.h"

bool WarkerMoveJudge::Judgement(AI *obj)
{

	if (obj->GetEtoPdis() < 1000)
	{
		return true;
	}

	return false;
}