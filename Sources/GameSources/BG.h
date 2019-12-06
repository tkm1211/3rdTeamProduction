#pragma once
#include "Model.h"
#include "OBJ3D.h"

class BG
{

private:
	std::unique_ptr<Model> wall;
	std::unique_ptr<Model> ground;

	OBJ3D modelData;

public:
	BG() {}
	~BG() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

};


DirectX::XMFLOAT3 SphereLinear // 戻り値 : 補間座標
(
	DirectX::XMFLOAT3 _start, // ベクトル
	DirectX::XMFLOAT3 _end,   // ベクトル
	float t					  // 補間値（0.0f ～ 1.0f）
)
{
	DirectX::XMVECTOR start, end;
	start = DirectX::XMVector3Normalize(DirectX::XMVectorSet(_start.x, _start.y, _start.z, 1.0f));
	end = DirectX::XMVector3Normalize(DirectX::XMVectorSet(_end.x, _end.y, _end.z, 1.0f));

	float angle = acosf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(start, end)));

	float sinSita = sinf(angle);

	float startPoint = sinf(angle * (1 - t));
	float endPoint = sinf(angle * t);

	DirectX::XMFLOAT3 startFloat3, endFloat3;
	DirectX::XMStoreFloat3(&startFloat3, start);
	DirectX::XMStoreFloat3(&endFloat3, end);

	float len = sqrtf(_start.x * _start.x + _start.y * _start.y + _start.z * _start.z);

	DirectX::XMFLOAT3 out;
	out.x = ((startPoint * startFloat3.x + endPoint * endFloat3.x) / sinSita) * len;
	out.y = ((startPoint * startFloat3.y + endPoint * endFloat3.y) / sinSita) * len;
	out.z = ((startPoint * startFloat3.z + endPoint * endFloat3.z) / sinSita) * len;

	return out;
}