#pragma once
#include <memory>
#include <vector>
#include "ArcherKokim.h"
#include "WarkerKokim.h"
#include "EliteWarkerKokim.h"

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

	std::vector<bool> nowCatch;

	void Update();
	void Draw();

	void ImGui();

	std::vector<std::shared_ptr<OBJ3D>> GetEnemyList()
	{
		return enmList;
	}

	static EnemyManager* GetInstance()
	{
		static EnemyManager instance;
		return &instance;
	}
private:
	std::unique_ptr<Model> pArcher;
	std::unique_ptr<Model> pWarker;
	std::unique_ptr<Model> pEliteWarker;
	std::unique_ptr<Model> pPlayer;
	std::unique_ptr<Model> pShot;


	std::vector<ArcherKokim> archer;
	std::vector<WarkerKokim> warker;
	std::vector<EliteWarkerKokim> eliteWarker;

	std::vector<std::shared_ptr<OBJ3D>> enmList;
	

};

