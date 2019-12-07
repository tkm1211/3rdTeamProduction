#pragma once
#include "Player.h"
#include "EnemyManager.h"
class CharacterSystem
{
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<EnemyManager> enmMgr;
public:
	CharacterSystem() {}
	~CharacterSystem() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	Player* GetPlayerAddress() { return player.get(); }
	EnemyManager* GetEnemyManagerAddress() { return enmMgr.get(); }

	static CharacterSystem* GetInstance()
	{
		static CharacterSystem instance;
		return &instance;
	}

};