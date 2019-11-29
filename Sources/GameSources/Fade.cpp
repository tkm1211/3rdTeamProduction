#include "Fade.h"
#include "SceneManager.h"

void Fade::Init()
{
	fade_spr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/Fade/BG_SceneTransition.png");
	fade_spr_data.texPos = { 0, 0 };		//テクスチャの左上
	fade_spr_data.size = { 1920, 1080 };	//テクスチャの幅、高さ
	onFadeFlg = false;
	state = 0;
	alpha = 0;
	scene = nullptr;
}

void Fade::UnInit()
{

}

void Fade::Update()
{
	if (!onFadeFlg) return;

	switch (state)
	{
	case 0:
		alpha = 0;
		state++;
		break;
	case 1:
		alpha += 0.01f;
		if (alpha >= 1.0f)
		{
			alpha = 1.0f;
			state++;
		}
		break;
	case 2:
		if (scene)
		{
			SceneManager::GetInstance()->SetScene(scene, false);
		}
		scene = nullptr;
		state++;
		break;
	case 3:
		alpha -= 0.01f;
		if (alpha <= 0.0f)
		{
			alpha = 0.0f;
			state++;
		}
		break;
	case 4:
		alpha = 0;
		state = 0;
		onFadeFlg = false;
		break;
	}

}

void Fade::Draw()
{
	fade_spr->Begin();
	fade_spr->Draw({ 0, 0 }, { 1920, 1080 }, fade_spr_data.texPos, fade_spr_data.size, 0, {1, 1, 1, alpha});
	fade_spr->End();
}