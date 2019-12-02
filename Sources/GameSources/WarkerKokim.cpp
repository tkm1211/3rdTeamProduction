#include "WarkerKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "WarkerAttack.h"
#include "WarkerMove.h"
#include "WarkerWait.h"
#include "GoToPlayer.h"
#include "Turn.h"
extern _Player _player;

WarkerKokim::WarkerKokim()
{
	brain.SetObj(&modelData);

	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY,NULL,NULL);
	{
		//aiTree.AddNode("Root", "Attack", 1, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, WarkerMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, GotoPlayerJudge::GetInstance(), GotoPlayerAction::GetInstance());
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, TurnJudge::GetInstance(), TurnAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, NULL, WarkerWaitAction::GetInstance());
	}

	brain.SetBehaviorTree(&aiTree);

}

void WarkerKokim::Update()
{
	DirectX::XMFLOAT3 vec;
	DirectX::XMStoreFloat3(&vec,
		DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&_player.pos),
			DirectX::XMLoadFloat3(&modelData.GetPos())));

	float dis;
	DirectX::XMStoreFloat(&dis,DirectX::XMVector3Length(
		DirectX::XMLoadFloat3(&vec)));

	brain.SetEtoPdis(dis);

	brain.Update();
}