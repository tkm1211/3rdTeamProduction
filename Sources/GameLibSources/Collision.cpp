#include "Collision.h"
#include "FrameWork.h"

Collision collision;


//******************************************************
//���́@vs�@����
//******************************************************
bool Collision::SphereVsSphere(DirectX::XMFLOAT3 pos1, DirectX::XMFLOAT3 pos2, float r1, float r2)
{
	if ((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) + (pos2.z - pos1.z) * (pos2.z - pos1.z) <= (r1 + r2) * (r1 + r2))
	{
		return true;
	}
	else return false;
}

//******************************************************
//���́@vs�@�J�v�Z��
//******************************************************
bool Collision::SphereVsCapsule(DirectX::XMFLOAT3 sphere, DirectX::XMFLOAT3 capsule1, DirectX::XMFLOAT3 capsule2, float sphere_radius, float capsule_radius)
{
	// ���̒��S�ƃJ�v�Z���̐����̋����i�̓��j���v�Z
	float dis = GetSqDistancePoint2Segment(sphere, capsule1, capsule2);

	// �����i�̓��j�����a�̘a�i�̓��j��菬������Γ������Ă���
	float radius = sphere_radius + capsule_radius;

	if (radius * radius < dis) return false;

	return true;
}
float Collision::GetSqDistancePoint2Segment(DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 seg_start, DirectX::XMFLOAT3 seg_end)
{
	const float eqsilon = 1.0e-5f;	// �덷�z���p�̔����Ȓl

	// �����̎n�_����I�_�ւ̃x�N�g��
	DirectX::XMFLOAT3 segment_sub = DirectX::XMFLOAT3(seg_end.x - seg_start.x, seg_end.y - seg_start.y, seg_end.z - seg_start.z);

	// �����̎n�_����_�ւ̃x�N�g��
	DirectX::XMFLOAT3 segment_point = DirectX::XMFLOAT3(point.x - seg_start.x, point.y - seg_start.y, point.z - seg_start.z);

	// �ˉe�x�N�g��
	DirectX::XMFLOAT3 cross_point;

	// 2�x�N�g���̓���
	float dot = (segment_sub.x * segment_point.x) + (segment_sub.y * segment_point.y) + (segment_sub.z * segment_point.z);
	if (dot < eqsilon)
	{// ���ς����Ȃ�A�����̎n�_���ŋߖT
		return ((segment_point.x * segment_point.x) + (segment_point.y * segment_point.y) + (segment_point.z * segment_point.z));
	}

	// �_��������̏I�_�ւ̃x�N�g��
	segment_point = DirectX::XMFLOAT3(seg_end.x - point.x, seg_end.y - point.y, seg_end.z - point.z);

	// 2�x�N�g���̓���
	dot = (segment_sub.x * segment_point.x) + (segment_sub.y * segment_point.y) + (segment_sub.z * segment_point.z);
	if (dot < eqsilon)
	{// ���ς����Ȃ�A�����̏I�_���ŋߖT
		return ((segment_point.x * segment_point.x) + (segment_point.y * segment_point.y) + (segment_point.z * segment_point.z));
	}

	// ��L�̂ǂ���ɂ��Y�����Ȃ��ꍇ�A������ɗ��Ƃ����ˉe���ŋߖT
	// (�{���Ȃ�T�C���ŋ��߂邪�A�O�ς̑傫��/�����̃x�N�g���̑傫���ŋ��܂�)
	cross_point.x = segment_sub.y * segment_point.z - segment_sub.z * segment_point.y;
	cross_point.y = segment_sub.z * segment_point.x - segment_sub.x * segment_point.z;
	cross_point.z = segment_sub.x * segment_point.y - segment_sub.y * segment_point.x;
	return (((cross_point.x * cross_point.x) + (cross_point.y * cross_point.y) + (cross_point.z * cross_point.z)) 
		/ ((segment_sub.x * segment_sub.x) + (segment_sub.y * segment_sub.y) + (segment_sub.z * segment_sub.z)));
}

