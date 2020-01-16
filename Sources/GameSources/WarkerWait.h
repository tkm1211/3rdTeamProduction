#pragma once
#include "ExecJudgementBase.h"

class AI;

class WarkerWaitJudge :
	public ExecJudgementBase
{
public:
	static WarkerWaitJudge *GetInstance()
	{
		static WarkerWaitJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

