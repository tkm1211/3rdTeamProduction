#include <FrameWork.h>

#include "SceneGameOver.h"
#include "SceneResult.h"

void SceneGameOver::Init()
{

}

void SceneGameOver::Update()
{
	// TODO : ゲームオーバー処理
	{
		// TODO : リザルトへ処理

	}
}

void SceneGameOver::Render()
{

}

void SceneGameOver::ImGui()
{
	ImGui::Begin("GameOver");

	if (ImGui::Button("Result"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneResult());
	}

	ImGui::End();
}

void SceneGameOver::UnInit() {}