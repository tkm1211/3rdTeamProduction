#pragma once
#define VELOCITY_WARKER 10

#include "ExecJudgementBase.h"
#include "ActionBase.h"


class AI;

class GotoPlayerJudge :
	public ExecJudgementBase
{
public:
	static GotoPlayerJudge *GetInstance()
	{
		static GotoPlayerJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class GotoPlayerAction:
	public ActionBase
{
public:
	static GotoPlayerAction *GetInstance()
	{
		static GotoPlayerAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
