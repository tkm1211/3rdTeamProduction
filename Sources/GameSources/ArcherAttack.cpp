#include "ArcherAttack.h"
#include "ArcherKokim.h"
#include "AI.h"
#include "CharacterSystem.h"

bool ArcherAttackJudge::Judgement(AI * obj)
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
	if (!archer->pArcherAttack->GetAnimatingFlg())
	{

		if (obj->GetEtoPdis() < archer->atDis && archer->GetPlayerDot() > 0.99f && archer->GetRecast() > archer->recastMax)
		{
			OBJ3D &pTrs = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData();
			archer->state = ARCHER_STATE::STRIKE;
			archer->CreateArrow(pTrs.GetPos(), archer->GetModelData()->GetPos());
			archer->arrow->GetModelData().SetPos(archer->GetModelData()->GetPos());
			archer->arrow->GetModelData().SetPosY(50);
			archer->arrow->GetModelData().SetAngleY(archer->modelData->GetAngle().y);
			archer->SetRecast(0);

			return true;
		}
	}
	else
	{
		return true;
	}
	return false;
}