//******************************************************
//OBB�@vs�@OBB
//******************************************************
//bool Collision::OBBVsOBB(OBJ3D* obj1, OBJ3D* obj2)
//{
//	DirectX::XMFLOAT3 Nv1_1;
//	DirectX::XMFLOAT3 Nv2_1;
//	DirectX::XMFLOAT3 Nv3_1;
//
//	DirectX::XMFLOAT3 Nv1_2;
//	DirectX::XMFLOAT3 Nv2_2;
//	DirectX::XMFLOAT3 Nv3_2;
//
//
//	DirectX::XMFLOAT3 v1_1;
//	DirectX::XMFLOAT3 v2_1;
//	DirectX::XMFLOAT3 v3_1;
//
//	DirectX::XMFLOAT3 v1_2;
//	DirectX::XMFLOAT3 v2_2;
//	DirectX::XMFLOAT3 v3_2;
//
//
//	//	��]
//	DirectX::XMMATRIX R, Rx, Ry, Rz;
//	DirectX::XMFLOAT4X4 rota, rota2;
//
//	Rx = DirectX::XMMatrixRotationX(obj1->angle.x);				//	X������Ƃ�����]�s��
//	Ry = DirectX::XMMatrixRotationY(obj1->angle.y);				//	Y������Ƃ�����]�s��
//	Rz = DirectX::XMMatrixRotationZ(obj1->angle.z);				//	Z������Ƃ�����]�s��
//	R = DirectX::XMMatrixRotationRollPitchYaw(0, 0, 0);
//	R = Rz * Ry * Rx;
//
//	DirectX::XMStoreFloat4x4(&rota, R);
//
//	// TODO : ��]�s�񂩂�f�[�^����
//	Nv1_1.x = rota._11;
//	Nv1_1.y = rota._12;
//	Nv1_1.z = rota._13;
//
//	Nv2_1.x = rota._21;
//	Nv2_1.y = rota._22;
//	Nv2_1.z = rota._23;
//
//	Nv3_1.x = rota._31;
//	Nv3_1.y = rota._32;
//	Nv3_1.z = rota._33;
//
//
//	Rx = DirectX::XMMatrixRotationX(obj2->angle.x);				//	X������Ƃ�����]�s��
//	Ry = DirectX::XMMatrixRotationY(obj2->angle.y);				//	Y������Ƃ�����]�s��
//	Rz = DirectX::XMMatrixRotationZ(obj2->angle.z);				//	Z������Ƃ�����]�s��
//	R = DirectX::XMMatrixRotationRollPitchYaw(0, 0, 0);
//	R = Rz * Ry * Rx;
//
//	DirectX::XMStoreFloat4x4(&rota2, R);
//
//	Nv1_2.x = rota2._11;
//	Nv1_2.y = rota2._12;
//	Nv1_2.z = rota2._13;
//
//	Nv2_2.x = rota2._21;
//	Nv2_2.y = rota2._22;
//	Nv2_2.z = rota2._23;
//
//	Nv3_2.x = rota2._31;
//	Nv3_2.y = rota2._32;
//	Nv3_2.z = rota2._33;
//
//	// TODO : cube��scale
//	v1_1.x = Nv1_1.x * obj1->collisionScale.x;
//	v1_1.y = Nv1_1.y * obj1->collisionScale.x;
//	v1_1.z = Nv1_1.z * obj1->collisionScale.x;
//
//	v2_1.x = Nv2_1.x * obj1->collisionScale.y;
//	v2_1.y = Nv2_1.y * obj1->collisionScale.y;
//	v2_1.z = Nv2_1.z * obj1->collisionScale.y;
//
//	v3_1.x = Nv3_1.x * obj1->collisionScale.z;
//	v3_1.y = Nv3_1.y * obj1->collisionScale.z;
//	v3_1.z = Nv3_1.z * obj1->collisionScale.z;
//
//	v1_2.x = Nv1_2.x * obj2->collisionScale.x;
//	v1_2.y = Nv1_2.y * obj2->collisionScale.x;
//	v1_2.z = Nv1_2.z * obj2->collisionScale.x;
//
//	v2_2.x = Nv2_2.x * obj2->collisionScale.y;
//	v2_2.y = Nv2_2.y * obj2->collisionScale.y;
//	v2_2.z = Nv2_2.z * obj2->collisionScale.y;
//
//	v3_2.x = Nv3_2.x * obj2->collisionScale.z;
//	v3_2.y = Nv3_2.y * obj2->collisionScale.z;
//	v3_2.z = Nv3_2.z * obj2->collisionScale.z;
//
//
//	DirectX::XMFLOAT3 interval;
//
//	interval.x = (obj1->pos.x + obj1->adjust.x) - (obj2->pos.x + obj2->adjust.x);
//	interval.y = (obj1->pos.y + obj1->adjust.y) - (obj2->pos.y + obj2->adjust.y);
//	interval.z = (obj1->pos.z + obj1->adjust.z) - (obj2->pos.z + obj2->adjust.z);
//
//	// interval.x = obj1->pos.x - obj2->pos.x;
//	// interval.y = obj1->pos.y - obj2->pos.y;
//	// interval.z = obj1->pos.z - obj2->pos.z;
//
//
//	float r1 = 0.0f;
//	float r2 = 0.0f;
//	float l = 0.0f;
//	float dot = 0.0f;
//
//
//	// ������ v1_1
//	r1 = sqrtf((v1_1.x * v1_1.x) + (v1_1.y * v1_1.y) + (v1_1.z * v1_1.z));
//	r2 = LenSegOnSepAxis(&Nv1_1, &v1_2, &v2_2, &v3_2);
//	dot = ((interval.x * Nv1_1.x) + (interval.y * Nv1_1.y) + (interval.z * Nv1_1.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ v2_1
//	r1 = sqrtf((v2_1.x * v2_1.x) + (v2_1.y * v2_1.y) + (v2_1.z * v2_1.z));
//	r2 = LenSegOnSepAxis(&Nv2_1, &v1_2, &v2_2, &v3_2);
//	dot = ((interval.x * Nv2_1.x) + (interval.y * Nv2_1.y) + (interval.z * Nv2_1.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ v3_1
//	r1 = sqrtf((v3_1.x * v3_1.x) + (v3_1.y * v3_1.y) + (v3_1.z * v3_1.z));
//	r2 = LenSegOnSepAxis(&Nv3_1, &v1_2, &v2_2, &v3_2);
//	dot = ((interval.x * Nv3_1.x) + (interval.y * Nv3_1.y) + (interval.z * Nv3_1.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//
//	// ������ v1_2
//	r1 = LenSegOnSepAxis(&Nv1_2, &v1_1, &v2_1, &v3_1);
//	r2 = sqrtf((v1_2.x * v1_2.x) + (v1_2.y * v1_2.y) + (v1_2.z * v1_2.z));
//	dot = ((interval.x * Nv1_2.x) + (interval.y * Nv1_2.y) + (interval.z * Nv1_2.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ v2_2
//	r1 = LenSegOnSepAxis(&Nv2_2, &v1_1, &v2_1, &v3_1);
//	r2 = sqrtf((v2_2.x * v2_2.x) + (v2_2.y * v2_2.y) + (v2_2.z * v2_2.z));
//	dot = ((interval.x * Nv2_2.x) + (interval.y * Nv2_2.y) + (interval.z * Nv2_2.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ v3_2
//	r1 = LenSegOnSepAxis(&Nv3_2, &v1_1, &v2_1, &v3_1);
//	r2 = sqrtf((v3_2.x * v3_2.x) + (v3_2.y * v3_2.y) + (v3_2.z * v3_2.z));
//	dot = ((interval.x * Nv3_2.x) + (interval.y * Nv3_2.y) + (interval.z * Nv3_2.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//
//	DirectX::XMFLOAT3 cross;
//
//	// ������ cross v1_1 + v1_2
//	cross.x = v1_1.y * v1_2.z - v1_1.z * v1_2.y;
//	cross.y = v1_1.z * v1_2.x - v1_1.x * v1_2.z;
//	cross.z = v1_1.x * v1_2.y - v1_1.y * v1_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v2_1, &v3_1);
//	r2 = LenSegOnSepAxis(&cross, &v2_2, &v3_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v1_1 + v2_2
//	cross.x = v1_1.y * v2_2.z - v1_1.z * v2_2.y;
//	cross.y = v1_1.z * v2_2.x - v1_1.x * v2_2.z;
//	cross.z = v1_1.x * v2_2.y - v1_1.y * v2_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v2_1, &v3_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v3_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v1_1 + v3_2
//	cross.x = v1_1.y * v3_2.z - v1_1.z * v3_2.y;
//	cross.y = v1_1.z * v3_2.x - v1_1.x * v3_2.z;
//	cross.z = v1_1.x * v3_2.y - v1_1.y * v3_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v2_1, &v3_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v2_1 + v1_2
//	cross.x = v2_1.y * v1_2.z - v2_1.z * v1_2.y;
//	cross.y = v2_1.z * v1_2.x - v2_1.x * v1_2.z;
//	cross.z = v2_1.x * v1_2.y - v2_1.y * v1_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v1_1, &v3_1);
//	r2 = LenSegOnSepAxis(&cross, &v2_2, &v3_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v2_1 + v2_2
//	cross.x = v2_1.y * v2_2.z - v2_1.z * v2_2.y;
//	cross.y = v2_1.z * v2_2.x - v2_1.x * v2_2.z;
//	cross.z = v2_1.x * v2_2.y - v2_1.y * v2_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v1_1, &v3_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v3_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v2_1 + v3_2
//	cross.x = v2_1.y * v3_2.z - v2_1.z * v3_2.y;
//	cross.y = v2_1.z * v3_2.x - v2_1.x * v3_2.z;
//	cross.z = v2_1.x * v3_2.y - v2_1.y * v3_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v1_1, &v3_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v3_1 + v1_2
//	cross.x = v3_1.y * v1_2.z - v3_1.z * v1_2.y;
//	cross.y = v3_1.z * v1_2.x - v3_1.x * v1_2.z;
//	cross.z = v3_1.x * v1_2.y - v3_1.y * v1_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v1_1, &v2_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v3_1 + v2_2
//	cross.x = v3_1.y * v2_2.z - v3_1.z * v2_2.y;
//	cross.y = v3_1.z * v2_2.x - v3_1.x * v2_2.z;
//	cross.z = v3_1.x * v2_2.y - v3_1.y * v2_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v1_1, &v2_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v3_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//	// ������ cross v3_1 + v3_2
//	cross.x = v3_1.y * v3_2.z - v3_1.z * v3_2.y;
//	cross.y = v3_1.z * v3_2.x - v3_1.x * v3_2.z;
//	cross.z = v3_1.x * v3_2.y - v3_1.y * v3_2.x;
//
//	r1 = LenSegOnSepAxis(&cross, &v1_1, &v2_1);
//	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
//	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
//	l = fabs(dot);
//	if (l > r1 + r2)
//	{
//		return false;
//	}
//
//
//	return true;
//}
//float Collision::LenSegOnSepAxis(DirectX::XMFLOAT3* sep, DirectX::XMFLOAT3* v1, DirectX::XMFLOAT3* v2, DirectX::XMFLOAT3* v3)
//{
//	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
//    // ������Sep�͕W��������Ă��邱��
//	float dot1 = ((sep->x * v1->x) + (sep->y * v1->y) + (sep->z * v1->z));
//	float dot2 = ((sep->x * v2->x) + (sep->y * v2->y) + (sep->z * v2->z));
//	float dot3 = 0.0f;
//	if (!v3)
//	{
//		dot3 = 0.0f;
//	}
//	else
//	{
//		dot3 = ((sep->x * v3->x) + (sep->y * v3->y) + (sep->z * v3->z));
//	}
//
//	float r1 = fabs(dot1);
//	float r2 = fabs(dot2);
//	float r3 = v3 ? (fabs(dot3)) : 0;
//
//	return r1 + r2 + r3;
//}



CollisionPrimitive::CollisionPrimitive( int type, bool isCreateBottom, DirectX::XMFLOAT3 _collisionScale)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device = FrameWork::GetInstance().GetDevice();


	geometricPrimitive = std::make_unique<GeometricPrimitive>( device.Get(), type, isCreateBottom, &_collisionScale );

	scale = collisionScale = _collisionScale;
	color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
}

void CollisionPrimitive::Render
 (  const DirectX::XMMATRIX& view,
	const DirectX::XMMATRIX& projection,
	const DirectX::XMFLOAT4& lightDirection,
	float elapsedTime )
{

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = FrameWork::GetInstance().GetContext();

	//	���[���h�ϊ��s��擾
	DirectX::XMMATRIX worldM = GetWorldMatrix();

	//	Matrix -> Float4x4 �ϊ�
	DirectX::XMFLOAT4X4 wvp;
	DirectX::XMFLOAT4X4 world;

	DirectX::XMStoreFloat4x4(&wvp, worldM * view * projection);
	DirectX::XMStoreFloat4x4(&world, worldM);

	//	�`��
	if (geometricPrimitive)
	{
		geometricPrimitive->Render(immediateContext.Get(), wvp, world, lightDirection, color, false);
	}

}