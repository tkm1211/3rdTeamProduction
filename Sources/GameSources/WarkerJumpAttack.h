#pragma once

#include "ExecJudgementBase.h"
#include "ActionBase.h"

class AI;

class WarkerJumpAttackJudge :
	public ExecJudgementBase
{
public:
	static WarkerJumpAttackJudge *GetInstance()
	{
		static WarkerJumpAttackJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class WarkerJumpAttackAction :
	public ActionBase
{
public:
	static WarkerJumpAttackAction *GetInstance()
	{
		static WarkerJumpAttackAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
