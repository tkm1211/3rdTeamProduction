#include <FrameWork.h>

#include "SceneGameOver.h"
#include "SceneResult.h"

void SceneGameOver::Init()
{

}

void SceneGameOver::Update()
{
	// TODO : �Q�[���I�[�o�[����
	{
		// TODO : ���U���g�֏���

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