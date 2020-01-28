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


int meshin;
int bonein;

void EnemyModelManager::Init()
{
	// Warker Kokim Models
	pWarker				= std::make_unique<Model>("Data/Assets/Model/Enemys/Warker.fbx"				, false);
	pWarkerAttack		= std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerAttack.fbx"		, false, true);
	pWarkerJumpAttack	= std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerJumpAttack.fbx"	, false, true);
	pWarkerRun			= std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerRun.fbx"			, false, true);
	pWarkerWait			= std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerWait.fbx"			, false, true);
	pWarkerHidame= std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerHidame.fbx", false, true);

	// Archer Kokim Models
	pArcher				= std::make_unique<Model>("Data/Assets/Model/Enemys/Archer.fbx"				, false);
	pArcherAttack		= std::make_unique<Model>("Data/Assets/Model/Enemys/ArcherAttack.fbx"		, false, true);
	pArcherRun			= std::make_unique<Model>("Data/Assets/Model/Enemys/ArcherRun.fbx"			, false, true);
	pArcherStay			= std::make_unique<Model>("Data/Assets/Model/Enemys/ArcherStay.fbx"			, false, true);
	pArcherHidame = std::make_unique<Model>("Data/Assets/Model/Enemys/ArcherHidame.fbx", false, true);

	// arrow
	pShot				= std::make_unique<Model>("Data/Assets/Model/Enemys/Arrow.fbx"				, false, true);

	EnemyModelManager::GetInstance()->pWarkerAttack->GetBoneTransformIndex(std::string("RightHand"), meshin, bonein);

	
}

EnemyManager::EnemyManager()
{
	
	//pEliteWarker = std::make_shared<Model>("Data/Assets/Model/Enemys/Warker.fbx", false, true);
	//pPlayer = std::make_shared<Model>("Data/Assets/Model/Player/Player.fbx", false);

	waveMgr = std::make_unique<WaveManager>();

	tmpWaveNum = 0.0f;

	if (waveMgr->GetWaves().size() <= 0)
	{
		waveMgr->GetWaves().emplace_back();
	}
}

EnemyManager::~EnemyManager()
{


};

void EnemyManager::Update()
{
	finishWave = waveMgr->GetFinishLastWave();
	if (Editer::GetInstance()->GetNowEditer())
	{
		
	}
	else
	{
		for (auto &wa : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			DirectX::XMFLOAT4X4 s = EnemyModelManager::GetInstance()->pWarkerAttack->GetBoneTransform(meshin,bonein, *wa.modelData.get());

			wa.GetWeaponCollision()->SetPos(DirectX::XMFLOAT3(
				wa.modelData->GetPos().x + s._41 + s._31 * 50,
				wa.modelData->GetPos().y + s._42 + s._32 * 50, 
				wa.modelData->GetPos().z + s._43	 + s._33 * 50));
		}
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).Update();
		
	}
	if ((waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimerMax() < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetTimer()) && !waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex())._isFinish)
	{
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).SetTimer(0);
		
		if (waveMgr->GetWaves().size()-1 > waveMgr->GetWaveNowIndex())
		{
			if (waveMgr->GetWaves().size() > 0)
			{
				for (auto &w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
				{
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()+1).GetWarker().emplace_back(w);
				}
				for (auto &a : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
				{
					waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()+1).GetArcher().emplace_back(a);
				}

				for (auto &w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex() + 1).GetWarker())
				{
					w.Add();
				}
				for (auto &a : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex() + 1).GetArcher())
				{
					a.Add();
				}
			}
			
			waveMgr->GetWaveNowIndex()++;
			waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex())._isChange = true;
		}
		if (waveMgr->GetWaveNowIndex() + 1 > tmpWaveNum)
		{
			UiSystem::GetInstance()->GetWaveTexAddress()->Start(waveMgr->GetWaveNowIndex() + 1);
			tmpWaveNum = waveMgr->GetWaveNowIndex() + 1;

			waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex())._isChange = false;
		}
	}
	else
	{
		bool nextWave=false;
		for (auto &w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			if (w.GetNowAsphyxia())
			{
				nextWave = true;
			}
			else
			{
				nextWave = false;
				break;
				
			}
		}
		if (nextWave)
		{
			for (auto &a : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
			{
				if (a.GetNowAsphyxia())
				{
					nextWave = true;
				}
				else
				{
					nextWave = false;
					break;
				}
			}
		}

		if (nextWave && waveMgr->GetWaves().size() - 1 == waveMgr->GetWaveNowIndex())
		{
			waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex())._isFinish = true;
		}

	}

	if (waveMgr->GetWaves().size() - 1 == waveMgr->GetWaveNowIndex() &&
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size() <= 0 &&
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size() <= 0)
	{
		waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex())._isFinish = true;
	}

#ifdef _DEBUG

	ImGui();
#endif // _DEBUG

}

