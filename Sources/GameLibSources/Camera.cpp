#include "camera.h"
#include "framework.h"
#include "InputDevice.h"


Camera camera;


Camera::Camera()
{
	Init();
}

void Camera::Init()
{
	pos = originPos;
	target = originTarget;
	up = originUp;
	right = originRight;

	float x = target.x - pos.x;
	float y = target.y - pos.y;
	float z = target.z - pos.z;

	distance = sqrtf(x * x + y * y + z * z);

	float	fov = DirectX::XMConvertToRadians(30.0f);
	float	aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	//SetOrthographicMatrix(50.0f, 50.0f, 0.1f, 100000.0f);
	SetPerspectiveMatrix(fov, aspect, 0.1f, 1000000.0f);

	standard_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 36.0f);

	rotateX = 0.0f;
	rotateY = 0.0f;

	foward.x = target.x - pos.x;
	foward.y = target.y - pos.y;
	foward.z = target.z - pos.z;
}


DirectX::XMMATRIX	Camera::SetOrthographicMatrix(float w, float h, float znear, float zfar)
{
	projection = DirectX::XMMatrixOrthographicLH(w, h, znear, zfar);

	return	projection;
}


DirectX::XMMATRIX	Camera::SetPerspectiveMatrix(float fov, float aspect, float znear, float zfar)
{
	projection = DirectX::XMMatrixPerspectiveFovLH(fov, aspect, znear, zfar);

	return	projection;
}


DirectX::XMMATRIX	Camera::GetViewMatrix()
{
	DirectX::XMVECTOR _pos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
	DirectX::XMVECTOR _target = DirectX::XMVectorSet(target.x, target.y, target.z, 1.0f);
	DirectX::XMVECTOR _up = DirectX::XMVectorSet(up.x, up.y, up.z, 0.0f);

	return	DirectX::XMMatrixLookAtLH(_pos, _target, _up);
}


void Camera::Update()
{
	ImGui::Begin(u8"Camera");

	ImGui::Text("pos.x : %f", pos.x);
	ImGui::Text("pos.y : %f", pos.y);
	ImGui::Text("pos.z : %f", pos.z);

	ImGui::Text("target.x : %f", target.x);
	ImGui::Text("target.y : %f", target.y);
	ImGui::Text("target.z : %f", target.z);

	// ImGui::Text("MOUSE.diMouseState.lX : %f", static_cast<float>(MOUSE.diMouseState.lX));
	// ImGui::Text("MOUSE.diMouseState.lY : %f", static_cast<float>(MOUSE.diMouseState.lY));
	// ImGui::Text("MOUSE.diMouseState.lZ : %f", static_cast<float>(MOUSE.diMouseState.lZ));

	if (ImGui::Button(u8"èâä˙âª"))
	{
		Init();
	}

	ImGui::End();

	POINT cursor;
	GetCursorPos(&cursor);

	oldCursor = newCursor;
	newCursor = DirectX::XMFLOAT2(static_cast<float>(cursor.x), static_cast<float>(cursor.y));

	float moveX = (newCursor.x - oldCursor.x) * 0.02f;
	float moveY = (newCursor.y - oldCursor.y) * 0.02f;

	if (GetKeyState(VK_MENU) < 0)
	{
		if (GetKeyState(VK_LBUTTON) < 0)
		{
			rotateY += moveX * 0.5f;
			rotateX += moveY * 0.5f;
		}
		else if (GetKeyState(VK_MBUTTON) < 0)
		{
			float s = distance * 0.035f;
			float x = moveX * s;
			float y = moveY * s;

			target.x += right.x * x;
			target.y += right.y * x;
			target.z += right.z * x;

			target.x += up.x * y;
			target.y += up.y * y;
			target.z += up.z * y;
		}
		else if (GetKeyState(VK_RBUTTON) < 0)
		{
			distance += (-moveY - moveX) * distance * 0.1f;
		}
		else
		{
			distance -= (float)MOUSE.diMouseState.lZ / 1.0f;
		}
	}

	float xSin = sinf(rotateX);
	float xCos = cosf(rotateX);
	float ySin = sinf(rotateY);
	float yCos = cosf(rotateY);

	DirectX::XMVECTOR front = DirectX::XMVectorSet(-xCos * ySin, -xSin, -xCos * yCos, 0.0f);
	DirectX::XMVECTOR _right = DirectX::XMVectorSet(yCos, 0.0f, -ySin, 0.0f);
	DirectX::XMVECTOR _up = DirectX::XMVector3Cross(_right, front);

	DirectX::XMVECTOR _target = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR _distance = DirectX::XMVectorSet(distance, distance, distance, 0.0f);
	DirectX::XMVECTOR _pos = DirectX::XMVectorSubtract(_target, DirectX::XMVectorMultiply(front, _distance));

	DirectX::XMStoreFloat3(&pos, _pos);
	DirectX::XMStoreFloat3(&up, _up);
	DirectX::XMStoreFloat3(&right, _right);

}

void Camera::PadUpdate()
{
	static float angle = 0.0f;
	angle -= (static_cast<float>(xInput[0].sRX) / 1000.0f);

	pos.x = target.x + 1000.0f * cosf(angle * 0.01745f);
	pos.z = target.z + 1000.0f * sinf(angle * 0.01745f);

	foward.x = target.x - pos.x;
	foward.y = target.y - pos.y;
	foward.z = target.z - pos.z;
}

#define PI 3.14159265358979f
int GetJoystickAngle()
{
	float radian = 0;
	int ans = 0;
	//int mathX = input->Rx*-1;
	//int mathY = input->Ry*-1;
	float mathX = (static_cast<float>(xInput[0].sRX) / 1000.0f) * -1;
	float mathY = (static_cast<float>(xInput[0].sRY) / 1000.0f) * -1;
	radian = atan2(mathX - 0, mathY - 0);
	ans = static_cast<int>((radian * 180) / PI);
	ans += 360;
	ans %= 360;
	return ans;
}