#pragma once

#include "ExecJudgementBase.h"
#include "EliteWarkerGoToPlayer.h"

class AI;

class EliteWarkerMoveJudge :
	public ExecJudgementBase
{
public:
	static EliteWarkerMoveJudge *GetInstance()
	{
		static EliteWarkerMoveJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};


