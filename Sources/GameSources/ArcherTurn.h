#pragma once
#include "ExecJudgementBase.h"
#include "ActionBase.h"

#define TURN_SPEED 0.02f
class AI;

class ArcherTurnJudge :
	public ExecJudgementBase
{
public:
	static ArcherTurnJudge *GetInstance()
	{
		static ArcherTurnJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class ArcherTurnAction :
	public ActionBase
{
public:
	static ArcherTurnAction *GetInstance()
	{
		static ArcherTurnAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
