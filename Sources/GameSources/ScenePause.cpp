#include <FrameWork.h>

#include "ScenePause.h"


void ScenePause::Init()
{

}

void ScenePause::Update()
{
	// TODO : ポーズ処理
	{
		// TODO : タイトルへ処理

		// TODO : リスタート処理

		// TODO : ゲームに戻る処置
	}
}

void ScenePause::Render()
{

}

void ScenePause::ImGui()
{
	ImGui::Begin("Pause");

	if (ImGui::Button("ReStart"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}
	if (ImGui::Button("Return Game"))
	{
		SceneManager::GetInstance()->ReSetStackScene();
	}
	if (ImGui::Button("Title"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}

	ImGui::End();
}

void ScenePause::UnInit() {}