#pragma once
#include "ParticleInformation.h"

class Particle
{
public:

	void BuffAreaUpdate(BuffAreaParticleInfo* p);
	bool SetBuffAreaParticle(BuffAreaParticleInfo* p, DirectX::XMFLOAT3 pos);

	void PlayerAttackSlashUpdate(PlayerAttackSlashParticleInfo *p);
	bool SetPlayerAttackSlash(PlayerAttackSlashParticleInfo *p, DirectX::XMFLOAT3 pos);

	void PlayerAttackSubSlashUpdate(PlayerAttackSlashParticleInfo *p);
	bool SetPlayerAttackSubSlash(PlayerAttackSlashParticleInfo *p, DirectX::XMFLOAT3 pos);

	void PlayerAttackSparkUpdate(PlayerAttackSparkParticleInfo *p);
	bool SetPlayerAttackSpark(PlayerAttackSparkParticleInfo *p, DirectX::XMFLOAT3 pos);

};