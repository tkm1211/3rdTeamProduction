#include "GameClear.h"
#include "Blender.h"
#include "Ranking.h"

void GameClear::Init()
{
	gameClearSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text02.png", 2);
	textSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text.png", 2);

}

void GameClear::Update(std::vector<int> num, int timer, int frame[])
{
	if (xInput[0].bAt)
	{
		Ranking::GetInstance()->Sort(num, timer, frame);
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}
}

void GameClear::Draw()
{
	SetBlenderMode(BM_ALPHA);
	gameClearSpr->Begin();
	gameClearSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) , 32 }, { 735.0f * 1.0f, 110.0f * 1.0f }, { 0.0f, 0.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	gameClearSpr->End();

	textSpr->Begin();
	textSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) , 900 }, { 735.0f * 1.0f, 110.0f * 1.0f }, { 0.0f, 110.0f * 3.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	textSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) + 530 , 900 }, { 735.0f * 1.0f, 110.0f * 1.0f }, { 0.0f, 110.0f * 8.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	textSpr->End();

	SetBlenderMode(BM_NONE);
}
