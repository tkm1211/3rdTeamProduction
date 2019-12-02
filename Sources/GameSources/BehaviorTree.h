#ifndef BEHAVIOR_TREE_H_
#define BEHAVIOR_TREE_H_

#include <string>

class ActionBase;
class ExecJudgementBase;
class NodeBase;
class BehaviorData;
class AI;
// ビヘイビアツリー
class BehaviorTree
{
public:
	// 選択ルール
	enum SELECT_RULE
	{
		NON,
		PRIORITY,			// 優先順位
		SEQUENCE,			// シーケンス
		SEQUENTIAL_LOOPING,	// シーケンシャルルーピング
		RANDOM,				// ランダム
		ON_OFF,				// オン・オフ
	};

public:
	BehaviorTree() :
		m_Root(NULL)
	{
	}

	// 実行ノードを推論する
	NodeBase *Inference(AI *obj, BehaviorData *data);

	// シーケンスノードから推論開
	NodeBase *SequenceBack(NodeBase *sequence_node, AI *obj, BehaviorData *data);

	// ノード追加
	void AddNode(std::string search_name, std::string entry_name, int priority, SELECT_RULE select_rule, ExecJudgementBase *judgment, ActionBase *action);

	// ツリー構造を表示
	void PrintTree();

	// 実行
	NodeBase *Update(AI *obj, NodeBase *action_node, BehaviorData *data);
private:
	// ルートノード
	NodeBase *m_Root;
};

#endif
