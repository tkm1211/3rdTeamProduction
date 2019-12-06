#pragma once
#include "ExecJudgementBase.h"
#include "ActionBase.h"

#define TURN_SPEED 0.02f
class AI;

class ArcherShotJudge :
	public ExecJudgementBase
{
public:
	static ArcherShotJudge *GetInstance()
	{
		static ArcherShotJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj) override;
};

class ArcherShotAction :
	public ActionBase
{
public:
	static ArcherShotAction *GetInstance()
	{
		static ArcherShotAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
