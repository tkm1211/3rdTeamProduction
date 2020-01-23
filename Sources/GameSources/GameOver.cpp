#include "GameOver.h"
#include "Blender.h"

void GameOver::Init()
{
	gameOverSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text02.png", 2);

}

void GameOver::Update()
{

}

void GameOver::Draw()
{
	SetBlenderMode(BM_ALPHA);
	gameOverSpr->Begin();
	gameOverSpr->Draw({ (1920 / 2 - 367) , 32 }, { 735.0f * 1.0f, 110.0f * 0.0f }, { 0.0f, 0.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	gameOverSpr->Draw({ (1920 / 2 - 367) , 32 }, { 735.0f * 1.0f, 110.0f * 0.0f }, { 0.0f, 110.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	gameOverSpr->End();
	SetBlenderMode(BM_NONE);
}
