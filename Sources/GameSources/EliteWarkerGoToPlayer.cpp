#include "EliteWarkerGoToPlayer.h"
#include "AI.h"
#include "OBJ3D.h"
#include "EnemyManager.h"
#include "CharacterSystem.h"

ActionBase::STATE EliteWarkerGotoPlayerAction::Update(AI * obj)
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
	OBJ3D&o = *archer->GetModelData();
	OBJ3D& pTrs = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData();

	o.SetAngleY(atan2(pTrs.GetPos().x - o.GetPos().x, pTrs.GetPos().z - o.GetPos().z));

	o.SetSpeed(DirectX::XMFLOAT3(sinf(o.GetAngle().y)*VELOCITY_ELITE_WARKER, 0, cosf(o.GetAngle().y)*VELOCITY_ELITE_WARKER));

	DirectX::XMFLOAT3 lPos;
	DirectX::XMStoreFloat3(&lPos,
		DirectX::XMVectorAdd(
			DirectX::XMLoadFloat3(&o.GetPos()),
			DirectX::XMLoadFloat3(&o.GetSpeed())));

	o.SetPos(lPos);

	return ActionBase::STATE::COMPLETE;
}

bool EliteWarkerGotoPlayerJudge::Judgement(AI * obj)
{
	if (obj->GetEtoPdis() < 10)
	{
		return false;
	}

	return true;
}
