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
	BehaviorData behaviorData;	// �r�w�C�r�A�f�[�^
	NodeBase	 * activeNode=nullptr;		// ���s���m�[�h
};