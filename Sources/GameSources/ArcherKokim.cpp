#include "ArcherKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "ArcherMove.h"
#include "ArcherTurn.h"
#include "ArcherAttack.h"
#include "ArcherShot.h"
#include "ArcherWait.h"

extern _Player _player;

ArcherKokim::ArcherKokim()
{
	SetObj(&modelData);

	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING, NULL, NULL);
	{
		aiTree.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING, ArcherAttackJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Attack", "ArcherShot", 1, BehaviorTree::SELECT_RULE::NON, ArcherShotJudge::GetInstance(), ArcherShotAction::GetInstance());
		}
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::SEQUENTIAL_LOOPING, ArcherMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, ArcherTurnJudge::GetInstance(), ArcherTurnAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, ArcherWaitJudge::GetInstance(), NULL);
	}

	SetBehaviorTree(&aiTree);
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

	SetEtoPdis(dis);

	recast++;
	AI::Update();
}
