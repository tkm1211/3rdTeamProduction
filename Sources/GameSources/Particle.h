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

	void PlayerAttackAfterImageUpdate(PlayerAttackAfterImageParticleInfo*p);
	bool SetPlayerAttackAfterImage(PlayerAttackAfterImageParticleInfo*p, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 ang);

	void CrystalDestroyUpdate(CrystalDestroyParticleInfo* p);
	bool SetCrystalDestroy(CrystalDestroyParticleInfo*p, DirectX::XMFLOAT3 pos);

	void SmokeUpdate(SmokeParticleInfo* p);
	bool SetSmoke(SmokeParticleInfo* p, DirectX::XMFLOAT3 pos, float minScale, float maxScale);

	void ThuderUpdate(ThuderEffectInfo* p);
	bool SetThuder(ThuderEffectInfo* p, DirectX::XMFLOAT3 pos);

	void UltimetThuderUpdate(UltimetThuderEffectInfo* p);
	bool SetUltimateThuder(UltimetThuderEffectInfo* p, DirectX::XMFLOAT3 pos);

	void UltimetThuderStoneUpdate(UltimetThuderStoneParticle* p);
	bool SetUltimateThuderStone(UltimetThuderStoneParticle* p, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 nmlSpeed, float scale, bool isBreak);

	bool SparkUpdate(SparkParticle* p);
	bool SetSpark(SparkParticle* p, DirectX::XMFLOAT3 pos);

	void SparkAfterImageUpdate(SparkAfterImageParticle* p);
	bool SetSparkAfterImage(SparkAfterImageParticle* p, DirectX::XMFLOAT3 pos, float scsale);

	void ArrowUpdate(ArrowParticleInfo* p);
	bool SetArrowParticle(ArrowParticleInfo* p, DirectX::XMFLOAT3 pos);

};