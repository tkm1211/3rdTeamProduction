#include <FrameWork.h>

#include "SceneResult.h"


void SceneResult::Init()
{

}

void SceneResult::Update()
{
	// TODO : ���U���g����
	{
		// TODO : �^�C�g���֏���

		// TODO : ���X�^�[�g����

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