#include <FrameWork.h>

#include "SceneResult.h"


void SceneResult::Init()
{

}

void SceneResult::Update()
{
	// TODO : リザルト処理
	{
		// TODO : タイトルへ処理

		// TODO : リスタート処理

	}
}

void SceneResult::Render()
{

}

void SceneResult::ImGui()
{
	ImGui::Begin("Result");

	if (ImGui::Button("ReStart"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}
	if (ImGui::Button("SceneTitle"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}

	ImGui::End();
}

void SceneResult::UnInit() {}