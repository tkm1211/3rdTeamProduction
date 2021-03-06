#include "GoToPlayer.h"
#include "AI.h"
#include "OBJ3D.h"
#include "EnemyManager.h"
#include "CharacterSystem.h"

bool GotoPlayerJudge::Judgement(AI* obj)
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
	if (obj->GetEtoPdis() < 100 || warker->hidame)
	{
		return false;
	}

	return true;
}

ActionBase::STATE GotoPlayerAction::Update(AI*obj)
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
	OBJ3DInstance &o = *warker->GetModelData();
	OBJ3D &pTrs = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData();
	o.SetAngleY(atan2(pTrs.GetPos().x - o.GetPos().x, pTrs.GetPos().z - o.GetPos().z));

	o.SetSpeed(DirectX::XMFLOAT3(sinf(o.GetAngle().y)*warker->GetVelocity(), 0, cosf(o.GetAngle().y)*warker->GetVelocity()));

	DirectX::XMFLOAT3 lPos;
	DirectX::XMStoreFloat3(&lPos,
		DirectX::XMVectorAdd(
			DirectX::XMLoadFloat3(&o.GetPos()),
			DirectX::XMLoadFloat3(&o.GetSpeed())));

	o.SetPos(lPos);

	warker->SetState(WARKER_STATE::RUN);

	return ActionBase::STATE::COMPLETE;
}