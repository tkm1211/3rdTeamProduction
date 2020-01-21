#include "GameTimer.h"
#include "Blender.h"

void GameTimer::Init()
{
	numSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/numText.png", 1000);
	frameSprData[0].texPos = { 0, 0 };		//テクスチャの左上
	frameSprData[0].size = { 96, 128 };	//テクスチャの幅、高さ
	frameSprData[1].texPos = { 0, 0 };	//テクスチャの左上
	frameSprData[1].size = { 96, 128 };	//テクスチャの幅、高さ

	maxNum = 0;
	timeNum.push_back(0);
	timer = 0;
	countStop = false;
}

void GameTimer::Update()
{
	if (countStop) return;

	timer++;
	frameNum[0]++;
	if (frameNum[0] > 9)
	{
		frameNum[0] = 0;
		frameNum[1]++;
		if (frameNum[1] > 9)
		{
			frameNum[1] = 0;
			if (maxNum == 0)
			{
				maxNum++;
			}
			timeNum.at(0)++;

			if (timeNum.at(0) > 9)
			{
				timeNum.at(0) = 0;
				if (maxNum == 1)
				{
					timeNum.push_back(0);
					maxNum++;
				}
				timeNum.at(1)++;
				if (timeNum.at(1) > 5)
				{
					timeNum.at(1) = 0;
					if (maxNum == 2)
					{
						timeNum.push_back(0);
						maxNum++;
					}
					timeNum.at(2)++;
					if (timeNum.at(2) > 9)
					{
						timeNum.at(2) = 0;
						if (maxNum == 3)
						{
							timeNum.push_back(0);
							maxNum++;
						}
						timeNum.at(3)++;
						if (timeNum.at(3) > 5)
						{
							countStop = true;
						}
					}
				}
			}

		}
	}
}

void GameTimer::Draw()
{
	SetBlenderMode(BM_ALPHA);
	numSpr->Begin();
	numSpr->Draw({ 1920 - 100 * 1, 32 }, { 96 * 1.0f, 128 * 1.0f }, { frameSprData[0].texPos.x + 96 * frameNum[0], frameSprData[0].texPos.y }, frameSprData[0].size, 0, { 1, 1, 1, 1 });
	numSpr->Draw({ 1920 - 100 * 1.5, 32 }, { 96 * 1.0f, 128 * 1.0f }, { frameSprData[1].texPos.x + 96 * frameNum[1], frameSprData[1].texPos.y }, frameSprData[1].size, 0, { 1, 1, 1, 1 });

	numSpr->Draw({ 1920 - 100 * 2, 32 }, { 96 * 1.0f, 128 * 1.0f }, { frameSprData[1].texPos.x + 96 * 10, frameSprData[1].texPos.y }, frameSprData[1].size, 0, { 1, 1, 1, 1 });

	if(timeNum.size() > 3) numSpr->Draw({ 1920 - 100 * 4, 32 }, { 96 * 1.0f, 128 * 1.0f }, { frameSprData[1].texPos.x + 96 * 10, frameSprData[1].texPos.y }, frameSprData[1].size, 0, { 1, 1, 1, 1 });

		 
	for (int i = 0; i < timeNum.size(); i++)
	{
		numSpr->Draw({ 1920 - (100 * (2.5f + (0.5f * i))), 32 }, { 96 * 1.0f, 128 * 1.0f }, { frameSprData[1].texPos.x + 96 * timeNum.at(i), frameSprData[1].texPos.y }, frameSprData[1].size, 0, { 1, 1, 1, 1 });
	}

	numSpr->End();
	SetBlenderMode(BM_NONE);
}

void GameTimer::UnInit()
{

}