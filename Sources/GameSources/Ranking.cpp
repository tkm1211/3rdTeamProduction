#include "Ranking.h"
#include <fstream>
#include <string>
#include "Blender.h"

void Ranking::Init()
{
	numSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/numText.png", 1000);

	for (int i = 0; i < 5; i++)
	{
		info[i].Clear();
	}
	Load();
}

void Ranking::Update()
{

}

void Ranking::Draw()
{
	SetBlenderMode(BM_ALPHA);
	numSpr->Begin();
	for (int i = 0; i < 5; i++)
	{
		float posY = 128.0f * i;

		numSpr->Draw({ 1920.0f - 100.0f * 1.0f,    32.0f + posY }, { 96 * 1.0f, 128 * 1.0f }, { 0.0f + 96 * info[i].frameNum[0], 0.0f }, {96.0f, 128.0f}, 0, { 1, 1, 1, 1 });
		numSpr->Draw({ 1920.0f - 100.0f * 1.5f,    32.0f + posY }, { 96 * 1.0f, 128 * 1.0f }, { 0.0f + 96 * info[i].frameNum[1], 0.0f }, {96.0f, 128.0f}, 0, { 1, 1, 1, 1 });
		numSpr->Draw({ 1920.0f - 100.0f * 2.0f,    32.0f + posY }, { 96 * 1.0f, 128 * 1.0f }, { 0.0f + 96 * 10                          , 0.0f }, {96.0f, 128.0f}, 0, { 1, 1, 1, 1 });
		for (int j = 0; j < info[i].timeNum.size(); j++)
		{
			numSpr->Draw({ 1920 - (100 * (2.5f + (0.5f * j))), 32 + (128.0f * i) }, { 96.0f * 1.0f, 128.0f * 1.0f }, { 0.0f + 96 * info[i].timeNum.at(j), 0.0f }, {96.0f, 128.0f}, 0, { 1, 1, 1, 1 });
		}
	}
	numSpr->End();

}

void Ranking::Sort(std::vector<int> num, int timer, int frame[2])
{
	RankingInfo tmp[6] = {};
	for (int i = 0; i < 5; i++)
	{
		tmp[i].gameTimer = info[i].gameTimer; 
		tmp[i].frameNum[0] = info[i].frameNum[0];
		tmp[i].frameNum[1] = info[i].frameNum[1];

		tmp[i].timeNum.resize(info[i].timeNum.size());
		for (size_t j = 0; j < tmp[i].timeNum.size(); j++)
		{
			tmp[i].timeNum.at(j) = info[i].timeNum.at(j);
		}
	}

	tmp[5].gameTimer = timer;
	tmp[5].frameNum[0] = frame[0];
	tmp[5].frameNum[1] = frame[1];
	tmp[5].timeNum.resize(num.size());
	for (size_t j = 0; j < tmp[5].timeNum.size(); j++)
	{
		tmp[5].timeNum.at(j) = num.at(j);
	}

	/* 数値を昇順にソート */
	for (int i = 0; i < 6; ++i) 
	{
		for (int j = i + 1; j < 6; ++j) 
		{
			if (tmp[i].gameTimer > tmp[j].gameTimer)
			{
				RankingInfo _tmp;
				_tmp = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = _tmp;
			}
			if (tmp[i].gameTimer == 0  && tmp[j].gameTimer != 0)
			{
				RankingInfo _tmp;
				_tmp = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = _tmp;
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		info[i] = tmp[i];
	}

	Save();

}

void Ranking::Load()
{
	FILE* fp;

	char Filename1[] = "./Data/Document/Ranking.txt";

	if ((fp = fopen(Filename1, "r")) == NULL)
	{
		return;
	}
	for (int j = 0; j < 5; j++)
	{
		fscanf(fp, "%d", &info[j].gameTimer);
		fscanf(fp, "%d", &info[j].frameNum[0]);
		fscanf(fp, "%d", &info[j].frameNum[1]);
		int size = 0;
		fscanf(fp, "%d", &size);
		info[j].timeNum.resize(size);

		for (size_t i = 0; i < info[j].timeNum.size(); i++)
		{
			fscanf(fp, "%d", &info[j].timeNum.at(i));
		}
	}
	fclose(fp);
}

void Ranking::Save()
{
	FILE* fp;

	char Filename1[] = "./Data/Document/Ranking.txt";
	fp = fopen(Filename1, "w");

	for (int j = 0; j < 5; j++)
	{
		fprintf(fp, "%d ", info[j].gameTimer);
		fprintf(fp, "\n");
		fprintf(fp, "%d ", info[j].frameNum[0]);
		fprintf(fp, "\n");
		fprintf(fp, "%d ", info[j].frameNum[1]);
		fprintf(fp, "\n");
		fprintf(fp, "%d ", info[j].timeNum.size());
		fprintf(fp, "\n");
		for (size_t i = 0; i < info[j].timeNum.size(); i++)
		{
			fprintf(fp, "%d ", info[j].timeNum.at(i));
			fprintf(fp, "\n");
		}
	}
	fclose(fp);

}