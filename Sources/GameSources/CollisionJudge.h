#pragma once


class CollisionJudge
{
private:
	static const int MAX_PLAYER_DAMAGE = 1000;
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

	// 雑魚 vs 雑魚達
	static void EnemyVsEnemies();

	// Player vs ステージ
	static void PlayerVsStage();

	// Camera vs ステージ
	static void CameraVsStage();

	// 雑魚達 vs ステージ
	static void EnemiesVsStage();
};