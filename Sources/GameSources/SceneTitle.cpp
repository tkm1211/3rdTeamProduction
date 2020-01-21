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
	//PlaySoundMem(SoundLoader::GetInstance()->titleBgm.get());
	//AllSoundStop();
	//titleBgSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/Title_BG.png");
	//titleBgSprData.texPos = { 0, 0 };		//テクスチャの左上
	//titleBgSprData.size = { 1920, 1080 };	//テクスチャの幅、高さ
	//startSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/UI_Title_Start.png");
	//startSprData.texPos = { 0, 0 };		//テクスチャの左上
	//startSprData.size = { 293, 71 };	//テクスチャの幅、高さ

	gameTimer = std::make_unique<GameTimer>();
	gameTimer->Init();

	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();
	UiSystem::GetInstance()->Init();
	Ranking::GetInstance()->Init();
}

void SceneTitle::Update()
{
	CharacterSystem::GetInstance()->Update();
	ObjectSystem::GetInstance()->Update();

	DirectX::XMFLOAT3 playerPos = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos();
	float playerAngle = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetAngle().y;

	CameraSystem::GetInstance()->mainView.SetTarget({ playerPos.x, playerPos.y + 150,   playerPos.z});
	DirectX::XMFLOAT3 l = CameraSystem::GetInstance()->mainView.GetPos();

	ParticleSystem::GetInstance()->Update();
	UiSystem::GetInstance()->Update();

	DirectX::XMFLOAT3 _p = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos();
	float _a = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetAngle().y;
	if (xInput->bDOWNt)
	{
		UiSystem::GetInstance()->GetDamageEffectsTexAddress()->AddToEffects(_p, {0, 0, 0});
	}

	if (GetKeyState (' ') < 0/* || xInput[0].bAt*/)
	{
		if (!Fade::GetInstance()->onFadeFlg)
		{
			Ranking::GetInstance()->Sort(gameTimer->timeNum, gameTimer->timer, gameTimer->frameNum);
			Fade::GetInstance()->onFadeFlg = true;
			Fade::GetInstance()->SetNextScene(new SceneTitle());
			//SetScene(new SceneLabo(), false);
		}
	}
	gameTimer->Update();

}

void SceneTitle::Render()
{
	CharacterSystem::GetInstance()->Draw();
	ObjectSystem::GetInstance()->Draw();
	ParticleSystem::GetInstance()->Draw();
	UiSystem::GetInstance()->Draw();
	gameTimer->Draw();
	//Ranking::GetInstance()->Draw();
	//titleBgSpr->Begin();
	//titleBgSpr->Draw({ 0, 0 }, { 1920, 1080 }, titleBgSprData.texPos, titleBgSprData.size, 0, { 1, 1, 1, 1 });
	//titleBgSpr->End();
	//startSpr->Begin();
	//startSpr->Draw({ 1920 / 2.0f - 293 / 2.0f, 900 }, { 293, 71 }, startSprData.texPos, startSprData.size, 0, { 1, 1, 1, 1 });
	//startSpr->End();
}

void SceneTitle::ImGui()
{
	CharacterSystem::GetInstance()->GetPlayerAddress()->ImGui();
}

void SceneTitle::UnInit() {}