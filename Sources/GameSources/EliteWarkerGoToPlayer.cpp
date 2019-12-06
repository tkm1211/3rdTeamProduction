#include "EliteWarkerGoToPlayer.h"
#include "AI.h"
#include "OBJ3D.h"
#include "EnemyManager.h"
extern _Player _player;

ActionBase::STATE EliteWarkerGotoPlayerAction::Update(AI * obj)
{
	OBJ3D&o = *obj->GetObj();

	o.SetAngleY(atan2(_player.pos.x - o.GetPos().x, _player.pos.z - o.GetPos().z));

	o.SetSpeed(DirectX::XMFLOAT3(sinf(o.GetAngle().y)*VELOCITY_ELITE_WARKER, 0, cosf(o.GetAngle().y)*VELOCITY_ELITE_WARKER));

	DirectX::XMFLOAT3 lPos;
	DirectX::XMStoreFloat3(&lPos,
		DirectX::XMVectorAdd(
			DirectX::XMLoadFloat3(&o.GetPos()),
			DirectX::XMLoadFloat3(&o.GetSpeed())));

	o.SetPos(lPos);

	obj->SetObj(&o);

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
