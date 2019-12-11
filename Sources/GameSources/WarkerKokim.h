#pragma once

#include "AI.h"
#include "Kokim.h"

class Player;


enum class WARKER_STATE
{
	RUN,
	STRIKE
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

	void SetState(WARKER_STATE state) {this->state= state; };
private:

	WARKER_STATE state = WARKER_STATE::RUN;
	float plDot;
};

