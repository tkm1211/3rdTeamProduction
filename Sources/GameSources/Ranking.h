#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"


class Ranking
{
private:
	struct RankingInfo
	{
		int frameNum[2];
		std::vector<int> timeNum;
		int gameTimer;

		void Clear() { gameTimer = 0; timeNum.resize(0); frameNum[0] = 0; frameNum[1] = 0; }
		RankingInfo() {}
		~RankingInfo() {}

		RankingInfo(const RankingInfo& o)
		{
			frameNum[0] = o.frameNum[0];
			frameNum[1] = o.frameNum[1];
			gameTimer = o.gameTimer;

			timeNum.resize(o.timeNum.size());

			for (size_t i = 0; i < timeNum.size(); i++)
			{
				timeNum.at(i) = o.timeNum.at(i);
			}

		}

	};
	
	RankingInfo info[5];
	std::unique_ptr<SpriteBatch> numSpr;
	std::unique_ptr<SpriteBatch> texSpr;

public:
	Ranking() {}
	~Ranking() {}

	void Init();
	void Update();
	void Draw();

	void Sort(std::vector<int> num, int timer, int frame[]);

	void Load();
	void Save();


	static Ranking* GetInstance()
	{
		static Ranking instance;
		return &instance;
	}

};