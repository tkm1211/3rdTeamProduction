#pragma once
#include "Player.h"
#include "Camera.h"
#include "FrameWork.h"


class Enemy;
class CharacterSystem
{
private:
	std::unique_ptr<Player> player;
	std::unique_ptr<Enemy> enemy[10];

public:
	void Init();
	void Update();
	void Draw();
	void UnInit();

	Player* GetPlayerAddress() { return player.get(); }

	static CharacterSystem* GetInstance()
	{
		static CharacterSystem instance;
		return &instance;
	}

};


class Enemy
{
public:
	std::unique_ptr<Model> pEneny;
	std::unique_ptr<CollisionPrimitive> pCylinderCollision;
	OBJ3D enenmyData;
	float radius;

public:
	Enemy() {}
	~Enemy() {}

	void Init(DirectX::XMFLOAT3 _pos)
	{
		pEneny = std::make_unique<Model>("Data/Assets/Model/enemy1.fbx", false);
		enenmyData.Init();
		enenmyData.SetPos(_pos);
		radius = 5.0f;

		pCylinderCollision = std::make_unique<CollisionPrimitive>(CollisionPrimitive::CYLINDER, false, DirectX::XMFLOAT3(75.0f, 10.0f, 0.0f));
		pCylinderCollision->SetPos(_pos);
	}
	void Update()
	{

	}
	void Draw()
	{
		pEneny->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		pEneny->Render(enenmyData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), enenmyData.GetColor(), FrameWork::GetInstance().GetElapsedTime(), radius);

		pCylinderCollision->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime(), true);
	}
	void UnInit()
	{

	}
};