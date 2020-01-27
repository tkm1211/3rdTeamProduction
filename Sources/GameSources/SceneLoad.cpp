#include <FrameWork.h>
#include <string>
#include "Fade.h"
#include "SceneLoad.h"

void SceneLoad::Init()
{
}

void SceneLoad::Update()
{
	if (Fade::GetInstance()->loading) return;

	Fade::GetInstance()->onFadeFlg = true;
	Fade::GetInstance()->loading = true;
	Fade::GetInstance()->SetNextScene(new SceneTitle());


}

void SceneLoad::Render()
{
}

void SceneLoad::ImGui()
{
}

void SceneLoad::UnInit() {}