void EnemyManager::Draw()
{
	
	SetRasterizerState(FrameWork::RS_CULL_BACK_TRUE);

	if (Editer::GetInstance()->GetNowEditer())
	{
		for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		{
			EnemyModelManager::GetInstance()->pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			EnemyModelManager::GetInstance()->pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());

		}

		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			EnemyModelManager::GetInstance()->pWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			EnemyModelManager::GetInstance()->pWarker->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		}

		/*pEliteWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		for (auto &ewrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker())
		{
			pEliteWarker->Render(ewrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix(), CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		}
*/
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
		//for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
		//{
		//	arc.pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		//	arc.pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		//	if (arc.GetArrow())
		//	{
		//		arc.pShot->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		//		arc.pShot->Render(arc.GetArrow()->GetModelData().GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
		//	}
		//}

		ArcherRenderer();

		WarkerRenderer();

		
	
		for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
		{
			wrk.GetWeaponCollision()->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), FrameWork::GetInstance().GetElapsedTime());
		}
		
	}

}

void EnemyManager::ArcherRenderer()
{
	EnemyModelManager::GetInstance()->pArcherStay->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pArcherRun->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pArcherAttack->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pShot->Begin(ShaderSystem::GetInstance()->GetShaderOfStaticMeshBatch(), false);
	EnemyModelManager::GetInstance()->pArcher->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pArcherHidame->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	for (auto &arc : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
	{
		switch (arc.state)
		{
		case ARCHER_STATE::WAIT:
			if (!arc.GetModelData()->GetIsAnimation() && !arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(true);
				arc.modelData->SetIsLoopAnimation(true);
			}
			else if (arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pArcherStay->Render(*arc.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

		/*	arc.pArcherStay->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			arc.pArcherStay->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case ARCHER_STATE::RUN:
			if (!arc.GetModelData()->GetIsAnimation() && !arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(true);
				arc.modelData->SetIsLoopAnimation(true);
			}
			else if (arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pArcherRun->Render(*arc.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

		/*	arc.pArcherRun->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			arc.pArcherRun->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case ARCHER_STATE::STRIKE:
			if (!arc.GetModelData()->GetIsAnimation() && !arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(true);
				arc.modelData->SetIsLoopAnimation(true);
			}
			else if (arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pArcherAttack->Render(*arc.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

			/*arc.pArcherAttack->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			arc.pArcherAttack->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			if (arc.arrow)
			{

				{
					EnemyModelManager::GetInstance()->pShot->Render(arc.arrow->GetModelData(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
				}

				/*arc.pShot->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
				arc.pShot->Render(arc.arrow->GetModelData().GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0, 1, 0, 1), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			}
			break;
		case ARCHER_STATE::TPOSE:

		{
			EnemyModelManager::GetInstance()->pArcher->Render(*arc.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
		}

			/*arc.pArcher->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			arc.pArcher->Render(arc.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case ARCHER_STATE::HIDAME:
		
			if (arc.GetNowAsphyxia())
			{
				arc.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pArcherHidame->Render(*arc.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}
			if (arc.GetNowAsphyxia())
			{

				arc.SetState(ARCHER_STATE::WAIT);
			}

			{
				EnemyModelManager::GetInstance()->pWarkerHidame->Render(*arc.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

			arc.hidameCnt++;
			if (arc.hidameCnt > 10)
			{
				arc.hidame = false;
				arc.hidameCnt = 0;
			}
			break;
		default: break;
		}
	}
	EnemyModelManager::GetInstance()->pArcherStay->SetShaders(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch());
	EnemyModelManager::GetInstance()->pArcherStay->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pArcherRun->SetShaders(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch());
	EnemyModelManager::GetInstance()->pArcherRun->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pArcherAttack->SetShaders(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch());
	EnemyModelManager::GetInstance()->pArcherAttack->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pShot->SetShaders(ShaderSystem::GetInstance()->GetShaderOfStaticMeshBatch());
	EnemyModelManager::GetInstance()->pShot->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pArcher->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pArcherHidame->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
}

void EnemyManager::WarkerRenderer()
{
	EnemyModelManager::GetInstance()->pWarkerWait->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pWarkerRun->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pWarkerAttack->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pWarkerJumpAttack->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	EnemyModelManager::GetInstance()->pWarkerHidame->Begin(ShaderSystem::GetInstance()->GetShaderOfSkinnedMeshBatch(), false);
	for (auto &wrk : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
	{
		switch (wrk.GetState())
		{
		case WARKER_STATE::WAIT:
			if (!wrk.GetModelData()->GetIsAnimation() && !wrk.GetNowAsphyxia())
			{
				wrk.modelData->SetIsAnimation(true);
				wrk.modelData->SetIsLoopAnimation(true);
			}
			else if (wrk.GetNowAsphyxia())
			{
				wrk.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pWarkerWait->Render(*wrk.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

		/*	wrk.pWarkerWait->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			wrk.pWarkerWait->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case WARKER_STATE::RUN:
			if (!wrk.GetModelData()->GetIsAnimation() && !wrk.GetNowAsphyxia())
			{
				wrk.modelData->SetIsAnimation(true);
				wrk.modelData->SetIsLoopAnimation(true);
			}
			else if (wrk.GetNowAsphyxia())
			{
				wrk.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pWarkerRun->Render(*wrk.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

		/*	wrk.pWarkerRun->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			wrk.pWarkerRun->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case WARKER_STATE::STRIKE:
			if (wrk.GetNowAsphyxia())
			{
				wrk.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pWarkerAttack->Render(*wrk.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

			/*wrk.pWarkerAttack->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			wrk.pWarkerAttack->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case WARKER_STATE::JUMP_ATTACK:
			if (wrk.GetNowAsphyxia())
			{
				wrk.modelData->SetIsAnimation(false);
			}

			{
				EnemyModelManager::GetInstance()->pWarkerJumpAttack->Render(*wrk.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

			/*wrk.pWarkerJumpAttack->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			wrk.pWarkerJumpAttack->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());*/
			break;
		case WARKER_STATE::TPOSE:
	
			//wrk.pWarker->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
			//wrk.pWarker->Render(wrk.GetModelData()->GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			//	DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1, 1, 1, 1), FrameWork::GetInstance().GetElapsedTime());
			break;

		case WARKER_STATE::HIDAME:

			if (wrk.GetNowAsphyxia())
			{

				wrk.SetState(WARKER_STATE::WAIT);
			}

			{
				EnemyModelManager::GetInstance()->pWarkerHidame->Render(*wrk.modelData.get(), /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
			}

			wrk.hidameCnt++;
			if (wrk.hidameCnt > 10)
			{
				wrk.hidame = false;
				wrk.hidameCnt = 0;
			}

		default: break;
		}
	}

	EnemyModelManager::GetInstance()->pWarkerWait->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pWarkerRun->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pWarkerAttack->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pWarkerJumpAttack->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	EnemyModelManager::GetInstance()->pWarkerHidame->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
}

void EnemyManager::AllDelete()
{
	waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().clear();
	waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().shrink_to_fit();

	
	waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().clear();
	waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().shrink_to_fit();

	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().clear();
	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().shrink_to_fit();

	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().clear();
	//waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEnemyList().shrink_to_fit();
}

void EnemyManager::AllDeleteX()
{


	for (int i = 0; i < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size(); i++)
	{
		if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(i).GetNowAsphyxia())
		{

			waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().begin() + i);
			i--;
		}
	}
	for (int i = 0; i < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size(); i++)
	{
		if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(i).GetNowAsphyxia())
		{

			waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().begin() + i);
			i--;
		}
	}

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
			ImGui::BulletText("WARKER");
			if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size() > 0)
			{
				ImGui::DragInt(u8"攻撃しだす距離w", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerAttackDistanceForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetAttackDistance() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerAttackDistanceForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetAttackDistance(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerAttackDistanceForSet());
					}
				}

				ImGui::DragInt(u8"プレイヤーを見つける距離w", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerFindPlayerDistanceForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetFindPlayerDistance() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerFindPlayerDistanceForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetFindPlayerDistance(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerFindPlayerDistanceForSet());
					}
				}
				ImGui::DragFloat(u8"エネミー　速度w", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetVelocity() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetVelocity(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerVelocityForSet());
					}
				}
				ImGui::DragInt(u8"攻撃　リキャスト時間w", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerStrikeRecastMaxForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(0).GetStrikeRecastMax() != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerStrikeRecastMaxForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker())
					{
						w.SetStrikeRecastMax(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarkerStrikeRecastMaxForSet());
					}
				}
			}
			ImGui::NewLine();
			ImGui::BulletText("ARCHER");
			if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size() > 0)
			{
				ImGui::DragInt(u8"攻撃しだす距離q", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherAttackDistanceForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(0).atDis != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherAttackDistanceForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
					{
						w.SetAttackDistance(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherAttackDistanceForSet());
					}
				}

				ImGui::DragInt(u8"プレイヤーを見つける距離q", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherFindPlayerDistanceForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(0).findPdis != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherFindPlayerDistanceForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
					{
						w.SetFindPlayerDistance(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherFindPlayerDistanceForSet());
					}
				}
				ImGui::DragInt(u8"攻撃　リキャスト時間q", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherStrikeRecastMaxForSet());
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(0).recastMax != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherStrikeRecastMaxForSet())
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
					{
						w.SetRecastMax(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherStrikeRecastMaxForSet());
					}
				}

				ImGui::DragInt(u8"攻撃力q", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).setArcherAttackPoint);
				if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(0).attackPoint != waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).setArcherAttackPoint)
				{
					for (auto& w : waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher())
					{
						w.SetAttackPoint(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).setArcherAttackPoint);
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

				ImGui::InputInt("ArcherHP", &waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcherHpForSet());
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
	else
	{
		ImGui::Begin("WaveManager");
		{
			if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex())._isFinish)
			{
				ImGui::Text("true");
			}
			else
			{
				ImGui::Text("false");
			}

			ImGui::Checkbox("StopTimer", &stopTimer);

		}
		ImGui::End();
	}
}
