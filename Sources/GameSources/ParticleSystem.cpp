#include "ParticleSystem.h"
#include "FrameWork.h"
#include "Camera.h"
#include "Blender.h"
#include "CameraSystem.h"


void ParticleSystem::Init()
{
	texture = std::make_unique<Billboard>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/Effect_Aura_Cloud1.png");
}

void ParticleSystem::Update()
{
	for (int i = 0; i < MAX; i++)
	{
		ptc.BuffAreaUpdate(&bap[i]);
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
	}
	texture->End();

	SetBlenderMode(BM_NONE);


}