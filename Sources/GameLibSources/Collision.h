#pragma once

#include <DirectXMath.h>
#include <memory>

#include "OBJ3D.h"
#include "GeometricPrimitive.h"


class Collision
{
public:
	bool SphereVsSphere(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, float r1, float r2);
	bool SphereVsCapsule(DirectX::XMFLOAT3 sphere, DirectX::XMFLOAT3 capsule1, DirectX::XMFLOAT3 capsule2, float sphere_radius, float capsule_radius);
//	bool OBBVsOBB(OBJ3D* obj1, OBJ3D* obj2);

private:
	// 球の中心とカプセルの線分の距離（の二乗）を計算用
	float GetSqDistancePoint2Segment(DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 seg_start, DirectX::XMFLOAT3 seg_end);
//	float LenSegOnSepAxis(DirectX::XMFLOAT3* sep, DirectX::XMFLOAT3* v1, DirectX::XMFLOAT3* v2, DirectX::XMFLOAT3* v3 = 0);
};

extern Collision collision;


class CollisionPrimitive : public OBJ3D
{
private:
	std::unique_ptr<GeometricPrimitive> geometricPrimitive;

	DirectX::XMFLOAT3 collisionScale;

public:
	CollisionPrimitive() : geometricPrimitive( nullptr ) {}

	enum CollisionPrimitiveType { CUBE, SPHERE, CYLINDER };
	CollisionPrimitive
	(
		int type,							// 衝突判定の形の番号（CollisionPrimitiveType:: より）
		bool isCreateBottom,				// 原点を足元にするかフラグ
		DirectX::XMFLOAT3 _collisionScale	// 衝突判定のスケール
	);

	~CollisionPrimitive()
	{
		if (geometricPrimitive)
		{
			geometricPrimitive = nullptr;
		}
	}

	void Render
	(
		const DirectX::XMMATRIX& view,
		const DirectX::XMMATRIX& projection,
		const DirectX::XMFLOAT4& lightDirection,
		float elapsedTime
	);

};