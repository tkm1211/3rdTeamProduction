#include "WarkerWait.h"
#include "WarkerKokim.h"

ActionBase::STATE WarkerWaitAction::Update(AI * obj)
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

	warker->SetState(WARKER_STATE::WAIT);

	return ActionBase::COMPLETE;
}
