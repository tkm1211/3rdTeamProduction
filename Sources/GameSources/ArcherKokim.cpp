#include "ArcherKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "ArcherMove.h"
#include "ArcherTurn.h"

extern _Player _player;

ArcherKokim::ArcherKokim()
{
	brain.SetObj(&modelData);

	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTree.AddNode("Root", "Move", 1, BehaviorTree::SELECT_RULE::PRIORITY, ArcherMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, ArcherTurnJudge::GetInstance(), ArcherTurnAction::GetInstance());
		}
	}

	brain.SetBehaviorTree(&aiTree);
}

void ArcherKokim::Update()
{
	DirectX::XMFLOAT3 vec;
	DirectX::XMStoreFloat3(&vec,
		DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&_player.pos),
			DirectX::XMLoadFloat3(&modelData.GetPos())));

	float dis;
	DirectX::XMStoreFloat(&dis, DirectX::XMVector3Length(
		DirectX::XMLoadFloat3(&vec)));

	brain.SetEtoPdis(dis);

	brain.Update();
}
