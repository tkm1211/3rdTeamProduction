#pragma once

#include "AI.h"
#include "Kokim.h"

#include "Shot.h"


#define RECAST_MAX 300

enum class ARCHER_STATE
{
	WAIT,
	RUN,
	STRIKE,
	TPOSE
};

class Shot;
class ArcherKokim :
	 public AI, public Kokim
{
public:

	int atDis = 500;
	int findPdis = 1000;
	int damageRecast = 0;
	int recastMax=100;
	int attackPoint;

	bool nowAsphyxia = false;

	ARCHER_STATE state;

	std::shared_ptr<Shot> arrow;
	std::shared_ptr<Model> pArcher;
	std::shared_ptr<Model> pArcherAttack;
	std::shared_ptr<Model> pArcherRun;
	std::shared_ptr<Model> pArcherStay;

	std::shared_ptr<Model> pShot;

	ArcherKokim() {};
	ArcherKokim(int num);
	virtual ~ArcherKokim() {};

	void Init();

	void Add();

	void Update();



	
	bool GetNowShot() { return nowShot; };
	int	 GetRecast() { return recast; };
	float GetPlayerDot() { return plDot; };
		
	void SetRecast(int hRecast) { recast = hRecast; };

	void SetAttackDistance(int attackDis) { this->atDis = attackDis; };
	void SetFindPlayerDistance(int findPdis) { this->findPdis = findPdis; };
	void SetState(ARCHER_STATE state) { this->state = state; };
	void SetRecastMax(int recast) { recastMax = recast; };
	void SetAttackPoint(int a) { attackPoint = a; };
	void ChangeNowAsphyxia() { nowAsphyxia ^= 1; };

	void CreateArrow(DirectX::XMFLOAT3 pPos, DirectX::XMFLOAT3 ePos) { arrow = std::make_unique<Shot>(pPos, ePos); };

private:
	
	bool nowShot=false;
	int recast = NULL;
	float plDot;

public:
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			cereal::make_nvp("modelData", modelData),
			cereal::make_nvp("index", index));
	}
};

