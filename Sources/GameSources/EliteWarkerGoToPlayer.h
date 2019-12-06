#pragma once
#define VELOCITY_ELITE_WARKER 10

#include "ExecJudgementBase.h"
#include "ActionBase.h"


class AI;

class EliteWarkerGotoPlayerJudge :
	public ExecJudgementBase
{
public:
	static EliteWarkerGotoPlayerJudge *GetInstance()
	{
		static EliteWarkerGotoPlayerJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class EliteWarkerGotoPlayerAction :
	public ActionBase
{
public:
	static EliteWarkerGotoPlayerAction *GetInstance()
	{
		static EliteWarkerGotoPlayerAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
