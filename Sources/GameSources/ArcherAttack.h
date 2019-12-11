#pragma once
#include "ExecJudgementBase.h"


class AI;

class ArcherAttackJudge :
	public ExecJudgementBase
{
public:
	static ArcherAttackJudge *GetInstance()
	{
		static ArcherAttackJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};

