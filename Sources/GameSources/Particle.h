#pragma once
#include "ParticleInformation.h"

class Particle
{
public:
	void BuffAreaUpdate(BuffAreaParticleInfo* p);
	bool SetBuffAreaParticle(BuffAreaParticleInfo* p, DirectX::XMFLOAT3 pos);
};