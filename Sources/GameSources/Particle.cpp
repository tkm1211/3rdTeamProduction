#include "Particle.h"
#include "easing.h"

void Particle::BuffAreaUpdate(BuffAreaParticleInfo* p)
{
	if (!p->data.isExist) return;
	float s = easing::OutCirc(p->data.time, p->data.existTime, p->maxScale, 0.0f);
	p->data.scale = {s, s};
	p->data.alpha = easing::InExp(p->data.time, p->data.existTime, 0.0f, 0.6f);
	p->data.time++;
	if (p->data.time > p->data.existTime)
	{
		p->data.isExist = false;
	}
}

bool Particle::SetBuffAreaParticle(BuffAreaParticleInfo* p, DirectX::XMFLOAT3 pos)
{
	if (p->data.isExist) return false;

	p->data.pos = pos;
	p->data.scale = DirectX::XMFLOAT2(0, 0);
	p->data.angle = {0, 0, 0};
	p->data.alpha = 1.0f;
	p->data.time = 0;
	p->data.existTime = rand() % 40 + 100;
	p->maxScale = rand() % 100 + 300;
	p->data.isExist = true;

	p->data.tex.Set(1024.0f, 1024.0f, 1024.0f, 1024.0f);

	return true;
}