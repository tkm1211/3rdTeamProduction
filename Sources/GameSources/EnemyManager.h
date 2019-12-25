#pragma once
#include <memory>
#include <vector>
#include "ArcherKokim.h"
#include "WarkerKokim.h"
#include "EliteWarkerKokim.h"
#include "Shot.h"
#include "WaveManager.h"

#include <cereal/cereal.hpp>

#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

class WaveManager;
class _Player
{
public:
	DirectX::XMFLOAT3 pos = { 0,0,0 };
	DirectX::XMFLOAT4 rotate = {};
	DirectX::XMFLOAT3 scale = { 1,1,1 };

};

enum class ENEMY_TYPE
{

	WARKER,
	ARCHER,
	ELITE_WARKER
};

class EditEnemy
{
public:
	EditEnemy(){};
	EditEnemy(std::shared_ptr<OBJ3D> modelData, ENEMY_TYPE type,int num):
		nowCatch(false), modelData(modelData),type(type), index(num)
	{
		
	};
	
	~EditEnemy() {};

	std::shared_ptr<OBJ3D> modelData;
	ENEMY_TYPE type;
	int index;
	bool nowCatch;

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			cereal::make_nvp("modelData", modelData),
			cereal::make_nvp("index", index),
			cereal::make_nvp("type", (int)type));
	}
};

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	WaveManager* GetWaveManager() { return waveMgr.get(); };
	std::vector<bool> nowCatch;

	void Update();
	void Draw();

	void WarkerRenderer();
	void AllDelete();


	void ImGui();

private:
	std::shared_ptr<Model> pArcher;
	std::shared_ptr<Model> pWarker;
	std::shared_ptr<Model> pWarkerRun;
	std::shared_ptr<Model> pWarkerAttack;
	std::shared_ptr<Model> pWarkerWait;
		
	std::shared_ptr<Model> pEliteWarker;
	std::shared_ptr<Model> pPlayer;
	std::shared_ptr<Model> pShot;

	std::unique_ptr<WaveManager> waveMgr;

	int enmNum = NULL;

	DirectX::XMFLOAT3 vPoswa = {-8,0,0};


	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(waveMgr);
	}
};

