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


	void SetBuffAreaParticle(DirectX::XMFLOAT3 pos, float rad)
	{
		float angle = rand() % 361 * 0.01745f;
		float _rad = 0;
		if(rad >= 1) _rad = rand() % (int)(rad);
		else return;
		
		for (int i = 0; i < MAX; i++)
		{
			DirectX::XMFLOAT3 _p = { pos.x + sinf(angle)*_rad, pos.y, pos.z + cosf(angle)*_rad };

			if (ptc.SetBuffAreaParticle(&bap[i], _p)) return;
		} 
	}
};