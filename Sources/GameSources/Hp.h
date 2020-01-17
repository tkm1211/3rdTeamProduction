#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"


class Hp
{
private:
	std::unique_ptr<SpriteBatch> hpSpr;
	TexData hpSprData[2];
	DirectX::XMFLOAT2 texcoord;

	float subHp;

private:
	void render(float x, float y, float angle, float scalex, float scaley, DirectX::XMFLOAT4 inf, DirectX::XMFLOAT4 tex, DirectX::XMFLOAT4 color);
public:
	Hp() {}
	~Hp() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	float GetSubHp() { return subHp; }

};