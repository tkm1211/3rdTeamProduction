#include "WarkerKokim.h"
#include "EnemyManager.h"
#include "BehaviorTree.h"
#include "WarkerAttack.h"
#include "WarkerStrike.h"
#include "WarkerJumpAttack.h"
#include "WarkerMove.h"
#include "WarkerWait.h"
#include "WarkerWandering.h"
#include "WarkerStay.h"
#include "GoToPlayer.h"
#include "Turn.h"
#include "CharacterSystem.h"
WarkerKokim::WarkerKokim(int num)
{
	{
		pWarker = std::make_shared<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);
		pWarkerAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerAttack.fbx", false);
		pWarkerJumpAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerJumpAttack.fbx", false);
		pWarkerRun = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerRun.fbx", false);
		pWarkerWait = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerWait.fbx", false);
	}

	WarkerAttackJudge::GetInstance()->pWarkerAttack = pWarkerAttack;

	modelData = std::make_shared<OBJ3D>();


	aiTreeData.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY,NULL,NULL);
	{
		aiTreeData.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, WarkerAttackJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Attack", "WarkerStrike", 2, BehaviorTree::SELECT_RULE::NON, WarkerStrikeJudge::GetInstance(), WarkerStrikeAction::GetInstance());
			aiTreeData.AddNode("Attack", "WarkerJumpAttack", 1, BehaviorTree::SELECT_RULE::NON, WarkerJumpAttackJudge::GetInstance(), WarkerJumpAttackAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, WarkerMoveJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, GotoPlayerJudge::GetInstance(), GotoPlayerAction::GetInstance());
			aiTreeData.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, TurnJudge::GetInstance(), TurnAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
		{
			aiTreeData.AddNode("Wait", "Wandering", 2, BehaviorTree::SELECT_RULE::NON, WarkerWanderingJudge::GetInstance(), WarkerWanderingAction::GetInstance());
			aiTreeData.AddNode("Wait", "Stay", 1, BehaviorTree::SELECT_RULE::NON, NULL, WarkerStayAction::GetInstance());
		}
	}

	SetBehaviorTree(aiTreeData);
	wanderingRct = 0;
	wanderingRctMax = 180;
	velocity = 5;
	randAng = 0;
	stWandering = 0;
	wanderingCnt = 0;
	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(60, 180, 60));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(20, 20, 20));

	state = WARKER_STATE::WAIT;
	Update();
	
}

void WarkerKokim::Init()
{

	{
		pWarker = std::make_shared<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);
		pWarkerAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerAttack.fbx", false);
		pWarkerJumpAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerJumpAttack.fbx", false);
		pWarkerRun = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerRun.fbx", false);
		pWarkerWait = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerWait.fbx", false);
	}

	WarkerAttackJudge::GetInstance()->pWarkerAttack = pWarkerAttack;
	
	aiTreeData.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTreeData.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, WarkerAttackJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Attack", "WarkerStrike", 2, BehaviorTree::SELECT_RULE::NON, WarkerStrikeJudge::GetInstance(), WarkerStrikeAction::GetInstance());
			aiTreeData.AddNode("Attack", "WarkerJumpAttack", 1, BehaviorTree::SELECT_RULE::NON, WarkerJumpAttackJudge::GetInstance(), WarkerJumpAttackAction::GetInstance());

		}
		aiTreeData.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, WarkerMoveJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Move", "GoToPlayer", 2, BehaviorTree::SELECT_RULE::NON, GotoPlayerJudge::GetInstance(), GotoPlayerAction::GetInstance());
			aiTreeData.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, TurnJudge::GetInstance(), TurnAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
		{
			aiTreeData.AddNode("Wait", "Wandering", 2, BehaviorTree::SELECT_RULE::NON, WarkerWanderingJudge::GetInstance(), WarkerWanderingAction::GetInstance());
			aiTreeData.AddNode("Wait", "Stay", 1, BehaviorTree::SELECT_RULE::NON, NULL, WarkerStayAction::GetInstance());
		}
	}
	/*velocity = 3.0f;*/

	modelData->SetScale(DirectX::XMFLOAT3(2, 2, 2));
	SetBehaviorTree(aiTreeData);
	wanderingRct = 0;
	wanderingRctMax = 180;
	velocity = 5;
	randAng = 0;
	stWandering = 0;
	wanderingCnt = 0;
	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(60, 180, 60));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(20, 20, 20));
	state = WARKER_STATE::WAIT;
}

void WarkerKokim::Add()
{

	SetBehaviorTree(aiTreeData);
	wanderingRct = 0;
	wanderingRctMax = 180;
	velocity = 5;
	randAng = 0;
	stWandering = 0;
	wanderingCnt = 0;
	state = WARKER_STATE::WAIT;
}

void WarkerKokim::Update()
{

	atAnimFrame = pWarkerAttack->GetAnimationFrame();

	if (!nowAsphyxia)
	{
		OBJ3D& pTrs = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData();

		
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


		if (state == WARKER_STATE::JUMP_ATTACK)
		{
			modelData->SetPos(
				DirectX::XMFLOAT3(
					modelData->GetPos().x + atJumpVec.x*3,
					modelData->GetPos().y,
					modelData->GetPos().z + atJumpVec.z * 3));
		}
		else
		{
			nowJumpAttack = false;
		}

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
		/*state = WARKER_STATE::TPOSE;*/

		modelData->SetPosY(110);
	}

	
}
