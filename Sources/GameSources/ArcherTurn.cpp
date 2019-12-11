#include "ArcherTurn.h"
#include "AI.h"
#include "OBJ3D.h"
#include "EnemyManager.h"
extern _Player _player;

ActionBase::STATE ArcherTurnAction::Update(AI * obj)
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
	OBJ3D &o = *archer->GetModelData();

	DirectX::XMVECTOR oVec = DirectX::XMVector3Normalize(
		DirectX::XMVectorSet(sinf(o.GetAngle().y), 0, cosf(o.GetAngle().y), 0));

	DirectX::XMVECTOR vecEtoP =
		DirectX::XMVector3Normalize(
			DirectX::XMVectorSubtract(
				DirectX::XMLoadFloat3(&_player.pos),
				DirectX::XMLoadFloat3(&o.GetPos())));

	DirectX::XMFLOAT3 cross;
	DirectX::XMStoreFloat3(&cross,
		DirectX::XMVector3Cross(
			oVec,
			vecEtoP));

	if (cross.y < -TURN_SPEED*2)
	{
		o.SetAngleY(o.GetAngle().y -TURN_SPEED);
		
	}
	else if(cross.y > TURN_SPEED*2)
	{
		o.SetAngleY(o.GetAngle().y + TURN_SPEED);
	}

	return ActionBase::STATE::COMPLETE;
}

bool ArcherTurnJudge::Judgement(AI * obj)
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
	OBJ3D &o = *archer->GetModelData();

	DirectX::XMVECTOR oVec = DirectX::XMVectorSet(cosf(o.GetAngle().y), 0, sinf(o.GetAngle().y), 0);

	DirectX::XMVECTOR vecEtoP =
		DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&_player.pos),
			DirectX::XMLoadFloat3(&o.GetPos()));

	float dot;
	DirectX::XMStoreFloat(&dot, DirectX::XMVector3Dot(oVec, vecEtoP));

	if (dot!=0)
	{
		return true;
	}


	return false;
}
