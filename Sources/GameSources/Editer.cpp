#include "Editer.h"
#include "Camera.h"
#include "Collision.h"
#include "CameraSystem.h"
#include "CharacterSystem.h"
#include "Wave.h"
Editer::Editer()
{
	nowEditer = false;
	nowCatch = false;
	catchIndex = -1;
	distance = 2500;
}

void Editer::Update()
{
	POINT cursor;
	::GetCursorPos(&cursor);

	oldCursor = newCursor;
	newCursor = DirectX::XMFLOAT2(static_cast<float>(cursor.x), static_cast<float>(cursor.y));


	
	DirectX::XMMATRIX view = CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix();
	DirectX::XMMATRIX proj = CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix();
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMVECTOR screen_start = DirectX::XMVectorSet(newCursor.x,newCursor.y,0.0f, 0.0f);
	DirectX::XMVECTOR screen_end = DirectX::XMVectorSet(newCursor.x, newCursor.y,1.f, 0.0f);
	/*const D3D11_VIEWPORT& vp = camera;*/
	DirectX::XMVECTOR world_start = DirectX::XMVector3Unproject(screen_start,
		0, 0, 1920, 1080, 0.1f, 1000000.0f,
		proj, view, world);

	DirectX::XMVECTOR world_end = DirectX::XMVector3Unproject(screen_end,
		0, 0, 1920, 1080, 0.1f, 1000000.0f,
		proj, view, world);

	

	DirectX::XMStoreFloat3(&screenWorld, world_start);
	DirectX::XMStoreFloat3(&screenWorld2, world_end);

	
	if (nowCatch)
	{


		for (int a =0; a<CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().size(); a++)
		{
			if (CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(a).nowCatch)
			{
				DirectX::XMVECTOR mworld_enm = DirectX::XMVector3Unproject(
					DirectX::XMLoadFloat3(
						&DirectX::XMFLOAT3(newCursor.x, newCursor.y, 0.5f)),
					0, 0, 1920, 1080, 0.1f, 1000000.0f,
					proj, view, world);
				DirectX::XMFLOAT3 world_enm;
				DirectX::XMStoreFloat3(&world_enm, mworld_enm);

				CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(a).modelData->SetPos(DirectX::XMFLOAT3(world_enm.x*adjust.x*cameraHeight,0,world_enm.z*adjust.y*cameraHeight));
		
				WaveManager* waveMgr = CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager();
				if (GetAsyncKeyState('A') & 1)
				{
					switch (CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(a).type)
					{
					case ENEMY_TYPE::WARKER:
						for (int i = 0; i < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().size(); i++)
						{
							if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().at(i).index== (int)CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(a).index)
							{
								waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetWarker().begin()+i);
							}
						}
						break;
					case ENEMY_TYPE::ARCHER:
						for (int i = 0; i < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().size(); i++)
						{
							if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().at(i).index == (int)CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(a).index)
							{
								waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetArcher().begin() + i);
							}
						}
						break;
					case ENEMY_TYPE::ELITE_WARKER:
						for (int i = 0; i < waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().size(); i++)
						{
							if (waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().at(i).index == (int)CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(a).index)
							{
								waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().erase(waveMgr->GetWaves().at(waveMgr->GetWaveNowIndex()).GetEliteWarker().begin() + i);
							}
						}
						break;
					}
					CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().erase(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().begin() + a);
					nowCatch = false;
				}
			}
		}

		if (GetAsyncKeyState(VK_RBUTTON) & 1)
		{
			nowCatch = false;
			for (size_t i =0; i<CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().size();i++)
			{
				CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(i).nowCatch = false;
			}
		}
	}
	else
	{
		float distance = NULL;
		if (::GetAsyncKeyState(VK_MENU) == 0)
		{
			for (size_t i =0; i<CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().size();i++)
			{
				if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					
					DirectX::XMStoreFloat2(&screenEnm,
						DirectX::XMVector3Project(
							DirectX::XMLoadFloat3(&CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(i).modelData->GetPos()),
							0, 0, 1920, 1080, 0.1f, 1000000.0f,
							proj, view, world));
					if (collision.SphereVsSphere(DirectX::XMFLOAT3(newCursor.x,0, newCursor.y),
						DirectX::XMFLOAT3(screenEnm.x, 0, screenEnm.y),1,100))
					{
						CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaves().at(CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex()).GetEnemyList().at(i).nowCatch = true;
						nowCatch = true;
						break;
						
					}
				
				}
			}
		}

		
	}

	
	Imgui();
}


void Editer::Imgui()
{
	ImGui::Begin("edit");

	ImGui::DragFloat2("Adjust", &adjust.x, 1.f);

	ImGui::End();
}