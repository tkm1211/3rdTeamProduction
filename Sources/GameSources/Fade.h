#pragma once

#include "Scene.h"
#include "Sprite.h"
#include "Model.h"
#include "OBJ3D.h"


class Fade
{

private:
	std::unique_ptr<SpriteBatch> fade_spr;
	TexData fade_spr_data;
	int state;
	float alpha;

	Scene* scene;

public:
	bool onFadeFlg;

	Fade() {}
	~Fade() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();
	
	//Fadeå„ÇÃÉVÅ[Éì
	void SetNextScene(Scene* s) { scene = s; }

	static Fade* GetInstance()
	{
		static Fade instance;
		return &instance;
	}


};