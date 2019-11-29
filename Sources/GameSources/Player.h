#pragma once
#include "Model.h"
#include "OBJ3D.h"

class Player
{
private:
	static const int MAX_SPEED = 10;
	enum class ModelState
	{
		T,
		WAIT,
		RUN,
		ATTACK1,
		ATTACK2,
		ATTACK3
	};


	std::unique_ptr<Model> pT			;
	std::unique_ptr<Model> pWait		;
	std::unique_ptr<Model> pRun			;
	std::unique_ptr<Model> pAttack[3]	;

	OBJ3D modelData;

	ModelState motionState;

	DirectX::XMFLOAT2 RightStickVec;

	DirectX::XMFLOAT3 MoveSpeed;

private:

	void SwitchMotion( ModelState state );

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();
	void ImGui() {};

	DirectX::XMFLOAT2 GetLeftStickVector();
	//右スティックの傾いてる角度を取得
	float GetLeftStickAngle();
	OBJ3D GetModelData() { return modelData; }

};