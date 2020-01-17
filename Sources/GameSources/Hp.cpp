#include "Hp.h"
#include "Blender.h"
#include "CharacterSystem.h"

void Hp::Init()
{
	hpSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/UI_HPGauge_waku.png", 2);
	hpSprData[0].texPos = { 0, 0 };		//テクスチャの左上
	hpSprData[0].size = { 830, 48 };	//テクスチャの幅、高さ
	hpSprData[1].texPos = { 0, 48 };	//テクスチャの左上
	hpSprData[1].size = { 830, 48 };	//テクスチャの幅、高さ

	texcoord = { 830 - 19, 43 };
	subHp = 0;
}

void Hp::Update()
{
	subHp = abs(798 - ((CharacterSystem::GetInstance()->GetPlayerAddress()->GetHp() * 798) / 10000.0f));

}

void Hp::Draw()
{
	SetBlenderMode(BM_ALPHA);
	hpSpr->Begin();
	hpSpr->Draw({32, 32}, { 830 * 1.0f, 48 * 1.0f }, hpSprData[0].texPos, hpSprData[0].size, 0, { 1, 1, 1, 1 });
	render(830 / 2 + 32, 48 / 2 + 32, 0, 1.0f, 1.0f, { 0, 48, 830, 48 }, {0, 48, texcoord.x - subHp, texcoord.y}, { 1, 1, 1, 1 });
	hpSpr->End();
	SetBlenderMode(BM_NONE);
}

void Hp::UnInit()
{

}

void Hp::render(float x, float y, float angle, float scalex, float scaley, DirectX::XMFLOAT4 inf, DirectX::XMFLOAT4 tex, DirectX::XMFLOAT4 color)
{
	hpSpr->Draw2(x - (inf.z / 2), y - (inf.w / 2), tex.z * scalex, tex.w * scaley, angle, color.x, color.y, color.z, color.w, tex);
}
