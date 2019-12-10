#include "Particle.h"
#include "easing.h"

// バフエリア
void Particle::BuffAreaUpdate(BuffAreaParticleInfo* p)
{
	if (!p->data.isExist) return;

	p->data.alpha = easing::InExp(p->data.time, p->data.existTime, 0.0f, 0.6f);

	p->data.pos.y += p->speed.y;

	p->data.time++;

	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetBuffAreaParticle(BuffAreaParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos       = pos;
	p->data.scale     ={ 20.0f, 20.0f };
	float y           = rand() % 100 + 30;
	p->speed          = {0.0f, y / 30, 0.0f};
	p->data.angle     = {0, 0, 0};
	p->data.alpha     = 1.0f;
	p->data.time      = 0;
	p->data.existTime = rand() % 40 + 100;
	p->data.isExist   = true;

	p->data.tex.Set(1024.0f * 4, 0.0f, 1024.0f, 1024.0f);

	return true;
}

// プレイヤーアタック (メインスラッシュ)
void Particle::PlayerAttackSlashUpdate(PlayerAttackSlashParticleInfo* p)
{
	if (!p->data.isExist) return;
	float s = easing::OutCirc(p->data.time, p->data.existTime, 0.0f, p->maxScale);
	p->data.scale.x =  s;
	s = easing::OutCirc(p->data.time, p->data.existTime, p->maxScale*1.5f, p->maxScale);
	p->data.scale.y = s;
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetPlayerAttackSlash(PlayerAttackSlashParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->maxScale = 600.0f;
	p->data.scale = DirectX::XMFLOAT2(p->maxScale, p->maxScale);

	p->data.angle = { 0, 0, rand() % 361 * 0.01745f};

	p->data.alpha = 1.0f;
	p->data.time = 0;
	p->data.existTime = 30;
	p->data.isExist = true;

	p->data.tex.Set(0.0f, 0.0f, 1024.0f, 1024.0f);

	return true;

}

// プレイヤーアタック (サブスラッシュ)
void Particle::PlayerAttackSubSlashUpdate(PlayerAttackSlashParticleInfo* p)
{
	if (!p->data.isExist) return;
	float s = easing::OutCirc(p->data.time, p->data.existTime, 0.0f, p->maxScale);
	p->data.scale.x =  s;
	s = easing::OutCirc(p->data.time, p->data.existTime, p->maxScale*1.5f, p->maxScale);
	p->data.scale.y = s;
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetPlayerAttackSubSlash(PlayerAttackSlashParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->maxScale = 600.0f;
	p->data.scale = DirectX::XMFLOAT2(p->maxScale, p->maxScale);

	p->data.angle = { 0, 0, rand() % 361 * 0.01745f};

	p->data.alpha = 1.0f;
	p->data.time = 0;
	p->data.existTime = 15;
	p->data.isExist = true;

	p->data.tex.Set(1024.0f*3, 0.0f, 1024.0f, 1024.0f);

	return true;

}

// プレイヤーアタック (スパーク)
void Particle::PlayerAttackSparkUpdate(PlayerAttackSparkParticleInfo* p)
{

	if (!p->data.isExist) return;
	float s       = easing::InQuint(p->data.time, p->data.existTime, 0.0f, p->maxScale);
	p->data.scale = { s, s };
	p->data.pos   = { p->data.pos.x + p->speed.x, p->data.pos.y + p->speed.y, p->data.pos.z + p->speed.z };
	p->speed      = { p->speed.x - p->accel.x, p->speed.y - p->accel.y , p->speed.z - p->accel.z };
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}

}

bool Particle::SetPlayerAttackSpark(PlayerAttackSparkParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.existTime = rand() % 20 + 30.0f;

	p->data.pos       = pos;
	p->maxScale       = 10.0f;
	p->data.scale     = { p->maxScale, p->maxScale };

	int x = rand() % 1000 - 500;
	int y = rand() % 300 + 200;
	int z = rand() % 1000 - 500;

	p->speed          = { x / 50.0f, y / 50.0f, z / 50.0f };
	p->accel          = { 0, 0, 0 };
	p->accel          = { p->speed.x / p->data.existTime, p->speed.y / 5.0f, p->speed.z / p->data.existTime };
	p->data.angle     = { 0, 0, rand() % 361 * 0.01745f };

	p->data.alpha     = 1.0f;
	p->data.time      = 0;
	p->data.isExist   = true;

	p->data.tex.Set(1024.0f * 1, 0.0f, 1024.0f, 1024.0f);

	return true;

}