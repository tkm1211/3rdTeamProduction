#pragma once
#include "Model.h"
#include <memory>
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

	std::shared_ptr<Model> pWarkerAttack;

	virtual bool Judgement(AI *obj);
};

