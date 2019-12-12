#pragma once


class CollisionJudge
{
private:
	static const int MAX_PLAYER_DAMAGE = 10;
	static const int MAX_ENEMY_DAMAGE  = 10;

public:
	// �S�Ă̏Փ˔�����s���֐�
	static void AllJudge();
	
public:
	// Player vs �G���B
	static void PlayerVsEnemies();

	// Player�̍U�� vs �G���B
	static void PlayerAttackVsEnemies();

	// �G���B�̍U�� vs Player
	static void EnemiesAttackVsPlayer();

	// �o�t�G���A vs Player
	static void BuffAreaVsPlayer();

	// Player vs �X�e�[�W
	static void PlayerVsStage();

	// �G���B vs �X�e�[�W
	static void EnemiesVsStage();
};