#pragma once


class CollisionJudge
{
private:
	static const int MAX_PLAYER_DAMAGE = 10;
	static const int MAX_ENEMY_DAMAGE  = 10;

public:
	// 全ての衝突判定を行う関数
	static void AllJudge();
	
public:
	// Player vs 雑魚達
	static void PlayerVsEnemies();

	// Playerの攻撃 vs 雑魚達
	static void PlayerAttackVsEnemies();

	// 雑魚達の攻撃 vs Player
	static void EnemiesAttackVsPlayer();

	// バフエリア vs Player
	static void BuffAreaVsPlayer();

	// Player vs ステージ
	static void PlayerVsStage();

	// 雑魚達 vs ステージ
	static void EnemiesVsStage();
};