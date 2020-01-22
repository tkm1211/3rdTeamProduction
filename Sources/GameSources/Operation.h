#pragma once
#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#undef max
#undef min

#include "Scene.h"
#include "Sprite.h"

class Operation
{
private:
	std::unique_ptr<SpriteBatch> operationSpr;
	TexData operationSprData;

public:
	Operation() {}
	~Operation() {}

	void Init();
	void Update();
	void Draw();
};