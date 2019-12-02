#include "CharacterSystem.h"


void CharacterSystem::Init()
{
	player = std::make_unique<Player>();
	player->Init();

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = std::make_unique<Enemy>();
		DirectX::XMFLOAT3 pos = DirectX::XMFLOAT3(static_cast<float>(rand() % 1000), 0.0f, static_cast<float>(rand() % 1000));
		enemy[i]->Init(pos);
	}
}

void CharacterSystem::UnInit()
{
	player->UnInit();
	for (int i = 0; i < 10; i++)
	{
		enemy[i]->UnInit();
	}
}

void CharacterSystem::Update()
{
	player->Update();
	for (int i = 0; i < 10; i++)
	{
		enemy[i]->Update();
	}

	for (int i = 0; i < 10; i++)
	{
		OBJ3D playerData = player->GetModelData();
		DirectX::XMFLOAT2 _playerPos = { playerData.GetPos().x, playerData.GetPos().z };
		DirectX::XMFLOAT3 _pos = enemy[i]->enenmyData.GetPos();
		if (Collision::CircleVsCircleAndExtrusion(_playerPos, player->pCylinderCollision->GetScale().x,
			DirectX::XMFLOAT2(_pos.x, _pos.z), enemy[i]->pCylinderCollision->GetScale().x / 3.0f))
		{
			player->SetPos(DirectX::XMFLOAT3(_playerPos.x, 0.0f, _playerPos.y));
			player->pCylinderCollision->SetPos(DirectX::XMFLOAT3(_playerPos.x, 0.0f, _playerPos.y));
		}
	}
}

void CharacterSystem::Draw()
{
	player->Draw();
	for (int i = 0; i < 10; i++)
	{
		enemy[i]->Draw();
	}
}