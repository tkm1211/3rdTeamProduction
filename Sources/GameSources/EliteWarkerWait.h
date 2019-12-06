#pragma once
#include "ActionBase.h"
#include <memory>

class EliteWarkerWaitAction :
	public ActionBase
{
public:
	static EliteWarkerWaitAction *GetInstance()
	{
		static std::unique_ptr<EliteWarkerWaitAction> instance;
		return instance.get();
	}
	virtual ActionBase::STATE Update(AI *obj);
};
