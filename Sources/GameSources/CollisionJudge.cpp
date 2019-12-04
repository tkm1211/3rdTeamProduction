#include "CollisionJudge.h"
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