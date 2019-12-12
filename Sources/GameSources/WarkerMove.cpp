#include "WarkerMove.h"
#include "WarkerKokim.h"
#include "OBJ3D.h"
#include "AI.h"

bool WarkerMoveJudge::Judgement(AI *obj)
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

	if (obj->GetEtoPdis() > 50&&obj->GetEtoPdis() < warker->GetFindPlayerDistance())
	{
		return true;
	}
	/*else if()
	{

	}*/

	return false;
}