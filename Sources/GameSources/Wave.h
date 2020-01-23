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
	bool _isFinish = false;

	int setWarkerAttackPoint = 1000;
	int setArcherAttackPoint = 1000;
	

	Wave();
	~Wave();

	void Update();


	int GetTimer() { return timer; };
	int& GetTimerMax() { return timerMax; };
	int& GetWarkerHpForSet() { return setWarkerHp; };
	int& GetArcherHpForSet() { return setArcherHp; };
	int& GetEliteWarkerHpForSet() { return setEliteWarkerHp; };

	int& GetWarkerAttackDistanceForSet() { return setWarkerAttackDis; };
	int& GetArcherAttackDistanceForSet() { return setArcherAttackDis; };
	int& GetEliteWarkerAttackDistanceForSet() { return setEliteWarkerAttackDis; };

	int& GetWarkerFindPlayerDistanceForSet() { return setWarkerFindPlayerDistance; };
	int& GetArcherFindPlayerDistanceForSet() { return setArcherFindPlayerDistance; };
	int& GetEliteWarkerFindPlayerDistanceForSet() { return setEliteWarkerFindPlayerDistance; };

	int& GetWarkerStrikeRecastMaxForSet() { return setWarkerStrikeRecastMax; };
	int& GetArcherStrikeRecastMaxForSet() { return setArcherStrikeRecastMax; };

	float& GetWarkerVelocityForSet() { return setWarkerVelocity; };
	float& GetArcherVelocityForSet() { return setArcherVelocity; };
	float& GetEliteWarkerVelocityForSet() { return setEliteWarkerVelocity; };

	std::vector<WarkerKokim>& GetWarker() { return warker; };
	std::vector<ArcherKokim>& GetArcher() { return archer; };
	std::vector<EliteWarkerKokim>& GetEliteWarker() { return eliteWarker; };

	std::vector<EditEnemy>& GetEnemyList(){return enmList;};

	void SetTimer(int timer) {  this->timer= timer; };
private:

	int timer=0;
	int timerMax = 200;

	int setWarkerHp=10;
	int setArcherHp=10;
	int setEliteWarkerHp=10;

	int setWarkerAttackDis = 50;
	int setArcherAttackDis = 50;
	int setEliteWarkerAttackDis = 50;

	int setWarkerFindPlayerDistance = 1000;
	int setArcherFindPlayerDistance = 1000;
	int setEliteWarkerFindPlayerDistance = 1000;

	int setWarkerStrikeRecastMax = 120;
	int setArcherStrikeRecastMax = 120;

	float setWarkerVelocity = 10;
	float setArcherVelocity = 10;
	float setEliteWarkerVelocity = 10;



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
			cereal::make_nvp("enmList", enmList),
			cereal::make_nvp("setWarkerHp", setWarkerHp),
			cereal::make_nvp("setArcherHp", setArcherHp),
			cereal::make_nvp("setWarkerAttackDis", setWarkerAttackDis),
			cereal::make_nvp("setArcherAttackDis", setArcherAttackDis),
			cereal::make_nvp("setWarkerFindPlayerDistance", setWarkerFindPlayerDistance),
			cereal::make_nvp("setArcherFindPlayerDistance", setArcherFindPlayerDistance),
			cereal::make_nvp("setWarkerStrikeRecastMax", setWarkerStrikeRecastMax),
			cereal::make_nvp("setWarkerVelocity", setWarkerVelocity),
			cereal::make_nvp("setArcherVelocity", setArcherVelocity));
	}
};