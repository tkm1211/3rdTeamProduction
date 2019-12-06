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

	virtual void SetObj(OBJ3D* hObj) { obj = hObj; };
	virtual void SetEtoPdis(float hEtoPdis) { EtoPdis = hEtoPdis; };
	virtual void SetBehaviorTree(BehaviorTree *hAiTree) { aiTree=hAiTree; };
	virtual OBJ3D* GetObj() { return obj; };
	virtual float GetEtoPdis() { return EtoPdis; };
private:
	float EtoPdis=0;

	OBJ3D *obj;

	BehaviorTree * aiTree;
	BehaviorData behaviorData;	// �r�w�C�r�A�f�[�^
	NodeBase	 * activeNode=nullptr;		// ���s���m�[�h
};