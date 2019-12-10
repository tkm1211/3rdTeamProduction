#include "ParticleSystem.h"
#include "FrameWork.h"
#include "Camera.h"
#include "Blender.h"
#include "CameraSystem.h"


void ParticleSystem::Init()
{
	texture = std::make_unique<Billboard>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/ParticleTexure.png");
}

void ParticleSystem::Update()
{
	for (int i = 0; i < MAX; i++)
	{
		ptc.BuffAreaUpdate(&bap[i]);
		ptc.PlayerAttackSlashUpdate(&pasp[i]);
		ptc.PlayerAttackSparkUpdate(&paspark[i]);
	}
}

void ParticleSystem::Draw()
{
	SetBlenderMode(BM_ALPHA);
	SetBlenderMode(BM_ADD);
	texture->Begin(FrameWork::GetInstance().GetContext().Get());
	for (int i = 0; i < MAX; i++)
	{
		if (bap[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				bap[i].data.pos, bap[i].data.tex.x, bap[i].data.tex.y, bap[i].data.tex.sx, bap[i].data.tex.sy,
				bap[i].data.angle, bap[i].data.scale, { 1.0f, 1.0f, 1.0f, bap[i].data.alpha });
		}
		if (pasp[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				pasp[i].data.pos, pasp[i].data.tex.x, pasp[i].data.tex.y, pasp[i].data.tex.sx, pasp[i].data.tex.sy,
				pasp[i].data.angle, pasp[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
		}
		if (paspark[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				paspark[i].data.pos, paspark[i].data.tex.x, paspark[i].data.tex.y, paspark[i].data.tex.sx, paspark[i].data.tex.sy,
				paspark[i].data.angle, paspark[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
		}
	}
	texture->End();

	SetBlenderMode(BM_NONE);


}