#include "SceneGame.h"
#include <FrameWork.h>
#include <string>
#include "Collision.h"
#include "CollisionJudge.h"
#include "Blender.h"
#include "InputDevice.h"
#include "SkinnedMesh.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "ParticleSystem.h"
#include "Editer.h"
#include "CameraSystem.h"
#include "EnemyManager.h"
#include "SoundLoader.h"
#include "Shot.h"
#include "UiSystem.h"
#include "Ranking.h"
#include "Crystal.h"
#include "ScenePause.h"

void SceneGame::Init()
{
	AllSoundStop();
	gameTimer = std::make_unique<GameTimer>();
	gameTimer->Init();
	gameOver = std::make_unique<GameOver>();
	gameOver->Init();

	CharacterSystem::GetInstance()->Init();
	ObjectSystem::GetInstance()->Init();
	ParticleSystem::GetInstance()->Init();
	UiSystem::GetInstance()->Init();
	Ranking::GetInstance()->Init();
	CrystalSystem::GetInstance()->Init();
	//UiSystem::GetInstance()->Init();

	//UiSystem::GetInstance()->GetWaveTexAddress()->Start(1);
	Editer::GetInstance()->SetNowEditer(false);

}

void SceneGame::Update()
{
	//if (Fade::GetInstance()->onFadeFlg) return;

	CharacterSystem::GetInstance()->Update();
	if (!CharacterSystem::GetInstance()->GetPlayerAddress()->GetisDead()) CameraControl::PadControlUpdate(&CameraSystem::GetInstance()->mainView);
	else CameraControl::CameraRotation(&CameraSystem::GetInstance()->mainView);
	CollisionJudge::CameraVsStage();

	DirectX::XMFLOAT3 playerPos = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos();
	float playerAngle = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetAngle().y;
	CameraSystem::GetInstance()->mainView.SetTarget({ playerPos.x, playerPos.y + 150,   playerPos.z });
	
	ParticleSystem::GetInstance()->Update();

	if (CharacterSystem::GetInstance()->GetPlayerAddress()->GetFinalBlow()) return;
	ObjectSystem::GetInstance()->Update();

	UiSystem::GetInstance()->Update();
	CrystalSystem::GetInstance()->Update();

	gameTimer->Update();

	if (!Editer::GetInstance()->GetNowEditer())
	{
	}
	else
	{
		CameraSystem::GetInstance()->enemyEditorView.Set(DirectX::XMFLOAT3(0, Editer::GetInstance()->cameraHeight, 0), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -1));
	}

	//if (xInput[0].bBt)
	//{
	//	ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos());
	//}

	if (Editer::GetInstance()->GetNowEditer())
	{
		Editer::GetInstance()->Update();
	}

	//UiSystem::GetInstance()->Update();

	CollisionJudge::PlayerVsStage();
	CollisionJudge::PlayerAttackVsEnemies();
	CollisionJudge::EnemiesAttackVsPlayer();
	CollisionJudge::PlayerVsEnemies();

	//TODO TITLE
	/*if (UiSystem::GetInstance()->GetHpAddress()->GetSubHp() >= 610 || 
		7 <= CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex())
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}

	if (GetKeyState('A') < 0)
	{
		UiSystem::GetInstance()->GetWaveTexAddress()->Start(10);
	}*/

	if (xInput[0].bSTARTt)
	{
		SceneManager::GetInstance()->SetScene(new ScenePause(), true);
	}

#ifdef _DEBUG
	SceneGame::ImGui();
#endif // _DEBUG

}

void SceneGame::Render()
{
	CharacterSystem::GetInstance()->Draw();
	ObjectSystem::GetInstance()->Draw();
	UiSystem::GetInstance()->Draw();
	gameTimer->Draw();

	if (!Editer::GetInstance()->GetNowEditer())
	{
		ParticleSystem::GetInstance()->Draw();
	}

	CrystalSystem::GetInstance()->Draw();
	//UiSystem::GetInstance()->Draw();
	if (CharacterSystem::GetInstance()->GetPlayerAddress()->GetisDead())
	{
		Ranking::GetInstance()->Draw();
		gameOver->Draw();
	}
}

void SceneGame::ImGui()
{
	ImGui::Begin("Title");
	if (ImGui::Button("BuffArea  POP "))
	{
		ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos());
		CharacterSystem::GetInstance()->GetPlayerAddress()->SufferDamage(5000);
	}
	if (ImGui::Button("Particle  POP "))
	{
		//ParticleSystem::GetInstance()->SetBuffAreaParticle({50.0f, 100.0f, 50.0f}, 200);
		ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle({ 0, 100, 0 });
		PlaySoundMem(SoundLoader::GetInstance()->playerAttackHit.get());
	}

	if (ImGui::Button("Editer"))
	{
		Editer::GetInstance()->SetNowEditer(Editer::GetInstance()->GetNowEditer() ^ 1);


		if (Editer::GetInstance()->GetNowEditer())
		{
			CameraSystem::GetInstance()->enemyEditorView.Init(DirectX::XMFLOAT3(0, 1000, 0), DirectX::XMFLOAT3(0, 0, 0));
			CameraSystem::GetInstance()->enemyEditorView.Set(DirectX::XMFLOAT3(0, 1000, 0), DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 1, 0));

			CameraSystem::GetInstance()->enemyEditorView.SetPerspectiveMatrix(DirectX::XMConvertToRadians(30.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 5000.0f);
			/*CameraSystem::GetInstance()->enemyEditorView.SetOrthographicMatrix(1920,1080, 0.1f, 1000000.0f);*/
		}
	}
	ImGui::DragInt("CameraHeight", &Editer::GetInstance()->cameraHeight);

	CharacterSystem::GetInstance()->ImGui();
	ObjectSystem::GetInstance()->ImGui();

	ImGui::End();
}

void SceneGame::UnInit() 
{
	CharacterSystem::GetInstance()->UnInit();
	ObjectSystem::GetInstance()->UnInit();
	UiSystem::GetInstance()->UnInit();
}