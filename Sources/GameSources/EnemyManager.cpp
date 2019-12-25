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
#include "CharacterSystem.h"
#include "WarkerAttack.h"
#include "UiSystem.h"

EnemyManager::EnemyManager()
{
	{
		pWarker =		std::make_shared<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);
		pWarkerAttack = std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerAttack.fbx", false);
		pWarkerRun =	std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerRun.fbx", false);
		pWarkerWait =	std::make_shared<Model>("Data/Assets/Model/Enemys/WarkerWait.fbx", false);
	}
	pEliteWarker =		std::make_shared<Model>("Data/Assets/Model/Enemys/Warker.fbx", false);

	{
		//pArcher = std::make_shared<Model>("Data/Assets/Model/Enemys/Archer.fbx", false);
		//pShot = std::make_shared<Model>("Data/Assets/Model/Enemys/Arrow.fbx", false);
	}
	pPlayer = std::make_shared<Model>("Data/Assets/Model/Player/Player.fbx", false);

	waveMgr = std::make_unique<WaveManager>();

	WarkerAttackJudge::GetInstance()->pWarkerAttack = pWarkerAttack;

	///*enowCatch.resize(enmList.size());*/

	pWarkerRun->StartAnimation(0, true);

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
		for (auto &wa : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			wa.GetWeaponCollision()->SetPos(pWarkerAttack->GetVectexPos("polySurface4", vPoswa, wa.GetModelData()->GetWorldMatrix(),0));
		}
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).Update();
		
	}
	if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimerMax() < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimer())
	{
		//waveMgr->GetWaves().emplace_back();
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).SetTimer(0);
		waveMgr->GetWaveNowIndex()++;

		UiSystem::GetInstance()->GetWaveTexAddress()->Start(waveMgr->GetWaveNowIndex()+1);
	}
	//ImGui();
}

void EnemyManager::Draw()
{
	
	SetRasterizerState(FrameWork::RS_CULL_BACK_TRUE);

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
		//pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		//for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		//{
		//	pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		//	if (arc.GetArrow())
		//	{
		//		pShot->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		//		pShot->Render(arc.GetArrow()->GetModelData().GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		//	}
		//}

		WarkerRenderer();

		pEliteWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
		{
			pEliteWarker->Render(ewrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		{
			//arc.GetBodyCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			//wrk.GetBodyCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
		{
			ewrk.GetBodyCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}

		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			//wrk.GetWeaponCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
	}

}

void EnemyManager::WarkerRenderer()
{
	for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
	{
		switch (wrk.GetState())
		{
		case WARKER_STATE::WAIT:
			if (!pWarkerWait->GetAnimatingFlg())
			{
				pWarkerWait->StartAnimation(0, true);
			}
			pWarkerWait->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pWarkerWait->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;
		case WARKER_STATE::RUN:
			if (!pWarkerRun->GetAnimatingFlg())
			{
				pWarkerRun->StartAnimation(0, true);
			}
			pWarkerRun->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pWarkerRun->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;
		case WARKER_STATE::STRIKE:
			if (!pWarkerAttack->GetAnimatingFlg())
			{
				pWarkerAttack->StartAnimation(0, false);
			}
			pWarkerAttack->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pWarkerAttack->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;
		case WARKER_STATE::TPOSE:
	
			pWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			pWarker->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;
		default: break;
		}
	}
}

void EnemyManager::AllDelete()
{
	/*waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().clear();
	waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().shrink_to_fit();*/

	for (int i = 0; i < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size(); i++)
	{
		if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(i).GetNowAsphyxia())
		{
			bool con = false;
			for (int j = 0; j < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().size(); j++)
			{
				
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().at(j).index == waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(i).GetIndex())
				{
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().begin() + j);
					con = true;
					break;
				}
			}
			waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().begin()+i);
			if (con)
			{
				i = -1;
			}
		}
	}
	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().clear();
	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().shrink_to_fit();

	////waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().clear();
	////waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().shrink_to_fit();

	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().clear();
	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().shrink_to_fit();
}

void EnemyManager::ImGui()
{


	ImGui::Begin("AllDeleteE");
	{

		if (ImGui::Button("AllDelete"))
		{
			AllDelete();
		}
	}
	ImGui::End();
	if (Editer::GetInstance()->GetNowEditer())
	{
		ImGui::Begin("EnemyManager");
		{

			if (ImGui::Button("AllDelete"))
			{
				AllDelete();
			}


			if (ImGui::Button("Warker"))
			{
				WarkerKokim w(enmNum++);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().emplace_back(w);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().emplace_back(
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size() - 1).GetModelData(),
					ENEMY_TYPE::WARKER,
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size() - 1).GetIndex());

			}
			if (ImGui::Button("Archer"))
			{
				ArcherKokim a(enmNum++);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().emplace_back(a);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().emplace_back(
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size() - 1).GetModelData(),
					ENEMY_TYPE::ARCHER,
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size() - 1).GetIndex());

			}
			if (ImGui::Button("EliteWarker"))
			{
				EliteWarkerKokim ew(enmNum++);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().emplace_back(ew);
				waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().emplace_back(
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().size() - 1).GetModelData(),
					ENEMY_TYPE::ELITE_WARKER,
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().at(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().size() - 1).GetIndex());

			}
			ImGui::NewLine();
			if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size() > 0)
			{
				ImGui::DragInt(u8"�U������������", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerAttackDistanceForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetAttackDistance() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerAttackDistanceForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetAttackDistance(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerAttackDistanceForSet());
					}
				}

				ImGui::DragInt(u8"�v���C���[�������鋗��", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerFindPlayerDistanceForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetFindPlayerDistance() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerFindPlayerDistanceForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetFindPlayerDistance(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerFindPlayerDistanceForSet());
					}
				}
				ImGui::DragFloat(u8"�G�l�~�[�@���x", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetVelocity() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetVelocity(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet());
					}
				}
				ImGui::DragFloat(u8"����@���L���X�g����", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetStrikeRecastMax() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerStrikeRecastMaxForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetStrikeRecastMax(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerStrikeRecastMaxForSet());
					}
				}

			}
				


			ImGui::NewLine();
			ImGui::BulletText("SetHP");
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

	ImGui::Begin("chinpo");
	{
		ImGui::DragFloat3("vPosWA", &vPoswa.x);
		/*ImGui::DragFloat3("")*/
	}
	ImGui::End();
}
