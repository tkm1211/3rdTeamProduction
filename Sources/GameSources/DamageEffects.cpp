#include "DamageEffects.h"
#include "Blender.h"
#include "easing.h"

void DamageEffects::Init()
{
	damageSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/damageEffect.png", 100);
	damageSprData.texPos = { 0, 0 };		//テクスチャの左上
	damageSprData.size = { 480, 480 };	//テクスチャの幅、高さ

}

void DamageEffects::Update()
{
	for (auto& it : damageEffectsInfo)
	{
		if (!it.isDisplay) continue;
		it.alpha = easing::InQuint(it.reduceTime, 120.0f, 0.0f, 1.0f);
		it.reduceTime++;
		if (it.reduceTime > 120)
		{
			it.isDisplay = false;
		}
	}
}

void DamageEffects::Draw()
{


	SetBlenderMode(BM_ALPHA);
	damageSpr->Begin();
	for (auto& it : damageEffectsInfo)
	{
		if (!it.isDisplay) continue;
		DrawRota(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, DirectX::XMConvertToDegrees(it.angle), 1, { 0, 0, 480, 480 }, {1, 1, 1, it.alpha});
	}
	damageSpr->End();
	SetBlenderMode(BM_NONE);
}

void DamageEffects::UnInit()
{

}

void DamageEffects::AddToEffects(DirectX::XMFLOAT3 _p1, DirectX::XMFLOAT3 _p2)
{
	DamageEffectsInfo tmp;

	_p1.x *= -1;
	float ang = atan2( _p2.z - _p1.z,  _p2.x - _p1.x);

	tmp.angle           = ang;
	tmp.alpha           = 1.0f;
	tmp.reduceTime = 0;
	tmp.isDisplay      = true;
	for (auto& it : damageEffectsInfo)
	{
		if (it.isDisplay) continue;
		it.angle           = tmp.angle;
		it.alpha           = tmp.alpha;
		it.reduceTime = tmp.reduceTime;
		it.isDisplay      = tmp.isDisplay;
		return;
	}

		damageEffectsInfo.push_back(tmp);
		return;
}

void DamageEffects::DrawRota(float x, float y, float angle, float scale, DirectX::XMFLOAT4 inf, DirectX::XMFLOAT4 color)
{
	damageSpr->Draw2(x - (inf.z / 2), y - (inf.w / 2), inf.z * scale, inf.w * scale, angle, color.x, color.y, color.z, color.w, inf);
}