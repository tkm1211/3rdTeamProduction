#pragma once
#include "Billboard.h"
#include "Particle.h"

class ParticleSystem
{
private:
	static const int MAX = 1000;
	std::unique_ptr<Billboard> texture;

	BuffAreaParticleInfo bap[MAX];
	PlayerAttackSlashParticleInfo pasp[MAX];
	PlayerAttackSparkParticleInfo paspark[MAX];
	PlayerAttackAfterImageParticleInfo plAfterImage[MAX];
	CrystalDestroyParticleInfo crystalDestroy[MAX];
	SmokeParticleInfo smoke[MAX];

	Particle ptc;
public:
	int popParticleNum;

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


	// 達人の煙筒
	void SetBuffAreaParticle(DirectX::XMFLOAT3 pos, float rad)
	{
		float angle = rand() % 361 * 0.01745f;

		for (int i = 0; i < MAX; i++)
		{
			DirectX::XMFLOAT3 _p = { pos.x + sinf(angle)* rad, pos.y, pos.z + cosf(angle) * rad };

			if (ptc.SetBuffAreaParticle(&bap[i], _p)) return;
		} 
	}

	// プレイヤー攻撃　ヒット時(スラッシュ)
	void SetPlayerAttackSlashParticle(DirectX::XMFLOAT3 pos)
	{		
		int num = 0;
		//SetPlayerAttackSubSlashParticle(pos);
		SetPlayerAttackSparkParticle(pos);
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetPlayerAttackSlash(&pasp[i], pos)) num++;
			if (num >= 2) return;
		} 
	}

	// プレイヤー攻撃　ヒット時(サブスラッシュ)
	void SetPlayerAttackSubSlashParticle(DirectX::XMFLOAT3 pos)
	{
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetPlayerAttackSubSlash(&pasp[i], pos)) return;
		}
	}

	// プレイヤー攻撃　ヒット時(火花)
	void SetPlayerAttackSparkParticle(DirectX::XMFLOAT3 pos)
	{		
		int num = 0;
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetPlayerAttackSpark(&paspark[i], pos)) num++;
			if (num >= 30) return;
		} 
	}

	// プレイヤー攻撃　(残像)
	void SetPlayerAttackAfterImageParticle(DirectX::XMFLOAT3 origin, DirectX::XMFLOAT3 sPos, DirectX::XMFLOAT3 ePos, DirectX::XMFLOAT3 angle)
	{
		int num = 0;
		for (int i = 0; i < MAX; i++)
		{
			//if (ptc.SetPlayerAttackAfterImage(&plAfterImage[i], ePos)) return;
			if (ptc.SetPlayerAttackAfterImage(&plAfterImage[i], SphereLinear(origin, ePos, sPos, 0.05f*num), angle)) num++;
			if (num > 20) return;
		} 
	}

	// クリスタル破壊
	void SetCrystalDestroy(DirectX::XMFLOAT3 pos)
	{
		int num = 0;
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetCrystalDestroy(&crystalDestroy[i], pos)) num++;
			if (num >= 15)
			{
				SetSmoke(pos);
				return;
			}
		}
	}

	// 煙
	void SetSmoke(DirectX::XMFLOAT3 pos)
	{
		int num = 0;
		for (int i = 0; i < MAX; i++)
		{
			if (ptc.SetSmoke(&smoke[i], pos)) num++;
			if (num >= 2) return;
		}
	}

	DirectX::XMFLOAT3 SphereLinear // 戻り値 : 補間座標
	(
		DirectX::XMFLOAT3 originPos, // 原点
		DirectX::XMFLOAT3 oldPos,    // 前のフレームの座標
		DirectX::XMFLOAT3 nowPos,    // 今のフレームの座標
		float t					     // 補間値（0.0f ～ 1.0f）
	)
	{
		DirectX::XMVECTOR start, end;
		start = DirectX::XMVector3Normalize(DirectX::XMVectorSet(oldPos.x - originPos.x, oldPos.y - originPos.y, oldPos.z - originPos.z, 1.0f));
		end = DirectX::XMVector3Normalize(DirectX::XMVectorSet(nowPos.x - originPos.x, nowPos.y - originPos.y, nowPos.z - originPos.z, 1.0f));
		DirectX::XMFLOAT3 _start, _end;
		_start = DirectX::XMFLOAT3(oldPos.x - originPos.x, oldPos.y - originPos.y, oldPos.z - originPos.z);
		_end = DirectX::XMFLOAT3(nowPos.x - originPos.x, nowPos.y - originPos.y, nowPos.z - originPos.z);
		float angle = acosf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(start, end)));
		float sinSita = sinf(angle);
		float startPoint = sinf(angle * (1 - t));
		float endPoint = sinf(angle * t);
		DirectX::XMFLOAT3 startFloat3, endFloat3;
		DirectX::XMStoreFloat3(&startFloat3, start);
		DirectX::XMStoreFloat3(&endFloat3, end);
		float len = sqrtf(_start.x * _start.x + _start.y * _start.y + _start.z * _start.z);
		DirectX::XMFLOAT3 out;
		out.x = originPos.x + ((startPoint * startFloat3.x + endPoint * endFloat3.x) / sinSita) * len;
		out.y = originPos.y + ((startPoint * startFloat3.y + endPoint * endFloat3.y) / sinSita) * len;
		out.z = originPos.z + ((startPoint * startFloat3.z + endPoint * endFloat3.z) / sinSita) * len;
		return out;
	}

};