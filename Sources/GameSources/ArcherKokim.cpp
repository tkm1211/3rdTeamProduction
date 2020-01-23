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
	{
		pArcher = std::make_shared<Model>("Data/Assets/Model/Enemys/Archer.fbx", false);
		pArcherAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/ArcherAttack.fbx", false);
		pArcherRun = std::make_shared<Model>("Data/Assets/Model/Enemys/ArcherRun.fbx", false);
		pArcherStay = std::make_shared<Model>("Data/Assets/Model/Enemys/ArcherStay.fbx", false);

		pShot = std::make_shared<Model>("Data/Assets/Model/Enemys/Arrow.fbx", false);
	}
	modelData = std::make_shared<OBJ3D>();
	


	aiTreeData.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTreeData.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, ArcherAttackJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Attack", "ArcherShot", 1, BehaviorTree::SELECT_RULE::NON, ArcherShotJudge::GetInstance(), ArcherShotAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, ArcherMoveJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, ArcherTurnJudge::GetInstance(), ArcherTurnAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, ArcherWaitJudge::GetInstance(), NULL);
	}

	SetBehaviorTree(aiTreeData);
	state = ARCHER_STATE::WAIT;

	bodyCol= std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(10, 10, 10));


	index = num;
}

void ArcherKokim::Init()
{
	{
		pArcher = std::make_shared<Model>("Data/Assets/Model/Enemys/Archer.fbx", false);
		pArcherAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/ArcherAttack.fbx", false);
		pArcherRun = std::make_shared<Model>("Data/Assets/Model/Enemys/ArcherRun.fbx", false);
		pArcherStay = std::make_shared<Model>("Data/Assets/Model/Enemys/ArcherStay.fbx", false);

		pShot = std::make_shared<Model>("Data/Assets/Model/Enemys/Arrow.fbx", false);
	}



	aiTreeData.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	{
		aiTreeData.AddNode("Root", "Attack", 3, BehaviorTree::SELECT_RULE::PRIORITY, ArcherAttackJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Attack", "ArcherShot", 1, BehaviorTree::SELECT_RULE::NON, ArcherShotJudge::GetInstance(), ArcherShotAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Move", 2, BehaviorTree::SELECT_RULE::PRIORITY, ArcherMoveJudge::GetInstance(), NULL);
		{
			aiTreeData.AddNode("Move", "Turn", 1, BehaviorTree::SELECT_RULE::NON, ArcherTurnJudge::GetInstance(), ArcherTurnAction::GetInstance());
		}
		aiTreeData.AddNode("Root", "Wait", 1, BehaviorTree::SELECT_RULE::NON, ArcherWaitJudge::GetInstance(), NULL);
	}

	SetBehaviorTree(aiTreeData);
	state = ARCHER_STATE::WAIT;
	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(10, 10, 10));



}

void ArcherKokim::Add()
{


	SetBehaviorTree(aiTreeData);
	state = ARCHER_STATE::WAIT;
	bodyCol = std::make_shared<CollisionPrimitive>(2, false, DirectX::XMFLOAT3(30, 90, 30));
	weaponCol = std::make_shared<CollisionPrimitive>(1, false, DirectX::XMFLOAT3(10, 10, 10));

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
	if (arrow)
	{
		weaponCol->SetPos(arrow->GetModelData().GetPos());
	}
}

