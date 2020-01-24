#include <FrameWork.h>
#include <string>

#include "SceneTitle.h"
#include "Collision.h"
#include "CollisionJudge.h"
#include "Blender.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "UiSystem.h"
#include "ParticleSystem.h"
#include "Editer.h"
#include "CameraSystem.h"
#include "SoundLoader.h"
#include "Ranking.h"

void SceneTitle::Init()
{
	titleBgSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/title.png", 1);
	titleBgSprData.texPos = { 0.0f, 0.0f };
	titleBgSprData.size = { 1920.0f, 1080.0f };

	startSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/title_tex.png", 1);
	startSprData.texPos = { 0, 0 };
	startSprData.size = { 890, 470 };

	textSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text.png", 1);
	textSprData.texPos = { 0, 0 };
	textSprData.size = { 735, 110 };

	AllSoundStop();
	AllBgmSoundStop();
	PlaySoundMem(SoundLoader::GetInstance()->title.get());
	/*nowLoading = std::make_unique<Sprite>(L"Data/Assets/Texture/text03.png");

	nowLoadingData.pos = DirectX::XMFLOAT2(0.0f, 0.0f);
	nowLoadingData.size = DirectX::XMFLOAT2(0.0f, 0.0f);
	nowLoadingData.texPos = DirectX::XMFLOAT2(0.0f, 0.0f);

	for (int i = 0; i < 3; i++)
	{
		dotData[i].pos = DirectX::XMFLOAT2(0.0f, 0.0f);
		dotData[i].size = DirectX::XMFLOAT2(0.0f, 0.0f);
		dotData[i].texPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	}*/
}

void SceneTitle::Update()
{
	if (Fade::GetInstance()->loading) return;

	

	if (xInput[0].bAt || xInput[0].bBt || xInput[0].bXt || xInput[0].bYt)
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->loading = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}
	addSize = (sinf(cnt / 15.0f)) / 4.0f + 1.0f;
	cnt++;

}

void SceneTitle::Render()
{
	//nowLoading->Draw(nowLoadingData.pos, nowLoadingData.size, nowLoadingData.texPos, nowLoadingData.size, 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	titleBgSpr->Begin();
	titleBgSpr->Draw({ 0, 0 }, { 1920, 1080 }, titleBgSprData.texPos, titleBgSprData.size, 0, { 1, 1, 1, 1 });
	titleBgSpr->End();

	startSpr->Begin();
	startSpr->Draw({ 1920 / 2.0f + 10 , 64 }, { 890, 470 }, startSprData.texPos, startSprData.size, 0, { 1, 1, 1, 1 });
	startSpr->End();

	textSpr->Begin();
	textSpr->Draw({ 1920 / 2.0f + 130, 860 + (addSize * 30) }, { 735, 110 }, textSprData.texPos, textSprData.size, 0, { 1, 1, 1, 1 });
	textSpr->End();
}

void SceneTitle::ImGui()
{
	//CharacterSystem::GetInstance()->GetPlayerAddress()->ImGui();

	//ImGui::Begin("tex");

	//ImGui::DragFloat2("pos", &nowLoadingData.pos.x, 0.1f);
	//ImGui::DragFloat2("texPos", &nowLoadingData.texPos.x, 0.1f);
	//ImGui::DragFloat2("size", &nowLoadingData.size.x, 0.1f);

	//ImGui::DragFloat2(" pos", &dotData[0].pos.x, 0.1f);
	//ImGui::DragFloat2(" texPos", &dotData[0].texPos.x, 0.1f);
	//ImGui::DragFloat2(" size", &dotData[0].size.x, 0.1f);


	//ImGui::End();
}

void SceneTitle::UnInit() {}