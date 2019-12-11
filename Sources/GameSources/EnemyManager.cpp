#include "EnemyManager.h"
#include "Model.h"
#include "FrameWork.h"
#include "Camera.h"
#include "directxmath.h"
#include "CameraSystem.h"
#include "Editer.h"
#include "Collision.h"
#include "ArcherKokim.h"
#include "Shot.h"
#include "WaveManager.h"
#include "Wave.h"
#define PLAYER_SPEED 10
_Player _player;


EnemyManager::EnemyManager()
{
	{
		pWarker = std::make_unique<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);
		pWarkerAttack = std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerAttack.fbx", false);
		pWarkerRun = std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerRun.fbx", false);
	}
	pEliteWarker = std::make_unique<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);

	{
		pArcher = std::make_unique<Model>("Data/Assets/Model/Enemys/Archer.fbx", false);
		pShot = std::make_unique<Model>("Data/Assets/Model/Enemys/Arrow.fbx", false);
	}
	pPlayer = std::make_unique<Model>("Data/Assets/Model/Player/Player.fbx", false);

	waveMgr = std::make_unique<WaveManager>();

	///*enowCatch.resize(enmList.size());*/

	pWarkerRun->StartAnimation(0, true);

	//pWarkerAttack->GetVectexPos("polySurface4", );

	waveMgr->GetWaves().emplace_back();
}

EnemyManager::~EnemyManager()
{


};

void EnemyManager::Update()
{
	if (Editer::GetInstance()->GetNowEditer())
	{
		
	}
	else
	{
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).Update();
	}
	/*if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimerMax() < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimer())
	{
		waveMgr->GetWaves().emplace_back();
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).SetTimer(0);
		waveMgr->GetWaveNowIndex()++;
		
	}*/

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


	ImGui();
}

void EnemyManager::Draw()
{
	
	if (Editer::GetInstance()->GetNowEditer())
	{
		pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		{
			pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());

		}

		pWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			pWarker->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		}

		pEliteWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
		{
			pEliteWarker->Render(ewrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		}

		/*for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		{
			arc.GetBodyCollision()->Render(CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			wrk.GetBodyCollision()->Render(CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
		{
			ewrk.GetBodyCollision()->Render(CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}*/
	}
	else
	{
		pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		{
			pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			if (arc.GetArrow())
			{
				pShot->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
				pShot->Render(arc.GetArrow()->GetModelData().GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			}
		}

		WarkerRenderer();

		pEliteWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
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

		/*for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		{
			arc.GetBodyCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			wrk.GetBodyCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
		{
			ewrk.GetBodyCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}*/
	}

}

void EnemyManager::WarkerRenderer()
{
	for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
	{
		switch (wrk.GetState())
		{
		case WARKER_STATE::RUN:
			pWarkerRun->StartAnimation(0, true);
			pWarkerRun->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pWarkerRun->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;
		case WARKER_STATE::STRIKE:
			pWarkerAttack->StartAnimation(0, false);
			pWarkerAttack->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pWarkerAttack->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;
		default: break;
		}
	}
}

void EnemyManager::ImGui()
{
	if (Editer::GetInstance()->GetNowEditer())
	{
		ImGui::Begin("EnemyManager");
		{

			if (ImGui::Button("Warker"))
			{
				WarkerKokim w(enmNum++);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().emplace_back(w);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().emplace_back(
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size()-1).GetModelData(),
					ENEMY_TYPE::WARKER,
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size()-1).GetIndex());

			}
			if (ImGui::Button("Archer"))
			{
				ArcherKokim a(enmNum++);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().emplace_back(a);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().emplace_back(
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size()-1).GetModelData(),
					ENEMY_TYPE::ARCHER,
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size()-1).GetIndex());
				
			}
			if (ImGui::Button("EliteWarker"))
			{
				EliteWarkerKokim ew(enmNum++);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().emplace_back(ew);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().emplace_back(
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().size()-1).GetModelData(),
					ENEMY_TYPE::ELITE_WARKER,
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().size()-1).GetIndex());
				
			}

			//ImGui::NewLine();
			//ImGui::BulletText("SetHP");
			{
				ImGui::InputInt("WarkerHP", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerHpForSet());

				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size() > 0)
				{
					if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerHpForSet() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetHp())
					{

						for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
						{
							w.SetHp(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerHpForSet());
						}
					}
				}
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size()>0 && waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherHpForSet() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(0).GetHp())
				{
					ImGui::InputInt("ArcherHP", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherHpForSet());

					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
					{
						w.SetHp(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherHpForSet());
					}
				}
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().size()>0 && waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarkerHpForSet() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().at(0).GetHp())
				{
					ImGui::InputInt("EliteWarkerHP", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarkerHpForSet());

					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
					{
						w.SetHp(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarkerHpForSet());
					}
				}
			}
			
		}
		ImGui::End();

	
		ImGui::Begin("WaveManager");
		{
			ImGui::SliderInt("WaveNum", &waveMgr->GetWaveNowIndex(), 0, waveMgr->GetWaves().size() - 1);

			if (ImGui::Button("CreateNewWave"))
			{
				waveMgr->GetWaves().emplace_back();
			}

			ImGui::DragInt("TimerMax", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimerMax());

			if (ImGui::Button("Save"))
			{
				waveMgr->Save();
			}

			if (ImGui::Button("Load"))
			{
				waveMgr->Load();
			}


		}
		ImGui::End();
	}
}
