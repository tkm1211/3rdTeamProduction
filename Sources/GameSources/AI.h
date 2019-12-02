#pragma once

class BehaviorTree;
class BehaviorData;
class NodeBase;
class OBJ3D;
class AI
{
public:
	AI();
	~AI() {};

	void Update();

	void SetObj(OBJ3D* hObj) { obj = hObj; };
	void SetEtoPdis(float hEtoPdis) { EtoPdis = hEtoPdis; };
	void SetBehaviorTree(BehaviorTree *hAiTree) { aiTree=hAiTree; };
	OBJ3D* GetObj() { return obj; };
	float GetEtoPdis() { return EtoPdis; };
private:
	float EtoPdis=0;

	OBJ3D *obj;

	BehaviorTree * aiTree;
	BehaviorData * behaviorData;	// �r�w�C�r�A�f�[�^
	NodeBase	 * activeNode=nullptr;		// ���s���m�[�h
};