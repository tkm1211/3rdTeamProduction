#include "GameClear.h"
#include "Blender.h"
#include "Ranking.h"

void GameClear::Init()
{
	gameClearSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text02.png", 2);
	textSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text.png", 2);
	backSpr = std::make_unique<Sprite>(L"Data/Assets/Texture/blackFade.png");

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
	backSpr->Draw({ 0, 0 }, { 1920, 1080 }, { 0,0 }, { 1920, 1080 }, 0, { 1, 1, 1, 0.75f });

	gameClearSpr->Begin();
	gameClearSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) , 32 }, { 735.0f * 1.0f, 110.0f * 1.0f }, { 0.0f, 0.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	gameClearSpr->End();

	textSpr->Begin();
	textSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) , 900 }, { 735.0f * 1.0f, 110.0f * 1.0f }, { 0.0f, 110.0f * 3.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	textSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) + 730 , 1000 }, { 735.0f * 0.75f, 110.0f * 0.75f }, { 0.0f, 110.0f * 8.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	textSpr->End();

	SetBlenderMode(BM_NONE);
}
