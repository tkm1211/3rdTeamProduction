#pragma once
#include "Scene.h"
#include "Sprite.h"

#include <memory>


class ScenePause : public Scene
{
private:
	enum SelectState
	{
		RETURN_GAME,
		RESTART,
		RETURN_TITLE
	};

private:
	std::unique_ptr<Sprite> bg;
	std::unique_ptr<Sprite> ui;

	TexData returnGame;
	TexData restart;
	TexData returnTitle;

	int state;
	int cnt;
	float size[3];

	int keyCnt[2];

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};