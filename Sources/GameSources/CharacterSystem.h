#pragma once
#include "Player.h"

class CharacterSystem
{
private:
	std::unique_ptr<Player> player;
public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	Player* GetPlayerAddress() { return player.get(); }

	static CharacterSystem* GetInstance()
	{
		static CharacterSystem instance;
		return &instance;
	}

};