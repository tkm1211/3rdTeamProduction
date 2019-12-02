#include "Collision.h"
#include "FrameWork.h"

Collision collision;


//******************************************************
//球体　vs　球体
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
//球体　vs　カプセル
//******************************************************
bool Collision::SphereVsCapsule(DirectX::XMFLOAT3& capsule1, DirectX::XMFLOAT3 capsule2, float capsule_radius, DirectX::XMFLOAT3 sphere, float sphere_radius)
{
	// 球の中心とカプセルの線分の距離（の二乗）を計算
	DirectX::XMFLOAT3 dir;
	float dis = GetSqDistancePoint2Segment(sphere, capsule1, capsule2, dir);

	// 距離（の二乗）が半径の和（の二乗）より小さければ当たっている
	float radius = sphere_radius + capsule_radius;

	if (radius * radius < dis) return false;
	if (dis == 0.0f) return false;
	if (dir.x == 0.0f && dir.y == 0.0f && dir.z == 0.0f) return false;

	float length = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);

	dir.x /= length;
	dir.y /= length;
	dir.z /= length;

	capsule1.x = sphere.x + radius * dir.x;
	capsule1.y = sphere.y + radius * dir.y;
	capsule1.z = sphere.z + radius * dir.z;

	return true;
}
float Collision::GetSqDistancePoint2Segment(DirectX::XMFLOAT3 point, DirectX::XMFLOAT3 seg_start, DirectX::XMFLOAT3 seg_end, DirectX::XMFLOAT3& dir)
{
	const float eqsilon = 1.0e-5f;	// 誤差吸収用の微小な値

	// 線分の始点から終点へのベクトル
	DirectX::XMFLOAT3 segment_sub = DirectX::XMFLOAT3(seg_end.x - seg_start.x, seg_end.y - seg_start.y, seg_end.z - seg_start.z);

	// 線分の始点から点へのベクトル
	DirectX::XMFLOAT3 segment_point = DirectX::XMFLOAT3(point.x - seg_start.x, point.y - seg_start.y, point.z - seg_start.z);
	dir = segment_point;

	// 射影ベクトル
	DirectX::XMFLOAT3 cross_point;

	// 2ベクトルの内積
	float dot = (segment_sub.x * segment_point.x) + (segment_sub.y * segment_point.y) + (segment_sub.z * segment_point.z);
	if (dot < eqsilon)
	{// 内積が負なら、線分の始点が最近傍
		return ((segment_point.x * segment_point.x) + (segment_point.y * segment_point.y) + (segment_point.z * segment_point.z));
	}

	// 点から線分の終点へのベクトル
	segment_point = DirectX::XMFLOAT3(seg_end.x - point.x, seg_end.y - point.y, seg_end.z - point.z);

	// 2ベクトルの内積
	dot = (segment_sub.x * segment_point.x) + (segment_sub.y * segment_point.y) + (segment_sub.z * segment_point.z);
	if (dot < eqsilon)
	{// 内積が負なら、線分の終点が最近傍
		return ((segment_point.x * segment_point.x) + (segment_point.y * segment_point.y) + (segment_point.z * segment_point.z));
	}

	// 上記のどちらにも該当しない場合、線分上に落とした射影が最近傍
	// (本来ならサインで求めるが、外積の大きさ/線分のベクトルの大きさで求まる)
	cross_point.x = segment_sub.y * segment_point.z - segment_sub.z * segment_point.y;
	cross_point.y = segment_sub.z * segment_point.x - segment_sub.x * segment_point.z;
	cross_point.z = segment_sub.x * segment_point.y - segment_sub.y * segment_point.x;
	dir = segment_sub;
	return (((cross_point.x * cross_point.x) + (cross_point.y * cross_point.y) + (cross_point.z * cross_point.z)) 
		/ ((segment_sub.x * segment_sub.x) + (segment_sub.y * segment_sub.y) + (segment_sub.z * segment_sub.z)));
}

