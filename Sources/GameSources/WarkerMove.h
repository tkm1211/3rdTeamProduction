#pragma once
#include "ExecJudgementBase.h"

class AI;

class WarkerMoveJudge: 
	public ExecJudgementBase
{
public:
	static WarkerMoveJudge *GetInstance()
	{
		static WarkerMoveJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};


