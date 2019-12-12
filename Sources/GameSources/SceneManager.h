#pragma once

#include "Scene.h"
#include "SceneLabo.h"
#include "SceneTitle.h"
#include "SceneGame.h"
#include "SceneGameOver.h"
#include "SceneTutorial.h"
#include "ScenePause.h"
#include "SceneResult.h"
#include "Fade.h"

#include <string>


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

	// Scene* scene : 次のシーン, bool nowSceneStack : 現在のシーンを残したいかどうか？
	void SetScene(Scene* scene, bool nowSceneStack = false);

	// スタックしたシーンを消す関数
	void ReSetStackScene();


	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}

private:
	std::string com;
	void GoToSceneLaboCommand()
	{
		/*if (GetKeyState(VK_CONTROL) < 0)
		{
			if (GetKeyState(VK_SHIFT) < 0)
			{
				if (GetKeyState('L') < 0)
				{
					SetScene(new SceneLabo());
				}
			}
		}*/

		if (GetKeyState(VK_RETURN) < 0)
		{
			char com_int[16];
			for (int i = 0; i < 16; i++) { com_int[i] = NULL; }
			com_int[0] = 103; com_int[1]  = 111; com_int[2]  =  32;
			com_int[3] = 115; com_int[4]  =  99; com_int[5]  = 101; com_int[6]  = 110; com_int[7] = 101; com_int[8] = 32;
			com_int[9] = 108; com_int[10] =  97; com_int[11] =  98; com_int[12] = 111;
			std::string _com(com_int);
			if (com == _com)
			{
				SetScene(new SceneLabo());
			}
		}
	}

	static const int flgInit         = 0x0000;
	static const int useImGui        = 0x0001;
	static const int usePlayerEditor = 0x0002;
	static const int useEnemyEditor  = 0x0004;
	//static const int useStageEditor  = 0x0008;
	//static const int useSoundEditor  = 0x0010;
	//static const int useShaderEditor = 0x0020;

	int commandFlg = flgInit;
	bool commandOn;
	void CommandCheck()
	{
		if (GetKeyState(VK_RETURN) < 0)
		{
			if (com == std::string("use imgui"))
			{
				commandFlg |= useImGui;
			}
			else if (com == std::string("not use imgui"))
			{
				commandFlg &= ~useImGui;
			}

			else if (com == std::string("use player editor"))
			{
				commandFlg |= usePlayerEditor;
			}
			else if (com == std::string("not use player editor"))
			{
				commandFlg &= ~usePlayerEditor;
			}

			else if (com == std::string("use enemy editor"))
			{
				commandFlg |= useEnemyEditor;
			}
			else if (com == std::string("not use enemy editor"))
			{
				commandFlg &= ~useEnemyEditor;
			}

			com.erase();
		}
	}
};