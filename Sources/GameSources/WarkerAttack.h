#pragma once

#include "ActionBase.h"

class AI;
class WarkerAttackJudge;


class WarkerAttackJudge
{
public:
	static WarkerAttackJudge *GetInstance()
	{
		static WarkerAttackJudge instance;
		return &instance;
	}

	virtual ActionBase::STATE Update(AI *obj);
};