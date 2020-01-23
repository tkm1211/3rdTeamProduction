#pragma once


class CollisionJudge
{
private:
	static const int MAX_PLAYER_DAMAGE = 1000;
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

	// �G�� vs �G���B
	static void EnemyVsEnemies();

	// Player vs �X�e�[�W
	static void PlayerVsStage();

	// Camera vs �X�e�[�W
	static void CameraVsStage();

	// �G���B vs �X�e�[�W
	static void EnemiesVsStage();
};