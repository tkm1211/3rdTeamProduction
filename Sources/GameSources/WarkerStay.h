#pragma once
#include "ExecJudgementBase.h"
#include "ActionBase.h"


class AI;

class WarkerStayJudge :
	public ExecJudgementBase
{
public:
	static WarkerStayJudge *GetInstance()
	{
		static WarkerStayJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

class WarkerStayAction :
	public ActionBase
{
public:
	static WarkerStayAction *GetInstance()
	{
		static WarkerStayAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};