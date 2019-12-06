#include "CollisionJudge.h"
#include "Collision.h"
#include "CharacterSystem.h"
#include "BG.h"


void CollisionJudge::AllJudge()
{
	PlayerAttackVsEnemies();
	EnemiesAttackVsPlayer();
	BuffAreaVsPlayer();
	PlayerVsStage();
	EnemiesVsStage();
}


void CollisionJudge::PlayerAttackVsEnemies()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	CollisionPrimitive* hitPlayerAttack;
	// hitPlayerAttack = player->GetPlayerAttackAddress();


}

void CollisionJudge::EnemiesAttackVsPlayer()
{

}

void CollisionJudge::BuffAreaVsPlayer()
{

}

void CollisionJudge::PlayerVsStage()
{

}

void CollisionJudge::EnemiesVsStage()
{

}