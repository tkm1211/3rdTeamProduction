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
#include "Wave.h"

void SceneGame::Init()
{
	AllSoundStop();
	AllBgmSoundStop();
	PlaySoundMem(SoundLoader::GetInstance()->main.get());

	gameTimer = std::make_unique<GameTimer>();
	gameTimer->Init();
	gameOver = std::make_unique<GameOver>();
	gameOver->Init();
	gameClear = std::make_unique<GameClear>();
	gameClear->Init();

	back = std::make_unique<Sprite>(L"Data/Assets/Texture/blackFade.png");
	/*nowLoading = std::make_unique<Sprite>(L"Data/Assets/Texture/text03.png");

	nowLoadingData.pos = DirectX::XMFLOAT2(600.0f, 455.0f);
	nowLoadingData.texPos = DirectX::XMFLOAT2(0.0f, 110.0f);
	nowLoadingData.size = DirectX::XMFLOAT2(440.0f, 110.0f);

	for (int i = 0; i < 3; i++)
	{
		dotData[i].pos = DirectX::XMFLOAT2(1050.0f + 50.0f * i, 455.0f);
		dotData[i].texPos = DirectX::XMFLOAT2(10013.8f, 110.0f);
		dotData[i].size = DirectX::XMFLOAT2(30.0f, 110.0f);
	}


	loadingThread = std::make_unique<std::thread>([&]()
	{
		std::lock_guard<std::mutex> lock(loadingMutex);

		CharacterSystem::GetInstance()->Init();
		ObjectSystem::GetInstance()->Init();
		ParticleSystem::GetInstance()->Init();
		UiSystem::GetInstance()->Init();
		Ranking::GetInstance()->Init();
		CrystalSystem::GetInstance()->Init();
	});*/
	//UiSystem::GetInstance()->Init();

	Editer::GetInstance()->SetNowEditer(false);
	CameraControl::PadControlUpdate(&CameraSystem::GetInstance()->mainView);
	DirectX::XMFLOAT3 playerPos = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos();
	float playerAngle = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetAngle().y;
	CameraSystem::GetInstance()->mainView.SetTarget({ playerPos.x, playerPos.y + 150,   playerPos.z });

	isWave = false;
	/*cnt = 0;
	state = 0;*/
}

void SceneGame::Update()
{
	//if (IsNowLoading())
	//{
	//	return; //ƒ[ƒh‚ªŠ®—¹‚µ‚Ä‚¢‚È‚©‚Á‚½‚ç‘¦return
	//}

	//if (loadingThread && loadingThread->joinable())
	//{
	//	loadingThread->join();
	//}
	ParticleSystem::GetInstance()->Update();

	if (Fade::GetInstance()->onFadeFlg) return;

	if (!isWave)
	{
		UiSystem::GetInstance()->GetWaveTexAddress()->Start(1);
		isWave = true;
	}

	EnemyManager* enm = CharacterSystem::GetInstance()->GetEnemyManagerAddress();
	CharacterSystem::GetInstance()->Update();
	if (!CharacterSystem::GetInstance()->GetPlayerAddress()->GetisDead()) CameraControl::PadControlUpdate(&CameraSystem::GetInstance()->mainView);
	else CameraControl::CameraRotation(&CameraSystem::GetInstance()->mainView);
	CollisionJudge::CameraVsStage();

	DirectX::XMFLOAT3 playerPos = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos();
	float playerAngle = CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetAngle().y;
	CameraSystem::GetInstance()->mainView.SetTarget({ playerPos.x, playerPos.y + 150,   playerPos.z });
	
	CollisionJudge::DeathBlowVsEnemies();
	if (CharacterSystem::GetInstance()->GetPlayerAddress()->GetFinalBlow()) return;
	ObjectSystem::GetInstance()->Update();

	UiSystem::GetInstance()->Update();
	CrystalSystem::GetInstance()->Update();

	if (enm->finishWave && !CharacterSystem::GetInstance()->GetPlayerAddress()->finish)
	{
		AllSoundStop();
		AllBgmSoundStop();
		PlaySoundMem(SoundLoader::GetInstance()->clear.get());

		CharacterSystem::GetInstance()->GetPlayerAddress()->finish = true;
	}

	if(!enm->finishWave && !CharacterSystem::GetInstance()->GetPlayerAddress()->GetisDead())
	{
		gameTimer->Update();
	}
	 if (CharacterSystem::GetInstance()->GetPlayerAddress()->GetisDead())
	{
		 enm->stopTimer = true;
		 gameOver->Update();
	}
	if (CharacterSystem::GetInstance()->GetPlayerAddress()->clearFlg)
	{
		gameClear->Update(gameTimer->timeNum, gameTimer->timer, gameTimer->frameNum);
	}

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
	CollisionJudge::EnemyVsEnemies();
	CollisionJudge::PlayerVsEnemies();
	CollisionJudge::EnemiesVsStage();

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
		AllSoundStop();
		// CharacterSystem::GetInstance()->GetPlayerAddress()->StopMotion();
		SkinnedMesh::OnPauseAnimation();
		SkinnedMeshBatch::OnPauseAnimation();
		SceneManager::GetInstance()->SetScene(new ScenePause(), true);
	}
	static int keycnt = 0;
	if (GetKeyState('P') < 0)
	{
		if (keycnt == 0)
		{
			SceneManager::GetInstance()->SetScene(new ScenePause(), true);
		}
		keycnt++;
	}
	else
	{
		keycnt = 0;
	}

#ifdef _DEBUG
	//SceneGame::ImGui();
#endif // _DEBUG

}

void SceneGame::Render()
{
	if (Fade::GetInstance()->nowLoad) return;

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
		gameOver->Draw();
	}
	if (CharacterSystem::GetInstance()->GetPlayerAddress()->clearFlg)
	{
		gameClear->Draw();
		Ranking::GetInstance()->Draw();
	}
}

void SceneGame::ImGui()
{

	CharacterSystem::GetInstance()->GetPlayerAddress()->ImGui();

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