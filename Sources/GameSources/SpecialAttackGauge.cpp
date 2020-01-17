#include "SpecialAttackGauge.h"
#include "Blender.h"

void SpecialAttackGauge::Init()
{
	specialGaugeSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/UI_HPGauge_waku.png", 2);
	specialGaugeSprData.texPos = { 0, 48*0 };		//テクスチャの左上
	specialGaugeSprData.size = { 830, 48 };	//テクスチャの幅、高さ

	texcoord = { 830 - 19, 43 };

	addGauge = 0.0;
	attackPoint = 0;
}

void SpecialAttackGauge::Update()
{
	addGauge = abs(798 - ((attackPoint * 798) / 10000.0f));

	//if (GetKeyState('A') < 0)
	//{
	//	attackPoint++;
	//}
	//if (GetKeyState('D') < 0)
	//{
	//	attackPoint--;
	//}
}

void SpecialAttackGauge::Draw()
{
	SetBlenderMode(BM_ALPHA);
	specialGaugeSpr->Begin();
	specialGaugeSpr->Draw({ 32, 72 }, { 830 * 1.0f, 48 * 1.0f }, specialGaugeSprData.texPos, specialGaugeSprData.size, 0, { 1, 1, 1, 1 });
	render(830 / 2 + 32, 48 / 2 + 72, 0, 1.0f, 1.0f, { 0, 48*2, 830, 48 }, { 0, 48*2, texcoord.x - addGauge, texcoord.y }, { 1, 1, 1, 1 });
	specialGaugeSpr->End();
	SetBlenderMode(BM_NONE);
}

void SpecialAttackGauge::UnInit()
{

}

void SpecialAttackGauge::render(float x, float y, float angle, float scalex, float scaley, DirectX::XMFLOAT4 inf, DirectX::XMFLOAT4 tex, DirectX::XMFLOAT4 color)
{
	specialGaugeSpr->Draw2(x - (inf.z / 2), y - (inf.w / 2), tex.z * scalex, tex.w * scaley, angle, color.x, color.y, color.z, color.w, tex);
}
