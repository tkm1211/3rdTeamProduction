#include "ArcherAttack.h"
#include "ArcherKokim.h"
#include "AI.h"

bool ArcherAttackJudge::Judgement(AI * obj)
{
#if defined(_DEBUG)
	ArcherKokim* archer = dynamic_cast<ArcherKokim*>(obj);
	if (archer == nullptr)
	{
		assert(0);
	}
#else
	ArcherKokim* archer = reinterpret_cast<ArcherKokim*>(job);
#endif
	if (obj->GetEtoPdis() < 1000 && archer->GetPlayerDot()> 0.99f)
	{
		return true;
	}
	return false;
}