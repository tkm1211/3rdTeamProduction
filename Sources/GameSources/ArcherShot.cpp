#include "ArcherShot.h"
#include "ArcherKokim.h"
#include "AI.h"
#include "EnemyManager.h"
extern _Player _player;

bool ArcherShotJudge::Judgement(AI * obj)
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

	if (archer->GetRecast() > RECAST_MAX)
	{
		return true;
	}
	return false;
}

ActionBase::STATE ArcherShotAction::Update(AI * obj)
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

	archer->CreateArrow(_player.pos, archer->GetObj()->GetPos());
	archer->SetRecast(0);

	return ActionBase::STATE::COMPLETE;
}
