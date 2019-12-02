#include "BehaviorData.h"
#include "NodeBase.h"

void BehaviorData::ResetNodeUsed(std::vector<NodeBase*> *reset_hierachy)
{
	for (auto itr = reset_hierachy->begin(); itr != reset_hierachy->end(); itr++)
	{
		m_UsedNodeMap[(*itr)->GetName()] = false;
	}
}

