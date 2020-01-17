#pragma once

#include "ExecJudgementBase.h"
#include "ActionBase.h"


class AI;

class WarkerWanderingJudge :
	public ExecJudgementBase
{
public:
	static WarkerWanderingJudge *GetInstance()
	{
		static WarkerWanderingJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class WarkerWanderingAction :
	public ActionBase
{
public:
	static WarkerWanderingAction *GetInstance()
	{
		static WarkerWanderingAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
