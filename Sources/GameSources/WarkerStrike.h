#pragma once


#include "ExecJudgementBase.h"
#include "ActionBase.h"


class AI;

class WarkerStrikeJudge :
	public ExecJudgementBase
{
public:
	static WarkerStrikeJudge *GetInstance()
	{
		static WarkerStrikeJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class WarkerStrikeAction :
	public ActionBase
{
public:
	static WarkerStrikeAction *GetInstance()
	{
		static WarkerStrikeAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
