#include "Particle.h"
#include "easing.h"
#include "ParticleSystem.h"

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
	p->maxScale = 900.0f;
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

// プレイヤーアタック (残像)
void Particle::PlayerAttackAfterImageUpdate(PlayerAttackAfterImageParticleInfo* p)
{

	if (!p->data.isExist) return;
	float s       = easing::InQuint(p->data.time, p->data.existTime, 0.0f, p->maxScale);
	p->data.scale = { s, s };

	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}

}

bool Particle::SetPlayerAttackAfterImage(PlayerAttackAfterImageParticleInfo* p, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 ang)
{
	if (p->data.isExist) return false;

	p->data.pos       = pos;
	p->maxScale       = 70.0f;
	p->data.scale     = { p->maxScale, p->maxScale };

	p->data.angle     = ang;

	p->data.alpha     = 1.0f;
	p->data.time      = 0;

	p->data.isExist   = true;
	p->data.existTime = 30.0f;

	p->data.tex.Set(1024.0f * 1.0f, 1024.0f * 1, 1024.0f, 1024.0f);

	return true;

}

// クリスタル破壊
void Particle::CrystalDestroyUpdate(CrystalDestroyParticleInfo* p)
{

	if (!p->data.isExist) return;
	//float s       = easing::InQuint(p->data.time, p->data.existTime, 0.0f, p->maxScale);
	//p->data.scale = { s, s };

	p->data.pos = { p->data.pos.x + p->speed.x, p->data.pos.y + p->speed.y , p->data.pos.z + p->speed.z };

	p->speed = { p->speed.x - p->accel.x, p->speed.y - p->accel.y , p->speed.z - p->accel.z };

	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}

}

bool Particle::SetCrystalDestroy(CrystalDestroyParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos       = pos;
	p->maxScale = rand() % 30 + 20;
	p->data.scale     = { p->maxScale, p->maxScale };

	int x = rand() % 1000 - 500;
	int y = rand() % 200 + 100;
	int z = rand() % 1000 - 500;

	p->speed = { x / 50.0f, y / 10.0f, z / 50.0f };

	p->data.angle     = { 0, 0, rand() % 361 * 0.01745f };

	p->data.alpha     = 1.0f;
	p->data.time      = 0;

	p->data.isExist   = true;
	p->data.existTime = 50.0f;

	p->accel = { p->speed.x / (p->data.existTime * 1.3f), p->speed.y / (p->data.existTime * 0.3f) , p->speed.z / (p->data.existTime * 1.3f) };

	int r = rand() % 2;
	p->data.tex.Set(1024.0f * 2.0f + r, 1024.0f * 1, 1024.0f, 1024.0f);

	return true;

}

// 煙
void Particle::SmokeUpdate(SmokeParticleInfo* p)
{
	if (!p->data.isExist) return;
	float s       = easing::InQuint(p->data.time, p->data.existTime, p->maxScale, p->originScale);
	p->data.scale = { s, s };

	p->data.pos = { p->data.pos.x + p->speed.x, p->data.pos.y + p->speed.y , p->data.pos.z + p->speed.z };

	p->data.alpha = easing::InSine(p->data.time, p->data.existTime, 0.0f, 1.0f);

	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetSmoke(SmokeParticleInfo* p, DirectX::XMFLOAT3 pos, float minScale, float maxScale)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;

	p->maxScale = rand() % 100 + maxScale;

	p->originScale = rand() % 100 + minScale;
	p->data.scale = { p->originScale, p->originScale };
	p->maxScale += p->originScale;


	int x = rand() % 1000 - 500;
	int y = rand() % 200 + 100;
	int z = rand() % 1000 - 500;

	p->speed = { x / 500.0f, y / 50.0f, z / 500.0f };

	p->data.angle = { 0, 0, rand() % 361 * 0.01745f };

	p->data.alpha = 0.0f;
	p->data.time = 0;

	p->data.existTime = rand() % 30 + 20;
	p->data.isExist = true;

	p->data.tex.Set(1024.0f * 4.0f, 1024.0f * 1, 1024.0f, 1024.0f);

	return true;

}

