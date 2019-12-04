#pragma once

#include "Scene.h"
#include "Model.h"
#include "OBJ3D.h"
#include "PlayerTemplate.h"
#include "Collision.h"
#include "Billboard.h"


class SceneLabo : public Scene
{
private:
	PlayerTemplate player;
	std::unique_ptr<Model> pPlayer;
	OBJ3D playerData;
	float radius;

	std::unique_ptr<Model> pItem;
	OBJ3D itemData;

	std::unique_ptr<CollisionPrimitive> pPlayerCube;
	std::unique_ptr<CollisionPrimitive> pGroundCube;

	std::unique_ptr<CollisionPrimitive> pPlayerCylinder;
	std::unique_ptr<CollisionPrimitive> pGroundCylinder;

	std::unique_ptr<Billboard> particle;

	struct ParticleData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 texPos;
		DirectX::XMFLOAT3 texSize;
		DirectX::XMFLOAT2 scale;
	};
	ParticleData particleData;

public:
	void Init();
	void UnInit();
	void Update();
	void Render();
	void ImGui();
};