#include "EnemyManager.h"
#include "Model.h"
#include "FrameWork.h"
#include "Camera.h"
#include "directxmath.h"
#include "CameraSystem.h"


#define PLAYER_SPEED 10
_Player _player;


EnemyManager::EnemyManager()
{
	pWarker = std::make_unique<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);
	pEliteWarker = std::make_unique<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);
	pArcher = std::make_unique<Model>("Data/Assets/Model/Enemys/Archer.fbx", false);
	pPlayer = std::make_unique<Model>("Data/Assets/Model/Player/Player.fbx", false);

	archer.emplace_back();
	warker.emplace_back();
	eliteWarker.emplace_back();

	for (auto &ewrk : eliteWarker)
	{
		ewrk.GetModelData()->SetScale(DirectX::XMFLOAT3(5, 5, 5));
	}
	for (auto &arc : archer)
	{
		enmList.emplace_back(arc.GetModelData());
	}
	for (auto &wrk : warker)
	{
		enmList.emplace_back(wrk.GetModelData());
	}
	for (auto &ewrk : eliteWarker)
	{
		enmList.emplace_back(ewrk.GetModelData());
	}
	/*enowCatch.resize(enmList.size());*/
}

void EnemyManager::Update()
{
	if (GetAsyncKeyState(VK_UP) < 0)
	{
		_player.pos.z += PLAYER_SPEED;
	}
	if (GetAsyncKeyState(VK_DOWN) < 0)
	{
		_player.pos.z -= PLAYER_SPEED;
	}
	if (GetAsyncKeyState(VK_RIGHT) < 0)
	{
		_player.pos.x += PLAYER_SPEED;
	}
	if (GetAsyncKeyState(VK_LEFT) < 0)
	{
		_player.pos.x -= PLAYER_SPEED;
	}

	for (auto &arc : archer)
	{
		arc.Update();
	}
	for (auto &wrk : warker)
	{
		wrk.Update();
	}
	for (auto &ewrk : eliteWarker)
	{
		ewrk.Update();
	}
}

void EnemyManager::Draw()
{
	pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	for (auto &arc : archer)
	{
		pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0,1,0,1), DirectX::XMFLOAT4(1,1,1,1), FrameWork::GetInstance().GetElapsedTime());
		if (arc.GetNowShot())
		{
			pShot->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pShot->Render(arc.GetArrow()->GetModelData().GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		}
	}
	pWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	for (auto &wrk : warker)
	{
		pWarker->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
	}
	pEliteWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	for (auto &ewrk : eliteWarker)
	{
		pEliteWarker->Render(ewrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
	}
	pPlayer->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);

	DirectX::XMMATRIX worldM;

	DirectX::XMMATRIX scaleM, rotateM, translateM;
	{
		scaleM = DirectX::XMMatrixScaling(_player.scale.x, _player.scale.y, _player.scale.z);
		rotateM = DirectX::XMMatrixRotationRollPitchYaw(_player.rotate.x, _player.rotate.y, _player.rotate.z);
		translateM = DirectX::XMMatrixTranslation(_player.pos.x, _player.pos.y, _player.pos.z);

		worldM = scaleM * rotateM*translateM;
	}
	pPlayer->Render(worldM, CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
}

void EnemyManager::ImGui()
{
	ImGui::Begin("EnemyManager");
	{

		if (ImGui::Button("Create"))
		{
			
		}

	}
	ImGui::End();
}
