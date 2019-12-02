#pragma once
#include <memory>
#include <vector>
#include "ArcherKokim.h"
#include "WarkerKokim.h"

class _Player
{
public:
	DirectX::XMFLOAT3 pos = { 0,0,0 };
	DirectX::XMFLOAT4 rotate = {};
	DirectX::XMFLOAT3 scale = { 1,1,1 };

};




class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager() {};

	void Update();
	void Draw();

	void ImGui();

	static EnemyManager* GetInstance()
	{
		static EnemyManager instance;
		return &instance;
	}
private:
	std::unique_ptr<Model> pArcher;
	std::unique_ptr<Model> pWarker;
	std::unique_ptr<Model> pPlayer;


	std::vector<ArcherKokim> archer;
	std::vector<WarkerKokim> warker;
};