void Particle::ThuderUpdate(ThuderEffectInfo* p)
{
	if (!p->data.isExist) return;
	int r = rand() % 4;
	p->data.tex.Set(1024.0f * (1 + r), 1024.0f * 2, 1024.0f, 1024.0f);
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetThuder(ThuderEffectInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->originScale = 400;
	p->data.scale = { p->originScale, p->originScale };

	float a = rand() % 180 - 90;
	a += rand() % 2 * 180;
	p->data.angle = { 0, 0, a * 0.01745f };

	p->data.alpha = 1.0f;
	p->data.time = 0;

	p->data.existTime = rand() % 10 + 10;
	p->data.isExist = true;

	int r = rand() % 4;
	p->data.tex.Set(1024.0f * (1 + r), 1024.0f * 2, 1024.0f, 1024.0f);

	return true;
}

void Particle::UltimetThuderUpdate(UltimetThuderEffectInfo* p)
{
	if (!p->data.isExist) return;
	float s = easing::InQuint(p->data.time, p->data.existTime, 0.0f, p->originScale);
	p->data.scale = { s * 0.3f, s };
	int r = rand() % 4;
	p->data.tex.Set(1024.0f * (1 + r), 1024.0f * 2, 1024.0f, 1024.0f);
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetUltimateThuder(UltimetThuderEffectInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->originScale = 2000;
	p->data.scale = { p->originScale * 0.3f, p->originScale };

	float a = rand() % 45 - (45 / 2.0f);
	a += rand() % 2 * 180;
	p->data.angle = { 0, 0, a * 0.01745f };

	p->data.alpha = 1.0f;
	p->data.time = 0;

	p->data.existTime = rand() % 10 + 5;
	p->data.isExist = true;

	int r = rand() % 4;
	p->data.tex.Set(1024.0f * (1 + r), 1024.0f * 2, 1024.0f, 1024.0f);

	return true;
}

void Particle::UltimetThuderStoneUpdate(UltimetThuderStoneParticle* p)
{
	if (!p->data.isExist) return;
	p->data.pos = { p->data.pos.x + p->speed.x, p->data.pos.y + p->speed.y, p->data.pos.z + p->speed.z };
	p->speed.y -= p->subSpeedY;
	p->data.angle.z += p->addAngleZ;
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetUltimateThuderStone(UltimetThuderStoneParticle* p, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 nmlSpeed, float scale, bool isBreak)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->data.scale = { scale, scale };

	float _speedY = 0;
	 _speedY = rand() % 10 + 15.0f;
	p->speed = { nmlSpeed.x * 8.0f, _speedY, nmlSpeed.z * 8.0f };

	float a = rand() % 45 - (45 / 2.0f);
	a += rand() % 2 * 180;
	p->data.angle = { 0, 0, a * 0.01745f };

	p->data.alpha = 1.0f;
	p->data.time = 0;

	p->data.existTime = rand() % 10 + 40;
	p->data.isExist = true;

	p->subSpeedY = (p->data.existTime * 0.5f) / p->speed.y;
	p->addAngleZ = (rand() % 14 - 7) * 0.01745f;

	p->data.tex.Set(1024.0f * 0, 1024.0f * 2, 1024.0f, 1024.0f);

	return true;
}

bool Particle::SparkUpdate(SparkParticle* p)
{
	if (!p->data.isExist) return false;


	p->data.pos.x += p->speed.x;
	p->data.pos.y += p->speed.y;
	p->data.pos.z += p->speed.z;

	p->data.time++;

	p->speed.y += p->subSpeedY;

	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
	return true;
}

bool Particle::SetSpark(SparkParticle* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	float s = rand() % 50 + 10.0f;
	p->data.scale = { s, s};

	p->data.angle = { 0, 0, 0 };

	p->data.alpha = 1.0f;
	p->data.time = 0;

	p->maxSpeed = rand() % 10 + 5;
	p->angle = rand() % 360 * 0.01745f;

	p->speed = { sinf(p->angle) * p->maxSpeed, rand() % 8 + 3.0f, cosf(p->angle) * p->maxSpeed };
	p->subSpeedY = p->speed.y * -0.48f;

	p->data.existTime = rand() % 10 + 40;
	p->data.isExist = true;

	p->data.tex.Set(1024.0f * 0, 1024.0f * 3, 1024.0f, 1024.0f);

	return true;
}

void Particle::SparkAfterImageUpdate(SparkAfterImageParticle* p)
{
	if (!p->data.isExist) return;

	float s = easing::OutSine(p->data.time, p->data.existTime, 0, p->originScale);
	p->data.scale = { s, s };

	p->data.time++;

	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetSparkAfterImage(SparkAfterImageParticle* p, DirectX::XMFLOAT3 pos, float scale)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;

	p->data.scale = { scale, scale };

	p->originScale = scale;

	p->data.angle = { 0, 0, 0 };

	p->data.alpha = 1.0f;
	p->data.time = 0;

	p->data.existTime = 10;
	p->data.isExist = true;

	p->data.tex.Set(1024.0f * 0, 1024.0f * 3, 1024.0f, 1024.0f);

	return true;
}

// 矢
void Particle::ArrowUpdate(ArrowParticleInfo* p)
{
	if (!p->data.isExist) return;

	p->data.alpha = easing::InExp(p->data.time, p->data.existTime, 0.0f, 1.0f);

	p->data.scale.x = 20.0f * p->data.alpha;
	p->data.scale.y = 20.0f * p->data.alpha;

	p->data.time++;

	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetArrowParticle(ArrowParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->data.scale = { 20.0f, 20.0f };
	float y = rand() % 100 + 30;
	p->data.angle = { 0, 0, 0 };
	p->data.alpha = 1.0f;
	p->data.time = 0;
	p->data.existTime = 100;
	p->data.isExist = true;

	p->data.tex.Set(1024.0f * 4, 0.0f, 1024.0f, 1024.0f);

	return true;
}