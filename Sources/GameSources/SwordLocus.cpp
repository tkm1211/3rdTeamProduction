#include "SwordLocus.h"
#include "CameraSystem.h"
#include "FrameWork.h"

void SwordLocus::Init()
{
	// geometry collision
	for (int i = 0; i < 10; i++)
	{
		ci[i].handPoint = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
		ci[i].handPoint->SetColor({ 1, 0, 0, 1 });

		ci[i].swordPoint = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
		ci[i].swordPoint->SetColor({ 0, 0, 1, 1 });
	}
}

void SwordLocus::Update()
{

}

void SwordLocus::Draw()
{
	for (int i = 0; i < 10; i++)
	{
		ci[i].handPoint->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		ci[i].swordPoint->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	}
}

void SwordLocus::UnInit()
{

}