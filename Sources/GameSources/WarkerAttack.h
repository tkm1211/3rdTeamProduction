#pragma once

#include "ExecJudgementBase.h"
class AI;


class WarkerAttackJudge:
	public ExecJudgementBase
{
public:
	static WarkerAttackJudge *GetInstance()
	{
		static WarkerAttackJudge instance;
		return &instance;
	}

	virtual bool Judgement(AI *obj);
};

