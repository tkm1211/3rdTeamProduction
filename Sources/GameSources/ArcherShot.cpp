#include "ArcherShot.h"
#include "ArcherKokim.h"
#include "AI.h"
#include "EnemyManager.h"
#include "CharacterSystem.h"
bool ArcherShotJudge::Judgement(AI * obj)
{
#if defined(_DEBUG)
	ArcherKokim* archer = dynamic_cast<ArcherKokim*>(obj);
	if (archer == nullptr)
	{
		assert(0);
	}
#else
	ArcherKokim* archer = reinterpret_cast<ArcherKokim*>(obj);
#endif

	if (archer->GetRecast() > archer->recastMax)
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
	ArcherKokim* archer = reinterpret_cast<ArcherKokim*>(obj);
#endif

	OBJ3D &pTrs = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData();
	archer->state = ARCHER_STATE::STRIKE;
	archer->CreateArrow(pTrs.GetPos(), archer->GetModelData()->GetPos());
	archer->arrow->GetModelData().SetPos(archer->GetModelData()->GetPos());
	archer->SetRecast(0);

	return ActionBase::STATE::COMPLETE;
}
