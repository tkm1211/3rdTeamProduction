#pragma once

#include "Scene.h"
#include "SceneLabo.h"
#include "SceneTitle.h"
#include "SceneGame.h"

#include "Fade.h"


class SceneManager
{
private:
	Scene* pScene;
	Scene* pNext;
	Scene* pStackScene;

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();

	// Scene* scene : ���̃V�[��, bool nowSceneStack : ���݂̃V�[�����c���������ǂ����H
	void SetScene(Scene* scene, bool nowSceneStack = false);

	// �X�^�b�N�����V�[���������֐�
	void ReSetStackScene();


	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

private:
	void GoToSceneLaboCommand()
	{
		if (GetKeyState(VK_CONTROL) < 0)
		{
			if (GetKeyState(VK_SHIFT) < 0)
			{
				if (GetKeyState('L') < 0)
				{
					Fade::GetInstance()->onFadeFlg = true;
					Fade::GetInstance()->SetNextScene(new SceneLabo());
				}
			}
		}
	}
};