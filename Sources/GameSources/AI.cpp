#include "AI.h"
#include "BehaviorData.h"
#include "NodeBase.h"


AI::AI()
{

	activeNode = nullptr;
	behaviorData = new BehaviorData();


}

void AI::Update()
{
	if (activeNode == NULL)
	{
		activeNode = aiTree->Inference(this, behaviorData);
	}

	if (activeNode != NULL)
	{
		activeNode = aiTree->Update(this, activeNode, behaviorData);
	}
}