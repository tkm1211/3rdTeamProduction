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
	// ���̒��S�ƃJ�v�Z���̐����̋����i�̓��j���v�Z�p
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
		int type,							// �Փ˔���̌`�̔ԍ��iCollisionPrimitiveType:: ���j
		bool isCreateBottom,				// ���_�𑫌��ɂ��邩�t���O
		DirectX::XMFLOAT3 _collisionScale	// �Փ˔���̃X�P�[��
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