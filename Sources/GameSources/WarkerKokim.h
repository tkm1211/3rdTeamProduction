#pragma once

#include "AI.h"
#include "Kokim.h"


enum class WARKER_STATE
{
	WAIT,
	RUN,
	STRIKE,
	TPOSE
};

class WarkerKokim:
	 public AI, public Kokim
{
public:
	WarkerKokim() {};
	WarkerKokim(int num);
	~WarkerKokim() {};

	void Init();

	void Update();

	WARKER_STATE const GetState() const { return state; };
	float GetPlayerDot() { return plDot; };
	int& GetAttackDistance() { return attackDis; };
	int& GetFindPlayerDistance() { return findPdis; };
	int& GetStrikeRecastMax() { return strikeRecastMax; };
	int& GetStrikeRecastCnt() { return strikeRecastCnt; };
	int& GetDamageRecast() { return damageRecast; };
	bool& GetNowAsphyxia() { return nowAsphyxia; };

	void SetAttackDistance(int attackDis) { this->attackDis=attackDis; };
	void SetFindPlayerDistance(int findPdis) {this->findPdis=findPdis; };
	void SetState(WARKER_STATE state) {this->state= state; };
	void SetStrikeRecastMax(int recast) { strikeRecastMax = recast; };
	void SetStrikeRecastCnt(int recast) { strikeRecastCnt = recast; };
	void SetDamageRecast(int damageRecast) { this->damageRecast = damageRecast; };


	void ChangeNowAsphyxia() { nowAsphyxia ^= 1; };
private:

	WARKER_STATE state = WARKER_STATE::RUN;
	float plDot;
	int attackDis=50;
	int findPdis=1000;
	int strikeRecastMax = 300;
	int strikeRecastCnt = 0;
	int damageRecast = 0;
	bool nowAsphyxia = false;

public:
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			cereal::make_nvp("attackDis", attackDis),
			cereal::make_nvp("findPdis", findPdis),
			cereal::make_nvp("modelData", modelData),
			cereal::make_nvp("index", index),
			cereal::make_nvp("hp", hp),
			cereal::make_nvp("velocity", velocity));
	}
	
};

