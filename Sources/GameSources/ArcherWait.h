#pragma once
#include "ExecJudgementBase.h"
#include "ActionBase.h"

class AI;

class ArcherWaitJudge :
	public ExecJudgementBase
{
public:
	static ArcherWaitJudge *GetInstance()
	{
		static ArcherWaitJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj) override;
};

class ArcherWaitAction :
	public ActionBase
{
public:
	static ArcherWaitAction *GetInstance()
	{
		static ArcherWaitAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
