#pragma once
#include "Camera.h"


class CameraControl
{
public:
	static void MouseControlUpdate( Camera* camera );
	static void PadControlUpdate( Camera* camera );
	static void AddSpeedUpdate( Camera* camera, DirectX::XMFLOAT3 _speed );
	static void CameraRotation( Camera* camera );
};