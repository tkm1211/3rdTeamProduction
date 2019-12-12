#include "Hp.h"
#include "Blender.h"
#include "CharacterSystem.h"

void Hp::Init()
{
	hpSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/UI_HPGauge_waku.png", 2);
	hpSprData[0].texPos = { 0, 0 };		//テクスチャの左上
	hpSprData[0].size = { 990, 257 };	//テクスチャの幅、高さ
	hpSprData[1].texPos = { 0, 257 };	//テクスチャの左上
	hpSprData[1].size = { 990, 257 };	//テクスチャの幅、高さ

	texcoord = { 840, 257 };
	subHp = 0;
}

void Hp::Update()
{
	subHp = abs(610 - ((CharacterSystem::GetInstance()->GetPlayerAddress()->GetHp() * 610) / 10000.0f));
}

void Hp::Draw()
{
	SetBlenderMode(BM_ALPHA);
	hpSpr->Begin();
	hpSpr->Draw({32, 32}, { 990 * 0.75f, 257 * 0.75f }, hpSprData[0].texPos, hpSprData[0].size, 0, { 1, 1, 1, 1 });
	render(990 / 2 + 33, 257 / 2 + 33, 0, 0.75, 0.75, { 0, 257, 990, 257 }, {0, 257, texcoord.x - subHp, texcoord.y}, { 1, 1, 1, 1 });
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
