#include "PlayerAttackEffect.h"
#include "FrameWork.h"
#include "Camera.h"
#include "Blender.h"
#include "CameraSystem.h"
#include "CharacterSystem.h"

void PlayerAttackEffect::Init()
{
	texture = std::make_unique<Billboard>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/PlayerEffectAttack.png");
}

void PlayerAttackEffect::Update()
{
	for (auto& e : effects)
	{
		if (!e.startFlag) continue;
		e.elapsedTime++;
		if (e.elapsedTime > e.animationTime)
		{
			e.elapsedTime = 0;
			e.texcoord.x++;
			if (e.texcoord.x > 7)
			{
				e.startFlag = false;
			}
		}
	}
}

void PlayerAttackEffect::Draw()
{
	texture->Begin(FrameWork::GetInstance().GetContext().Get());
	for (auto& e : effects)
	{
		if (!e.startFlag) continue;
		texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			e.pos, 1024 * (int)(e.texcoord.x), 1024 * (int)(e.texcoord.y), 1024, 1024,
			{ 
			e.angle.x /*- CameraSystem::GetInstance()->mainView.GetRotateX()*/, 
			e.angle.y - CameraSystem::GetInstance()->mainView.GetRotateY(),
			e.angle.z /*- CameraSystem::GetInstance()->mainView.GetRotateX() */
			},
			e.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
		//texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		//	e.pos, 1024 * (int)(e.texcoord.x), 1024 * 1, 1024, 1024,
		//	{ 
		//	e.angle.x /*- CameraSystem::GetInstance()->mainView.GetRotateX()*/, 
		//	e.angle.y - CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XMConvertToRadians(90),
		//	e.angle.z /*- CameraSystem::GetInstance()->mainView.GetRotateX() */
		//	},
		//	e.scale, { 1.0f, 1.0f, 1.0f, 1.0f });
	}
	texture->End();
}

void PlayerAttackEffect::UnInit()
{

}

void PlayerAttackEffect::SetEffectInfo(DirectX::XMFLOAT3 _pos, int attackNum)
{
	float playerAngleY = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetAngle().y;

	EffectsInfo temp;
	temp.pos                = _pos;
	temp.elapsedTime  = 0;
	temp.startFlag        = true;
	
	if (attackNum == 0)
	{
		temp.angle                = { DirectX::XMConvertToRadians(-60), DirectX::XMConvertToRadians(270) + playerAngleY, DirectX::XMConvertToRadians(0) };
		temp.scale                 = { 175, 175 };
		temp.animationTime  = 3;
		temp.texcoord           = { 0, 0 };
	}
	else if (attackNum == 1)
	{
		temp.angle                = { DirectX::XMConvertToRadians(85), DirectX::XMConvertToRadians(-30) + playerAngleY, DirectX::XMConvertToRadians(50) };
		temp.scale                 = { 175, 175 };
		temp.animationTime = 3;
		temp.texcoord           = { 0, 0 };
	}
	else if (attackNum == 2)
	{
		temp.angle                = { DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(270) + playerAngleY, DirectX::XMConvertToRadians(0) };
		temp.scale                 = { 175, 175 };
		temp.animationTime = 3;
		temp.texcoord           = { 0, 0 };
	}

	for (auto& e : effects)
	{
		if (e.startFlag) continue;
		e.angle                = temp.angle;
		e.animationTime = temp.animationTime;
		e.elapsedTime     = temp.elapsedTime;
		e.pos                    = temp.pos;
		e.scale                 = temp.scale;
		e.startFlag           = temp.startFlag;
		e.texcoord           = temp.texcoord;
		return;
	}

	effects.push_back(temp);
	return;
}
