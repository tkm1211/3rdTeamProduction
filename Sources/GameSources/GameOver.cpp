#include "GameOver.h"
#include "Blender.h"
#include "SoundLoader.h"

void GameOver::Init()
{
	gameOverSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text02.png", 2);
	textSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text.png", 2);
	backSpr = std::make_unique<Sprite>(L"Data/Assets/Texture/blackFade.png");

	isSound = false;
}

void GameOver::Update()
{
	if (!isSound)
	{
		AllSoundStop();
		AllBgmSoundStop();
		PlaySoundMem(SoundLoader::GetInstance()->over.get());
		isSound = true;
	}

	if (xInput[0].bAt)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}
}

void GameOver::Draw()
{
	SetBlenderMode(BM_ALPHA);
	backSpr->Draw({ 0, 0 }, { 1920, 1080 }, { 0,0 }, { 1920, 1080 }, 0, { 1, 1, 1, 0.75f });

	gameOverSpr->Begin();
	gameOverSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) , 32 }, { 735.0f * 1.0f, 110.0f * 0.0f }, { 0.0f, 0.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	gameOverSpr->End();

	textSpr->Begin();
	textSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) , 900 }, { 735.0f * 1.0f, 110.0f * 1.0f }, { 0.0f, 110.0f * 3.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	textSpr->Draw({ (1920 / 2 - (735.0f / 2.0f)) + 730 , 1000 }, { 735.0f * 0.75f, 110.0f * 0.75f }, { 0.0f, 110.0f * 8.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	textSpr->End();

	SetBlenderMode(BM_NONE);
}
