#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"

class GameTimer
{
private:
	std::unique_ptr<SpriteBatch> numSpr;
	TexData frameSprData[2];

	int maxNum;


	bool countStop;


public:
	std::vector<int> timeNum;
	int frameNum[2];
	int timer;

	GameTimer() {}
	~GameTimer() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();
};