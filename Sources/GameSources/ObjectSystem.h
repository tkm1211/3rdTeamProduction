#pragma once
#include "BuffArea.h"

class ObjectSystem
{
private:
	std::unique_ptr<BuffArea> buffarea;

public:
	ObjectSystem() {}
	~ObjectSystem() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	BuffArea* GetBuffAreaAddress() { return buffarea.get(); }

	static ObjectSystem* GetInstance()
	{
		static ObjectSystem instance;
		return &instance;
	}

};