#pragma once
#include "ExecJudgementBase.h"
#include "ActionBase.h"


class AI;

class TurnJudge :
	public ExecJudgementBase
{
public:
	static TurnJudge *GetInstance()
	{
		static TurnJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class TurnAction :
	public ActionBase
{
public:
	static TurnAction *GetInstance()
	{
		static TurnAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
