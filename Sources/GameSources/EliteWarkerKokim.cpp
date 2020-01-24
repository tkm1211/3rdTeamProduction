#include "EliteWarkerKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "EliteWarkerMove.h"
#include "EliteWarkerWait.h"
#include "CharacterSystem.h"
EliteWarkerKokim::EliteWarkerKokim(int num)
{
	modelData = std::make_shared<OBJ3DInstance>();

	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, EliteWarkerMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, EliteWarkerGotoPlayerJudge::GetInstance(), EliteWarkerGotoPlayerAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, NULL, EliteWarkerWaitAction::GetInstance());
	}

	SetBehaviorTree(aiTree);

	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(160, 160, 160));

	index = num;
}

void EliteWarkerKokim::Init()
{
	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, EliteWarkerMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, EliteWarkerGotoPlayerJudge::GetInstance(), EliteWarkerGotoPlayerAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, NULL, EliteWarkerWaitAction::GetInstance());
	}

	SetBehaviorTree(aiTree);

	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(160, 160, 160));
}

void EliteWarkerKokim::Update()
{
	OBJ3D& pTrs = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData();

	DirectX::XMFLOAT3 vec;
	DirectX::XMStoreFloat3(&vec,
		DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&pTrs.GetPos()),
			DirectX::XMLoadFloat3(&modelData->GetPos())));

	float dis;
	DirectX::XMStoreFloat(&dis, DirectX::XMVector3Length(
		DirectX::XMLoadFloat3(&vec)));

	SetEtoPdis(dis);

	AI::Update();
	bodyCol->SetPos(modelData->GetPos());
}
