#pragma once
#include "Billboard.h"
#include "Particle.h"

class ParticleSystem
{
private:
	static const int MAX = 500;
	std::unique_ptr<Billboard> texture;
//public:

	BuffAreaParticleInfo bap[MAX];
	PlayerAttackSlashParticleInfo pasp[MAX];
	PlayerAttackSparkParticleInfo paspark[MAX];

	Particle ptc;
public:

	ParticleSystem() {}
	~ParticleSystem() {}

	void Init();
	void Update();
	void Draw();

	
	static ParticleSystem* GetInstance()
	{
		static ParticleSystem instance;
		return &instance;
	}


	// �B�l�̉���
	void SetBuffAreaParticle(DirectX::XMFLOAT3 pos, float rad)
	{
		float angle = rand() % 361 * 0.01745f;

		for (int i = 0; i < MAX; i++)
		{
			DirectX::XMFLOAT3 _p = { pos.x + sinf(angle)* rad, pos.y, pos.z + cosf(angle) * rad };

			if (ptc.SetBuffAreaParticle(&bap[i], _p)) return;
		} 
	}

	// �v���C���[�U���@�q�b�g��(�X���b�V��)
	void SetPlayerAttackSlashParticle(DirectX::XMFLOAT3 pos)
	{		
		//SetPlayerAttackSubSlashParticle(pos);
		SetPlayerAttackSparkParticle(pos);
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetPlayerAttackSlash(&pasp[i], pos)) return;
		} 
	}

	// �v���C���[�U���@�q�b�g��(�T�u�X���b�V��)
	void SetPlayerAttackSubSlashParticle(DirectX::XMFLOAT3 pos)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetPlayerAttackSubSlash(&pasp[i], pos)) return;
		}
	}

	//�v���C���[�U���@�q�b�g��(�Ή�)
	void SetPlayerAttackSparkParticle(DirectX::XMFLOAT3 pos)
	{		
		int num = 0;
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetPlayerAttackSpark(&paspark[i], pos)) num++;
			if (num >= 30) return;
		} 
	}
};