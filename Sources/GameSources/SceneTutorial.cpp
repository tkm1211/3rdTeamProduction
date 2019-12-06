#include <FrameWork.h>

#include "SceneTutorial.h"


void SceneTutorial::Init()
{
	
}

void SceneTutorial::Update()
{
	// TODO : Skip処理
	{
		
	}

	// TODO : チュートリアル処理
	{
		
	}
}

void SceneTutorial::Render()
{

}

void SceneTutorial::ImGui()
{
	ImGui::Begin("Tutorial");

	if (ImGui::Button("Skip"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}
	if (ImGui::Button("Clear GoToGame"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}

	ImGui::End();
}

void SceneTutorial::UnInit() {}