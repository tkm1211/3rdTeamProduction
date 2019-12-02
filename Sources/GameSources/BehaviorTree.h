#ifndef BEHAVIOR_TREE_H_
#define BEHAVIOR_TREE_H_

#include <string>

class ActionBase;
class ExecJudgementBase;
class NodeBase;
class BehaviorData;
class AI;
// �r�w�C�r�A�c���[
class BehaviorTree
{
public:
	// �I�����[��
	enum SELECT_RULE
	{
		NON,
		PRIORITY,			// �D�揇��
		SEQUENCE,			// �V�[�P���X
		SEQUENTIAL_LOOPING,	// �V�[�P���V�������[�s���O
		RANDOM,				// �����_��
		ON_OFF,				// �I���E�I�t
	};

public:
	BehaviorTree() :
		m_Root(NULL)
	{
	}

	// ���s�m�[�h�𐄘_����
	NodeBase *Inference(AI *obj, BehaviorData *data);

	// �V�[�P���X�m�[�h���琄�_�J
	NodeBase *SequenceBack(NodeBase *sequence_node, AI *obj, BehaviorData *data);

	// �m�[�h�ǉ�
	void AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgementBase *judgment, ActionBase *action);

	// �c���[�\����\��
	void PrintTree();

	// ���s
	NodeBase *Update(AI *obj, NodeBase *action_node, BehaviorData *data);
private:
	// ���[�g�m�[�h
	NodeBase *m_Root;
};

#endif
