#include <FrameWork.h>

#include "ScenePause.h"


void ScenePause::Init()
{

}

void ScenePause::Update()
{
	// TODO : �|�[�Y����
	{
		// TODO : �^�C�g���֏���

		// TODO : ���X�^�[�g����

		// TODO : �Q�[���ɖ߂鏈�u
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