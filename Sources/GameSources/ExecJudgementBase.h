#ifndef EXEC_JUDGMENT_BASE_H_
#define EXEC_JUDGMENT_BASE_H_


class AI;
// ���s����
class ExecJudgementBase
{
public:
	virtual bool Judgement(AI *obj) = 0;
};

#endif
