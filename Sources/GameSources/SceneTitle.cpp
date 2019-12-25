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
#include "ParticleSystem.h"
#include "Editer.h"
#include "CameraSystem.h"
#include "SoundLoader.h"


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

	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();

}

void SceneTitle::Update()
{
	CharacterSystem::GetInstance()->Update();
	ObjectSystem::GetInstance()->Update();

	CameraSystem::GetInstance()->mainView.SetTarget(DirectX::XMFLOAT3(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().x,
		CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().y + 60.0f,
		CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos().z
	));

	ParticleSystem::GetInstance()->Update();


	if (GetKeyState('/') < 0/* || xInput[0].bAt*/)
	{
		if (!Fade::GetInstance()->onFadeFlg)
		{
			Fade::GetInstance()->onFadeFlg = true;
			Fade::GetInstance()->SetNextScene(new SceneGame());
			//SetScene(new SceneLabo(), false);
		}
	}

}

void SceneTitle::Render()
{
	CharacterSystem::GetInstance()->Draw();
	ObjectSystem::GetInstance()->Draw();
	ParticleSystem::GetInstance()->Draw();

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