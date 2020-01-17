#pragma once

#include <memory>
#include <Camera.h>
#include <Model.h>
#include <Billboard.h>
#include <GeometricPrimitive.h>

#include "Scene.h"
#include "Sprite.h"


class DamageEffects
{
private:

	struct DamageEffectsInfo
	{
		float angle;        //degree
		float alpha;
		int    reduceTime;
		bool  isDisplay;   //表示フラグ
	};

	std::unique_ptr<SpriteBatch> damageSpr;
	TexData damageSprData;

	std::vector<DamageEffectsInfo> damageEffectsInfo;
public:
	DamageEffects() {}
	~DamageEffects() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void DrawRota(float x, float y, float angle, float scale, DirectX::XMFLOAT4 inf, DirectX::XMFLOAT4 color);

	// _p1 : プレイヤーの座標 _p2 : アーチャーの座標
	void AddToEffects(DirectX::XMFLOAT3 _p1, DirectX::XMFLOAT3 _p2);

};