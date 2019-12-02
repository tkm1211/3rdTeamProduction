#pragma once

#include "ActionBase.h"

class WarkerWaitAction :
	public ActionBase
{
public:
	static WarkerWaitAction *GetInstance()
	{
		static WarkerWaitAction instance;
		return &instance;
	}
	virtual ActionBase::STATE Update(AI *obj);
};
