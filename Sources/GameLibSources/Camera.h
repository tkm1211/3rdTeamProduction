#pragma once

#include	<DirectXMath.h>


class Camera
{
private:
	const DirectX::XMFLOAT3	originPos = DirectX::XMFLOAT3(0.0f, 500.0f, 41.0f);
	const DirectX::XMFLOAT3	originTarget = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	const DirectX::XMFLOAT3	originUp = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	const DirectX::XMFLOAT3	originRight = DirectX::XMFLOAT3(1.0f, 0.0f, 0.0f);

	DirectX::XMFLOAT3	standard_pos;
	DirectX::XMFLOAT3	pos;
	DirectX::XMFLOAT3	up;
	DirectX::XMFLOAT3	right;
	DirectX::XMMATRIX	projection;

	DirectX::XMFLOAT2 oldCursor;
	DirectX::XMFLOAT2 newCursor;

	float rotateX;
	float rotateY;

	float distance;

public:
	DirectX::XMFLOAT3	target;
	DirectX::XMFLOAT3	foward;

public:
	Camera();

	void Init();
	void Update();
	void PadUpdate();

public:
	DirectX::XMMATRIX	SetOrthographicMatrix( float w, float h, float znear, float zfar );
	DirectX::XMMATRIX	SetPerspectiveMatrix( float fov, float aspect, float znear, float zfar );
	DirectX::XMMATRIX	GetViewMatrix();
	DirectX::XMMATRIX	GetProjectionMatrix(){ return	projection; }
	DirectX::XMFLOAT3	GetPos() { return pos; }

	void Set(DirectX::XMFLOAT3 _pos, DirectX::XMFLOAT3 _target, DirectX::XMFLOAT3 _up)
	{
		pos = _pos;
		target = _target;
		up = _up;
	}
	void SetRotateX(float _rotateX) { rotateX = _rotateX; }
	void SetRotateY(float _rotateY) { rotateY = _rotateY; }
};

int GetJoystickAngle();
extern Camera camera;