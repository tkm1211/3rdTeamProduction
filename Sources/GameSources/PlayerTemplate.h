#pragma once
#include "Model.h"
#include "OBJ3D.h"


class PlayerTemplate
{
private:
	std::unique_ptr<Model> pWait;
	std::unique_ptr<Model> pRun;
	std::unique_ptr<Model> pAttack;
	std::unique_ptr<Model> pItem;

	OBJ3D modelData;
	OBJ3D itemData;

	enum ModelState
	{
		WAIT,
		RUN,
		ATTACK
	};
#if 0
	ModelState modelState;
#else
	int modelState;
#endif

public:
	PlayerTemplate() {}
	~PlayerTemplate() {}

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();
	void ImGui();
};