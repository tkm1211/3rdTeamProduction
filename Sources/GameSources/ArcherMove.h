#pragma once


#include "ExecJudgementBase.h"


class AI;

class ArcherMoveJudge :
	public ExecJudgementBase
{
public:
	static ArcherMoveJudge *GetInstance()
	{
		static ArcherMoveJudge instance;
		return &instance;
	}
	virtual bool Judgement(AI *obj);
};