//******************************************************
//OBB　vs　OBB
//******************************************************
bool Collision::OBBVsOBB(OBJ3D* obj1, OBJ3D* obj2)
{
	DirectX::XMFLOAT3 Nv1_1;
	DirectX::XMFLOAT3 Nv2_1;
	DirectX::XMFLOAT3 Nv3_1;

	DirectX::XMFLOAT3 Nv1_2;
	DirectX::XMFLOAT3 Nv2_2;
	DirectX::XMFLOAT3 Nv3_2;


	DirectX::XMFLOAT3 v1_1;
	DirectX::XMFLOAT3 v2_1;
	DirectX::XMFLOAT3 v3_1;

	DirectX::XMFLOAT3 v1_2;
	DirectX::XMFLOAT3 v2_2;
	DirectX::XMFLOAT3 v3_2;


	//	回転
	DirectX::XMFLOAT4X4 rota;

	DirectX::XMStoreFloat4x4(&rota, obj1->GetWorldMatrix());

	Nv1_1.x = rota._11;
	Nv1_1.y = rota._12;
	Nv1_1.z = rota._13;

	Nv2_1.x = rota._21;
	Nv2_1.y = rota._22;
	Nv2_1.z = rota._23;

	Nv3_1.x = rota._31;
	Nv3_1.y = rota._32;
	Nv3_1.z = rota._33;

	DirectX::XMStoreFloat4x4(&rota, obj2->GetWorldMatrix());

	Nv1_2.x = rota._11;
	Nv1_2.y = rota._12;
	Nv1_2.z = rota._13;

	Nv2_2.x = rota._21;
	Nv2_2.y = rota._22;
	Nv2_2.z = rota._23;

	Nv3_2.x = rota._31;
	Nv3_2.y = rota._32;
	Nv3_2.z = rota._33;


	DirectX::XMFLOAT3 scale = obj1->GetScale();

	v1_1.x = Nv1_1.x * scale.x / 2.0f;
	v1_1.y = Nv1_1.y * scale.x / 2.0f;
	v1_1.z = Nv1_1.z * scale.x / 2.0f;

	v2_1.x = Nv2_1.x * scale.y / 2.0f;
	v2_1.y = Nv2_1.y * scale.y / 2.0f;
	v2_1.z = Nv2_1.z * scale.y / 2.0f;

	v3_1.x = Nv3_1.x * scale.z / 2.0f;
	v3_1.y = Nv3_1.y * scale.z / 2.0f;
	v3_1.z = Nv3_1.z * scale.z / 2.0f;

	scale = obj2->GetScale();

	v1_2.x = Nv1_2.x * scale.x / 2.0f;
	v1_2.y = Nv1_2.y * scale.x / 2.0f;
	v1_2.z = Nv1_2.z * scale.x / 2.0f;

	v2_2.x = Nv2_2.x * scale.y / 2.0f;
	v2_2.y = Nv2_2.y * scale.y / 2.0f;
	v2_2.z = Nv2_2.z * scale.y / 2.0f;

	v3_2.x = Nv3_2.x * scale.z / 2.0f;
	v3_2.y = Nv3_2.y * scale.z / 2.0f;
	v3_2.z = Nv3_2.z * scale.z / 2.0f;


	DirectX::XMFLOAT3 interval;
	DirectX::XMFLOAT3 pos1 = obj1->GetPos();
	DirectX::XMFLOAT3 pos2 = obj2->GetPos();

	interval.x = pos1.x - pos2.x;
	interval.y = pos1.y - pos2.y;
	interval.z = pos1.z - pos2.z;

	float r1 = 0.0f;
	float r2 = 0.0f;
	float l = 0.0f;
	float dot = 0.0f;


	// 分離軸 v1_1
	r1 = sqrtf((v1_1.x * v1_1.x) + (v1_1.y * v1_1.y) + (v1_1.z * v1_1.z));
	r2 = LenSegOnSepAxis(&Nv1_1, &v1_2, &v2_2, &v3_2);
	dot = ((interval.x * Nv1_1.x) + (interval.y * Nv1_1.y) + (interval.z * Nv1_1.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 v2_1
	r1 = sqrtf((v2_1.x * v2_1.x) + (v2_1.y * v2_1.y) + (v2_1.z * v2_1.z));
	r2 = LenSegOnSepAxis(&Nv2_1, &v1_2, &v2_2, &v3_2);
	dot = ((interval.x * Nv2_1.x) + (interval.y * Nv2_1.y) + (interval.z * Nv2_1.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 v3_1
	r1 = sqrtf((v3_1.x * v3_1.x) + (v3_1.y * v3_1.y) + (v3_1.z * v3_1.z));
	r2 = LenSegOnSepAxis(&Nv3_1, &v1_2, &v2_2, &v3_2);
	dot = ((interval.x * Nv3_1.x) + (interval.y * Nv3_1.y) + (interval.z * Nv3_1.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}


	// 分離軸 v1_2
	r1 = LenSegOnSepAxis(&Nv1_2, &v1_1, &v2_1, &v3_1);
	r2 = sqrtf((v1_2.x * v1_2.x) + (v1_2.y * v1_2.y) + (v1_2.z * v1_2.z));
	dot = ((interval.x * Nv1_2.x) + (interval.y * Nv1_2.y) + (interval.z * Nv1_2.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 v2_2
	r1 = LenSegOnSepAxis(&Nv2_2, &v1_1, &v2_1, &v3_1);
	r2 = sqrtf((v2_2.x * v2_2.x) + (v2_2.y * v2_2.y) + (v2_2.z * v2_2.z));
	dot = ((interval.x * Nv2_2.x) + (interval.y * Nv2_2.y) + (interval.z * Nv2_2.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 v3_2
	r1 = LenSegOnSepAxis(&Nv3_2, &v1_1, &v2_1, &v3_1);
	r2 = sqrtf((v3_2.x * v3_2.x) + (v3_2.y * v3_2.y) + (v3_2.z * v3_2.z));
	dot = ((interval.x * Nv3_2.x) + (interval.y * Nv3_2.y) + (interval.z * Nv3_2.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}


	DirectX::XMFLOAT3 cross;

	// 分離軸 cross v1_1 + v1_2
	cross.x = v1_1.y * v1_2.z - v1_1.z * v1_2.y;
	cross.y = v1_1.z * v1_2.x - v1_1.x * v1_2.z;
	cross.z = v1_1.x * v1_2.y - v1_1.y * v1_2.x;

	r1 = LenSegOnSepAxis(&cross, &v2_1, &v3_1);
	r2 = LenSegOnSepAxis(&cross, &v2_2, &v3_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v1_1 + v2_2
	cross.x = v1_1.y * v2_2.z - v1_1.z * v2_2.y;
	cross.y = v1_1.z * v2_2.x - v1_1.x * v2_2.z;
	cross.z = v1_1.x * v2_2.y - v1_1.y * v2_2.x;

	r1 = LenSegOnSepAxis(&cross, &v2_1, &v3_1);
	r2 = LenSegOnSepAxis(&cross, &v1_2, &v3_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v1_1 + v3_2
	cross.x = v1_1.y * v3_2.z - v1_1.z * v3_2.y;
	cross.y = v1_1.z * v3_2.x - v1_1.x * v3_2.z;
	cross.z = v1_1.x * v3_2.y - v1_1.y * v3_2.x;

	r1 = LenSegOnSepAxis(&cross, &v2_1, &v3_1);
	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v2_1 + v1_2
	cross.x = v2_1.y * v1_2.z - v2_1.z * v1_2.y;
	cross.y = v2_1.z * v1_2.x - v2_1.x * v1_2.z;
	cross.z = v2_1.x * v1_2.y - v2_1.y * v1_2.x;

	r1 = LenSegOnSepAxis(&cross, &v1_1, &v3_1);
	r2 = LenSegOnSepAxis(&cross, &v2_2, &v3_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v2_1 + v2_2
	cross.x = v2_1.y * v2_2.z - v2_1.z * v2_2.y;
	cross.y = v2_1.z * v2_2.x - v2_1.x * v2_2.z;
	cross.z = v2_1.x * v2_2.y - v2_1.y * v2_2.x;

	r1 = LenSegOnSepAxis(&cross, &v1_1, &v3_1);
	r2 = LenSegOnSepAxis(&cross, &v1_2, &v3_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v2_1 + v3_2
	cross.x = v2_1.y * v3_2.z - v2_1.z * v3_2.y;
	cross.y = v2_1.z * v3_2.x - v2_1.x * v3_2.z;
	cross.z = v2_1.x * v3_2.y - v2_1.y * v3_2.x;

	r1 = LenSegOnSepAxis(&cross, &v1_1, &v3_1);
	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v3_1 + v1_2
	cross.x = v3_1.y * v1_2.z - v3_1.z * v1_2.y;
	cross.y = v3_1.z * v1_2.x - v3_1.x * v1_2.z;
	cross.z = v3_1.x * v1_2.y - v3_1.y * v1_2.x;

	r1 = LenSegOnSepAxis(&cross, &v1_1, &v2_1);
	r2 = LenSegOnSepAxis(&cross, &v2_2, &v3_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v3_1 + v2_2
	cross.x = v3_1.y * v2_2.z - v3_1.z * v2_2.y;
	cross.y = v3_1.z * v2_2.x - v3_1.x * v2_2.z;
	cross.z = v3_1.x * v2_2.y - v3_1.y * v2_2.x;

	r1 = LenSegOnSepAxis(&cross, &v1_1, &v2_1);
	r2 = LenSegOnSepAxis(&cross, &v1_2, &v3_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}

	// 分離軸 cross v3_1 + v3_2
	cross.x = v3_1.y * v3_2.z - v3_1.z * v3_2.y;
	cross.y = v3_1.z * v3_2.x - v3_1.x * v3_2.z;
	cross.z = v3_1.x * v3_2.y - v3_1.y * v3_2.x;

	r1 = LenSegOnSepAxis(&cross, &v1_1, &v2_1);
	r2 = LenSegOnSepAxis(&cross, &v1_2, &v2_2);
	dot = ((interval.x * cross.x) + (interval.y * cross.y) + (interval.z * cross.z));
	l = fabs(dot);
	if (l > r1 + r2)
	{
		return false;
	}


	return true;
}
float Collision::LenSegOnSepAxis(DirectX::XMFLOAT3* sep, DirectX::XMFLOAT3* v1, DirectX::XMFLOAT3* v2, DirectX::XMFLOAT3* v3)
{
	// 3つの内積の絶対値の和で投影線分長を計算
    // 分離軸Sepは標準化されていること
	float dot1 = ((sep->x * v1->x) + (sep->y * v1->y) + (sep->z * v1->z));
	float dot2 = ((sep->x * v2->x) + (sep->y * v2->y) + (sep->z * v2->z));
	float dot3 = 0.0f;
	if (!v3)
	{
		dot3 = 0.0f;
	}
	else
	{
		dot3 = ((sep->x * v3->x) + (sep->y * v3->y) + (sep->z * v3->z));
	}

	float r1 = fabs(dot1);
	float r2 = fabs(dot2);
	float r3 = v3 ? (fabs(dot3)) : 0;

	return r1 + r2 + r3;
}

//******************************************************
//矩形　vs　矩形
//******************************************************
bool Collision::RectVsRectAndExtrusion(DirectX::XMFLOAT2& pos1, DirectX::XMFLOAT2 scale1, DirectX::XMFLOAT2 pos2, DirectX::XMFLOAT2 scale2)
{
	bool isHit = false;

	if (pos1.x - scale1.x <= pos2.x - scale2.x)
	{
		pos1.x = pos2.x - scale2.x + scale1.x;
		isHit = true;
	}
	if (pos2.x + scale2.x <= pos1.x + scale1.x)
	{
		pos1.x = pos2.x + scale2.x - scale1.x;
		isHit = true;
	}
	if (pos1.y - scale1.y <= pos2.y - scale2.y)
	{
		pos1.y = pos2.y - scale2.y + scale1.y;
		isHit = true;
	}
	if (pos2.y + scale2.y <= pos1.y + scale1.y)
	{
		pos1.y = pos2.y + scale2.y - scale1.y;
		isHit = true;
	}

	return isHit;
}

//******************************************************
//円　vs　円
//******************************************************
bool Collision::CircleVsCircleAndExtrusion(DirectX::XMFLOAT2& pos1, float radius1, DirectX::XMFLOAT2 pos2, float radius2)
{
	if ((pos2.x - pos1.x) * (pos2.x - pos1.x) + (pos2.y - pos1.y) * (pos2.y - pos1.y) <= (radius1 + radius2) * (radius1 + radius2))
	{
		DirectX::XMFLOAT2 dir = { pos1.x - pos2.x, pos1.y - pos2.y };
		float length = sqrtf(dir.x * dir.x + dir.y * dir.y);

		dir.x /= length;
		dir.y /= length;

		pos1.x = pos2.x + (radius1 + radius2) * dir.x;
		pos1.y = pos2.y + (radius1 + radius2) * dir.y;

		return true;
	}
	else return false;
}

//******************************************************
//カプセル　vs　円
//******************************************************
//bool Collision::CapsuleVsCircleAndExtrusion(DirectX::XMFLOAT3& nowPos1, DirectX::XMFLOAT3 oldPos1, float radius1, DirectX::XMFLOAT3 pos2, float radius2)
//{
//	/*if ((pos2.x - nowPos1.x) * (pos2.x - nowPos1.x) + (pos2.z - nowPos1.z) * (pos2.z - nowPos1.z) <= (radius1 + radius2) * (radius1 + radius2))
//	{
//		DirectX::XMFLOAT2 dir = { oldPos1.x - pos2.x, oldPos1.z - pos2.z };
//		float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
//
//		dir.x /= length;
//		dir.y /= length;
//
//		nowPos1.x = pos2.x + (radius1 + radius2) * dir.x;
//		nowPos1.z = pos2.z + (radius1 + radius2) * dir.y;
//
//		return true;
//	}*/
//	if ((pos2.x - oldPos1.x) * (pos2.x - oldPos1.x) + (pos2.z - oldPos1.z) * (pos2.z - oldPos1.z) <= (radius1 + radius2) * (radius1 + radius2))
//	{
//		DirectX::XMFLOAT2 dir = { oldPos1.x - pos2.x, oldPos1.z - pos2.z };
//		float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
//
//		dir.x /= length;
//		dir.y /= length;
//
//		nowPos1.x = pos2.x + (radius1 + radius2) * dir.x;
//		nowPos1.z = pos2.z + (radius1 + radius2) * dir.y;
//
//		return true;
//	}
//	else
//	{
//		DirectX::XMFLOAT2 dir = { nowPos1.x - oldPos1.x, nowPos1.z - oldPos1.z };
//		float length = sqrtf(dir.x * dir.x + dir.y * dir.y);
//
//		if (length <= 0.0f) return false;
//
//		DirectX::XMFLOAT3 frontVec = { dir.x / length, 0.0f, dir.y / length };
//		DirectX::XMFLOAT3 upVec = { 0.0f, 1.0f, 0.0f };
//		DirectX::XMFLOAT3 rightVec;
//		rightVec.x = upVec.y * frontVec.z - upVec.z * frontVec.y;
//		rightVec.y = upVec.z * frontVec.x - upVec.x * frontVec.z;
//		rightVec.z = upVec.x * frontVec.y - upVec.y * frontVec.x;
//
//		DirectX::XMFLOAT3 rey = { dir.x, 0.0f, dir.y };
//		DirectX::XMFLOAT3 rightPoint = { rightVec.x * radius1, 0.0f, rightVec.z * radius1 };
//		DirectX::XMFLOAT3 leftPoint = { rightVec.x * radius1 * -1, 0.0f, rightVec.z * radius1 * -1 };
//
//
//	}
//}


CollisionPrimitive::CollisionPrimitive( int type, bool isCreateBottom, DirectX::XMFLOAT3 _collisionScale)
{
	Microsoft::WRL::ComPtr<ID3D11Device> device = FrameWork::GetInstance().GetDevice();

	primitiveType = type;
	geometricPrimitive = std::make_unique<GeometricPrimitive>( device.Get(), type, isCreateBottom, &_collisionScale );

	collisionScale = _collisionScale;
	if (type == CollisionPrimitiveType::CYLINDER)
	{
		scale.x = _collisionScale.x;
		scale.z = _collisionScale.x;
		scale.y = _collisionScale.y;
	}
	color = DirectX::XMFLOAT4(0.2f, 0.8f, 0.45f, 1.0f);
}

void CollisionPrimitive::Render
 (  const DirectX::XMMATRIX& view,
	const DirectX::XMMATRIX& projection,
	const DirectX::XMFLOAT4& lightDirection,
	float elapsedTime,
	bool bSolid )
{

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = FrameWork::GetInstance().GetContext();

	//	ワールド変換行列取得
	DirectX::XMMATRIX worldM;
	if (primitiveType == CollisionPrimitiveType::CYLINDER)
	{
		scale.x += 15.0f;
		scale.z += 15.0f;

		worldM = GetWorldMatrix();

		scale.x -= 15.0f;
		scale.z -= 15.0f;
	}
	else
	{
		worldM = GetWorldMatrix();
	}

	//	Matrix -> Float4x4 変換
	DirectX::XMFLOAT4X4 wvp;
	DirectX::XMFLOAT4X4 world;

	DirectX::XMStoreFloat4x4(&wvp, worldM * view * projection);
	DirectX::XMStoreFloat4x4(&world, worldM);

	//	描画
	if (geometricPrimitive)
	{
		geometricPrimitive->Render(immediateContext.Get(), wvp, world, lightDirection, color, bSolid);
	}

}