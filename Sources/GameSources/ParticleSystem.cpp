#include "ParticleSystem.h"
#include "FrameWork.h"
#include "Camera.h"
#include "Blender.h"
#include "CameraSystem.h"


void ParticleSystem::Init()
{
	texture = std::make_unique<Billboard>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/ParticleTexture.png");
	swordLocus = std::make_unique<SwordLocus>();
	swordLocus->Init();
	popParticleNum = 0;
}

void ParticleSystem::Update()
{
	for (int i = 0; i < MAX; i++)
	{
		ptc.BuffAreaUpdate(&bap[i]);
		ptc.PlayerAttackSlashUpdate(&pasp[i]);
		ptc.PlayerAttackSparkUpdate(&paspark[i]);
		ptc.PlayerAttackAfterImageUpdate(&plAfterImage[i]);
		ptc.CrystalDestroyUpdate(&crystalDestroy[i]);
		ptc.SmokeUpdate(&smoke[i]);
		ptc.ThuderUpdate(&thunder[i]);
		ptc.UltimetThuderUpdate(&ultimetThunder[i]);
		ptc.UltimetThuderStoneUpdate(&ultimetThunderStone[i]);
		ptc.ArrowUpdate(&arrow[i]);
		ptc.BuffUpdate(&buff[i]);
		if (ptc.SparkUpdate(&spark[i]))
		{
			SetSparkAfterImage(spark[i].data.pos, spark[i].data.scale.x);
		}

		ptc.SparkAfterImageUpdate(&sparkAfterImage[i]);
	}

	swordLocus->Update();

}

void ParticleSystem::Draw()
{
	texture->Begin(FrameWork::GetInstance().GetContext().Get());
	for (int i = 0; i < MAX; i++)
	{
		SetBlenderMode(BM_ADD);
		if (bap[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				bap[i].data.pos, bap[i].data.tex.x, bap[i].data.tex.y, bap[i].data.tex.sx, bap[i].data.tex.sy,
				bap[i].data.angle, bap[i].data.scale, { 1.0f, 1.0f, 1.0f, bap[i].data.alpha });
			popParticleNum++;
		}
		if (pasp[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				pasp[i].data.pos, pasp[i].data.tex.x, pasp[i].data.tex.y, pasp[i].data.tex.sx, pasp[i].data.tex.sy,
				pasp[i].data.angle, pasp[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (paspark[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				paspark[i].data.pos, paspark[i].data.tex.x, paspark[i].data.tex.y, paspark[i].data.tex.sx, paspark[i].data.tex.sy,
				paspark[i].data.angle, paspark[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (plAfterImage[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				plAfterImage[i].data.pos, plAfterImage[i].data.tex.x, plAfterImage[i].data.tex.y, plAfterImage[i].data.tex.sx, plAfterImage[i].data.tex.sy,
				plAfterImage[i].data.angle, plAfterImage[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (thunder[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				thunder[i].data.pos, thunder[i].data.tex.x, thunder[i].data.tex.y, thunder[i].data.tex.sx, thunder[i].data.tex.sy,
				thunder[i].data.angle, thunder[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (ultimetThunder[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				ultimetThunder[i].data.pos, ultimetThunder[i].data.tex.x, ultimetThunder[i].data.tex.y, ultimetThunder[i].data.tex.sx, ultimetThunder[i].data.tex.sy,
				ultimetThunder[i].data.angle, ultimetThunder[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (sparkAfterImage[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				sparkAfterImage[i].data.pos, sparkAfterImage[i].data.tex.x, sparkAfterImage[i].data.tex.y, sparkAfterImage[i].data.tex.sx, sparkAfterImage[i].data.tex.sy,
				sparkAfterImage[i].data.angle, sparkAfterImage[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		SetBlenderMode(BM_ALPHA);
		if (ultimetThunderStone[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				ultimetThunderStone[i].data.pos, ultimetThunderStone[i].data.tex.x, ultimetThunderStone[i].data.tex.y, ultimetThunderStone[i].data.tex.sx, ultimetThunderStone[i].data.tex.sy,
				ultimetThunderStone[i].data.angle, ultimetThunderStone[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (smoke[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				smoke[i].data.pos, smoke[i].data.tex.x, smoke[i].data.tex.y, smoke[i].data.tex.sx, smoke[i].data.tex.sy,
				smoke[i].data.angle, smoke[i].data.scale, { 1.0f, 1.0f, 1.0f, smoke[i].data.alpha });
			popParticleNum++;
		}
		if (crystalDestroy[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				crystalDestroy[i].data.pos, crystalDestroy[i].data.tex.x, crystalDestroy[i].data.tex.y, crystalDestroy[i].data.tex.sx, crystalDestroy[i].data.tex.sy,
				crystalDestroy[i].data.angle, crystalDestroy[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		SetBlenderMode(BM_ADD);
		//SetBlenderMode(BM_ALPHA);
		if (arrow[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				arrow[i].data.pos, arrow[i].data.tex.x, arrow[i].data.tex.y, arrow[i].data.tex.sx, arrow[i].data.tex.sy,
				arrow[i].data.angle, arrow[i].data.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
			popParticleNum++;
		}
		if (buff[i].data.isExist)
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				buff[i].data.pos, buff[i].data.tex.x, buff[i].data.tex.y, buff[i].data.tex.sx, buff[i].data.tex.sy,
				buff[i].data.angle, buff[i].data.scale, buff[i].color);
			popParticleNum++;
		}
	}
	texture->End();

	swordLocus->Draw();
	
	SetBlenderMode(BM_NONE);


}