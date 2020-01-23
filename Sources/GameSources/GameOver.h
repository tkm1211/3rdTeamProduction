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

class GameOver
{
private:
	std::unique_ptr<SpriteBatch> gameOverSpr;

public:
	GameOver() {}
	~GameOver() {}

	void Init();
	void Update();
	void Draw();
};