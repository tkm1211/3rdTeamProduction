#include "ArcherKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "ArcherMove.h"
#include "ArcherTurn.h"
#include "ArcherAttack.h"
#include "ArcherShot.h"
#include "ArcherWait.h"
#include "CharacterSystem.h"
ArcherKokim::ArcherKokim(int num)
{
	modelData = std::make_shared<OBJ3D>();
	
	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTree.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, ArcherAttackJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Attack", "ArcherShot", 1, BehaviorTree::SELECT_RULE::NON, ArcherShotJudge::GetInstance(), ArcherShotAction::GetInstance());
		}
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, ArcherMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, ArcherTurnJudge::GetInstance(), ArcherTurnAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, ArcherWaitJudge::GetInstance(), NULL);
	}

	SetBehaviorTree(&aiTree);

	bodyCol= std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));

	index = num;
}

void ArcherKokim::Init()
{
	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTree.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, ArcherAttackJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Attack", "ArcherShot", 1, BehaviorTree::SELECT_RULE::NON, ArcherShotJudge::GetInstance(), ArcherShotAction::GetInstance());
		}
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, ArcherMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, ArcherTurnJudge::GetInstance(), ArcherTurnAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, ArcherWaitJudge::GetInstance(), NULL);
	}

	SetBehaviorTree(&aiTree);

	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));
}

void ArcherKokim::Update()
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

	DirectX::XMVECTOR plForward = DirectX::XMVectorSet(sinf(modelData->GetAngle().y),0,cosf(modelData->GetAngle().y),1);

	plForward = DirectX::XMVector3Normalize(plForward);
	DirectX::XMStoreFloat3(&vec,
		DirectX::XMVector3Normalize(
			DirectX::XMLoadFloat3(&vec)));

	DirectX::XMStoreFloat(&plDot,
		DirectX::XMVector3Dot(
			DirectX::XMLoadFloat3(&vec),
			plForward));

	recast++;
	AI::Update();
	bodyCol->SetPos(modelData->GetPos());
}

