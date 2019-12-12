#pragma once
#include <vector>
#include "OBJ3D.h"
#include <cereal/cereal.hpp>

#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include "EnemyManager.h"
//#include "ArcherKokim.h"
//#include "WarkerKokim.h"
//#include "EliteWarkerKokim.h"

class EditEnemy;
class Wave
{
public:
	Wave();
	~Wave();

	void Update();


	int GetTimer() { return timer; };
	int& GetTimerMax() { return timerMax; };
	int& GetWarkerHpForSet() { return setWarkerHp; };
	int& GetArcherHpForSet() { return setArcherHp; };
	int& GetEliteWarkerHpForSet() { return setEliteWarkerHp; };

	std::vector<WarkerKokim>& GetWarker() { return warker; };
	std::vector<ArcherKokim>& GetArcher() { return archer; };
	std::vector<EliteWarkerKokim>& GetEliteWarker() { return eliteWarker; };

	std::vector<EditEnemy>& GetEnemyList(){return enmList;};

	void SetTimer(int timer) {  this->timer= timer; };
private:
	int timer=0;
	int timerMax = 200;

	int setWarkerHp=0;
	int setArcherHp=0;
	int setEliteWarkerHp=0;



	std::vector<ArcherKokim> archer;
	std::vector<WarkerKokim> warker;
	std::vector<EliteWarkerKokim> eliteWarker;

	std::vector<EditEnemy> enmList;


public:
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			cereal::make_nvp("timerMax", timerMax),
			cereal::make_nvp("archer", archer),
			cereal::make_nvp("warker", warker),
			cereal::make_nvp("eliteWarker", eliteWarker),
			cereal::make_nvp("enmList", enmList));
	}
};