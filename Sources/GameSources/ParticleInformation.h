#pragma once
#include "Model.h"
#include "OBJ3D.h"

#undef max
#undef min

struct TexCoord
{
	float x;
	float y;
	float sx;
	float sy;
	void Set(float _x, float _y, float _sx, float _sy)
	{
		x = _x;
		y = _y;
		sx = _sx;
		sy = _sy;
	}
};

struct Data
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT2 scale;
	TexCoord tex;
	DirectX::XMFLOAT3 angle;
	float alpha;
	float existTime;
	float time;
	bool isExist;
};

struct BuffAreaParticleInfo
{
	Data data;
	DirectX::XMFLOAT3 speed;
};

struct PlayerAttackSlashParticleInfo
{
	Data data;
	float maxScale;
};

struct PlayerAttackSparkParticleInfo
{
	Data data;
	float maxScale;
	DirectX::XMFLOAT3 speed;
	DirectX::XMFLOAT3 accel;
};

struct PlayerAttackAfterImageParticleInfo
{
	Data data;
	float maxScale;
};

struct CrystalDestroyParticleInfo
{
	Data data;
	DirectX::XMFLOAT3 speed;
	DirectX::XMFLOAT3 accel;
	float maxScale;
};

struct SmokeParticleInfo
{
	Data data;
	DirectX::XMFLOAT3 speed;
	float maxScale;
	float originScale;
};

struct ThuderEffectInfo
{
	Data data;
	float originScale;
};

struct UltimetThuderEffectInfo
{
	Data data;
	float originScale;
};

struct UltimetThuderStoneParticle
{
	Data data;
	DirectX::XMFLOAT3 speed;
	float subSpeedY;
	float addAngleZ;
	bool isBreak;
};

struct SparkParticle
{
	Data data;
	DirectX::XMFLOAT3 speed;
	float maxSpeed;
	float subSpeedY;
	float angle;
};

struct SparkAfterImageParticle
{
	Data data;
	float originScale;
};

struct ArrowParticleInfo
{
	Data data;
};

struct Buff
{
	Data data;
	float originScale;
	DirectX::XMFLOAT3 speed;
	DirectX::XMFLOAT4 color;
};
