#include "WarkerStrike.h"
#include "WarkerKokim.h"

bool WarkerStrikeJudge::Judgement(AI * obj)
{
	return true;
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
	WarkerKokim* warker = reinterpret_cast<WarkerKokim*>(job);
#endif

	warker->SetState(WARKER_STATE::STRIKE);

	return ActionBase::STATE::COMPLETE;
}
