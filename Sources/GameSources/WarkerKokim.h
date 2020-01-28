#pragma once

#include "AI.h"
#include "Kokim.h"


enum class WARKER_STATE
{
	WAIT,
	RUN,
	STRIKE,
	JUMP_ATTACK,
	TPOSE,
	HIDAME
};

enum class  WARKER_ATTACK_STATE
{
	STRIKE,
	JUMP_ATTACK
};

class WarkerKokim:
	 public AI, public Kokim
{
public:
	float velocity=5;
	float randAng;
	int	wanderingRct=0;
	int wanderingRctMax=180;
	int stWandering;
	int wanderingCnt;
	int atAnimFrame;
	int attackPoint;
	bool nowJumpAttack;
	bool hitPl=false;
	int hidameCnt=0;

	DirectX::XMFLOAT3 vec;
	DirectX::XMFLOAT3 atJumpVec;

	WARKER_ATTACK_STATE stAttack;

	bool isAttack;
	bool isJumpAttack;

	WarkerKokim() {};
	WarkerKokim(int num);
	~WarkerKokim() {};

	void Init();

	void Add();

	void Update();

	WARKER_STATE const GetState() const { return state; };
	float GetPlayerDot() { return plDot; };
	int& GetAttackDistance() { return attackDis; };
	int& GetFindPlayerDistance() { return findPdis; };
	int& GetStrikeRecastMax() { return strikeRecastMax; };
	int& GetStrikeRecastCnt() { return strikeRecastCnt; };
	int& GetDamageRecast() { return damageRecast; };
	bool& GetNowAsphyxia() { return nowAsphyxia; };

	void SetPos(DirectX::XMFLOAT3 pos) { this->modelData->SetPos(pos); };
	void SetAttackDistance(int attackDis) { this->attackDis=attackDis; };
	void SetFindPlayerDistance(int findPdis) {this->findPdis=findPdis; };
	void SetState(WARKER_STATE state) {this->state= state; };
	void SetStrikeRecastMax(int recast) { strikeRecastMax = recast; };
	void SetStrikeRecastCnt(int recast) { strikeRecastCnt = recast; };
	void SetDamageRecast(int damageRecast) { this->damageRecast = damageRecast; };
	void SetAttackPoint(int attack) { this->attackPoint = attack; };


	void ChangeNowAsphyxia() { nowAsphyxia ^= 1; };
private:



	WARKER_STATE state = WARKER_STATE::RUN;
	float plDot;
	int attackDis=500;
	int findPdis=1000;
	int strikeRecastMax =80;
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

