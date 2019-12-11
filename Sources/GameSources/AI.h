#pragma once
#include "BehaviorData.h"
class BehaviorTree;
class NodeBase;
class OBJ3D;
class AI
{
public:
	AI();
	virtual ~AI() {};

	virtual void Update();

	virtual void SetEtoPdis(float hEtoPdis) { EtoPdis = hEtoPdis; };
	virtual void SetBehaviorTree(BehaviorTree *hAiTree) { aiTree=hAiTree; };
	virtual float GetEtoPdis() { return EtoPdis; };
private:
	float EtoPdis=0;

	BehaviorTree * aiTree;
	BehaviorData behaviorData;	// ビヘイビアデータ
	NodeBase	 * activeNode=nullptr;		// 実行中ノード
};