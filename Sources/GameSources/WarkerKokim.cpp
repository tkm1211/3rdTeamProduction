#include "WarkerKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "WarkerAttack.h"
#include "WarkerStrike.h"
#include "WarkerMove.h"
#include "WarkerWait.h"
#include "GoToPlayer.h"
#include "Turn.h"
#include "CharacterSystem.h"
WarkerKokim::WarkerKokim(int num)
{
	modelData = std::make_shared<OBJ3D>();

	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY,NULL,NULL);
	{
		aiTree.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, WarkerAttackJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Attack", "WarkerStrike", 1, BehaviorTree::SELECT_RULE::NON, WarkerStrikeJudge::GetInstance(), WarkerStrikeAction::GetInstance());

		}
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, WarkerMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, GotoPlayerJudge::GetInstance(), GotoPlayerAction::GetInstance());
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, TurnJudge::GetInstance(), TurnAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, NULL, WarkerWaitAction::GetInstance());
	}

	SetBehaviorTree(&aiTree);
	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(10, 10, 10));
	index = num;
	state = WARKER_STATE::RUN;
	Update();
	
}

void WarkerKokim::Init()
{
	static BehaviorTree aiTree;

	aiTree.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTree.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, WarkerAttackJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Attack", "WarkerStrike", 1, BehaviorTree::SELECT_RULE::NON, WarkerStrikeJudge::GetInstance(), WarkerStrikeAction::GetInstance());
		}
		aiTree.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, WarkerMoveJudge::GetInstance(), NULL);
		{
			aiTree.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, GotoPlayerJudge::GetInstance(), GotoPlayerAction::GetInstance());
			aiTree.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, TurnJudge::GetInstance(), TurnAction::GetInstance());
		}
		aiTree.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, NULL, WarkerWaitAction::GetInstance());
	}

	SetBehaviorTree(&aiTree);
	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(10, 10, 10));

}

void WarkerKokim::Update()
{
	if (!nowAsphyxia)
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

		DirectX::XMVECTOR plForward = DirectX::XMVectorSet(sinf(modelData->GetAngle().y), 0, cosf(modelData->GetAngle().y), 1);

		plForward = DirectX::XMVector3Normalize(plForward);
		DirectX::XMStoreFloat3(&vec,
			DirectX::XMVector3Normalize(
				DirectX::XMLoadFloat3(&vec)));

		DirectX::XMStoreFloat(&plDot,
			DirectX::XMVector3Dot(
				DirectX::XMLoadFloat3(&vec),
				plForward));

		AI::Update();
		bodyCol->SetPos(modelData->GetPos());

		if (damageRecast > 0)
		{
			damageRecast--;
		}
		

		if (hp <= 0)
		{
			ChangeNowAsphyxia();
		}
	}
	else
	{
		state = WARKER_STATE::TPOSE;
		modelData->SetPosY(110);
	}
}
