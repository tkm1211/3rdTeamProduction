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



class GameClear
{
private:


	std::unique_ptr<SpriteBatch> gameClearSpr;
	std::unique_ptr<SpriteBatch> textSpr;

public:
	GameClear() {}
	~GameClear() {}

	void Init();
	void Update(std::vector<int> num, int timer, int frame[]);
	void Draw();
};