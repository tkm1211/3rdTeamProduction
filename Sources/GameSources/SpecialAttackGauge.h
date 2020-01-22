#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"

class SpecialAttackGauge
{
private:
	std::unique_ptr<SpriteBatch> specialGaugeSpr;
	TexData specialGaugeSprData;
	DirectX::XMFLOAT2 texcoord;
	int attackPoint;
	int totalPoint;
	float addGauge;
private:
	void render(float x, float y, float angle, float scalex, float scaley, DirectX::XMFLOAT4 inf, DirectX::XMFLOAT4 tex, DirectX::XMFLOAT4 color);

public:
	SpecialAttackGauge() {}
	~SpecialAttackGauge() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void SetAttckPoint(int _point);

};