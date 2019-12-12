#include "WaveTex.h"
#include "easing.h"
#include "Blender.h"


void WaveTex::Init()
{
	wave = std::make_unique<Sprite>(L"Data/Assets/Texture/WAVE/WAVE.png");
	num = std::make_unique<Sprite>(L"Data/Assets/Texture/WAVE/Number.png");
}
void WaveTex::Update()
{
	if (move)
	{
		switch (status)
		{
		case WaveTex::MOVE_IN:
			wavePos.x = easing::OutExp(static_cast<float>(timer), static_cast<float>(MAX_IN_TIMER), 0.0f, -1920.0f);
			waveNumPos.x = easing::OutExp(static_cast<float>(timer), static_cast<float>(MAX_IN_TIMER), 750.0f, 1920.0f + 750.0f);
			if (MAX_IN_TIMER <= timer++)
			{
				timer = 0;
				wavePos.x = 0.0f;
				waveNumPos.x = 750.0f;
				status = WaveTex::STOP;
			}
			break;
		case WaveTex::STOP:
			if (MAX_STOP_TIMER <= timer++)
			{
				timer = 0;
				status = WaveTex::MOVE_OUT;
			}
			break;
		case WaveTex::MOVE_OUT:
			wavePos.x = easing::InExp(static_cast<float>(timer), static_cast<float>(MAX_OUT_TIMER), 1920.0f, 0.0f);
			waveNumPos.x = easing::InExp(static_cast<float>(timer), static_cast<float>(MAX_OUT_TIMER), -1920.0f + 750.0f, 750.0f);
			if (MAX_OUT_TIMER <= timer++)
			{
				timer = 0;
				wavePos.x = 1920.0f;
				waveNumPos.x = -1920.0f + 750.0f;
				move = false;
				status = WaveTex::END;
			}
			break;
		case WaveTex::END: break;
		default: break;
		}
	}
}
void WaveTex::Draw()
{
	if (move)
	{
		SetBlenderMode(BM_ALPHA);
		wave->Draw(wavePos, DirectX::XMFLOAT2(1920.0f, 1080.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1920.0f, 1080.0f), 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		num->Draw(waveNumPos, DirectX::XMFLOAT2(200.0f, 200.0f), DirectX::XMFLOAT2(200.0f * static_cast<float>(no[0]), 0.0f), DirectX::XMFLOAT2(200.0f, 200.0f), 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		num->Draw(DirectX::XMFLOAT2(waveNumPos.x + 200.0f, waveNumPos.y), DirectX::XMFLOAT2(200.0f, 200.0f), DirectX::XMFLOAT2(200.0f * static_cast<float>(no[1]), 0.0f), DirectX::XMFLOAT2(200.0f, 200.0f), 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		SetBlenderMode(BM_NONE);
	}
}
void WaveTex::Start(int waveNum)
{
	if (move) return;

	move = true;
	status = WaveTex::MOVE_IN;
	wavePos.x = -1920.0f;
	wavePos.y = 0.0f;
	waveNumPos.x = 1920.0f + 750.0f;
	waveNumPos.y = 550.0f;
	no[0] = waveNum / 10;
	no[1] = waveNum % 10;
}