#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Collision.h"

#include "BuffArea.h"
#include "BG.h"
#include "Billboard.h"
#include "Sprite.h"
#include "WaveTex.h"
#include "GameTimer.h"
#include "GameOver.h"
#include "GameClear.h"

class SceneGame : public Scene
{
private:
	WaveTex waveTex;
	std::unique_ptr<GameTimer> gameTimer;
	std::unique_ptr<GameOver> gameOver;
	std::unique_ptr<GameClear> gameClear;
	std::unique_ptr<Sprite> back;

	bool isWave;

	/*std::unique_ptr<Sprite> nowLoading;


	TexData nowLoadingData;
	TexData dotData[3];

	int cnt;
	int state;

private:
	std::unique_ptr<std::thread> loadingThread;
	std::mutex loadingMutex;
	bool IsNowLoading()
	{
		if (loadingThread && loadingMutex.try_lock())
		{
			loadingMutex.unlock();
			return false;
		}
		return true;
	}*/

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};
