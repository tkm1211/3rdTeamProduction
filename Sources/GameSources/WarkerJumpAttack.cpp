#include "WarkerJumpAttack.h"
#include "WarkerKokim.h"

bool WarkerJumpAttackJudge::Judgement(AI * obj)
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

	if (warker->stAttack == WARKER_ATTACK_STATE::JUMP_ATTACK)
	{
		return true;
	}
	return false;
}

ActionBase::STATE WarkerJumpAttackAction::Update(AI * obj)
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

	if (!warker->isJumpAttack)
	{
		warker->modelData->SetIsAnimation(true);
		warker->modelData->SetIsLoopAnimation(false);
		warker->isJumpAttack = true;
	}

	if (!warker->nowJumpAttack)
	{
		warker->nowJumpAttack = true;
		warker->atJumpVec = warker->vec;
	}

	if (warker->isJumpAttack && !warker->modelData->GetIsAnimation())
	{
		warker->isJumpAttack = false;
	}

	warker->SetState(WARKER_STATE::JUMP_ATTACK);

	return ActionBase::STATE::COMPLETE;
}
