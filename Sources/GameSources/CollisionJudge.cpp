#include "CollisionJudge.h"
#include "Collision.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "BG.h"
#include "EnemyManager.h"
#include "ParticleSystem.h"
#include "Wave.h"
#include "SoundLoader.h"

void CollisionJudge::AllJudge()
{
	//PlayerAttackVsEnemies();
	//EnemiesAttackVsPlayer();
	//BuffAreaVsPlayer();
	//PlayerVsStage();
	//EnemiesVsStage();
	//PlayerVsEnemies();
}


void CollisionJudge::PlayerVsEnemies()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	EnemyManager* enemyManager;
	enemyManager = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	WaveManager* waveManager;
	waveManager = enemyManager->GetWaveManager();

	Wave* waveData = &waveManager->GetWaves()[waveManager->GetWaveNowIndex()];

	for (auto& warkerKokim : waveData->GetWarker())
	{
		DirectX::XMFLOAT3 playerPosFloat3 = player->GetModelData().GetPos();
		DirectX::XMFLOAT2 playerPos = DirectX::XMFLOAT2(playerPosFloat3.x, playerPosFloat3.z);
		DirectX::XMFLOAT3 enmeyPosFloat3 = DirectX::XMFLOAT3(warkerKokim.GetModelData()->GetPos().x, warkerKokim.GetModelData()->GetPos().y, warkerKokim.GetModelData()->GetPos().z);
		DirectX::XMFLOAT2 enmeyPos = DirectX::XMFLOAT2(enmeyPosFloat3.x, enmeyPosFloat3.z);

		if (warkerKokim.GetState() == WARKER_STATE::RUN)
		{
			if (Collision::CircleVsCircleAndExtrusion(enmeyPos, warkerKokim.GetBodyCollision()->GetCollisionScale().x, playerPos, player->bodyCollision->GetCollisionScale().x))
			{
				warkerKokim.modelData->SetPos(DirectX::XMFLOAT3(enmeyPos.x, enmeyPosFloat3.y, enmeyPos.y));
			}
		}
		else
		{
			if (Collision::CircleVsCircleAndExtrusion(playerPos, player->bodyCollision->GetCollisionScale().x, enmeyPos, warkerKokim.GetBodyCollision()->GetCollisionScale().x))
			{
				player->SetModelPosition(DirectX::XMFLOAT3(playerPos.x, playerPosFloat3.y, playerPos.y));
				//	ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle(warkerKokim.GetModelData()->GetPos());
			}
		}
	}
}

void CollisionJudge::PlayerAttackVsEnemies()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	if (!player->GetOnAtkCollision()) return;

	EnemyManager* enemyManager;
	enemyManager = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	WaveManager* waveManager;
	waveManager = enemyManager->GetWaveManager();

	Wave* waveData = &waveManager->GetWaves()[waveManager->GetWaveNowIndex()];

	for (auto& warkerKokim : waveData->GetWarker())
	{

		if (Collision::SphereVsSphere(player->atkCollision->GetPos(), warkerKokim.GetModelData()->GetPos(), player->atkCollision->GetCollisionScale().x, warkerKokim.GetBodyCollision()->GetCollisionScale().x) && !warkerKokim.GetNowAsphyxia() && warkerKokim.GetDamageRecast() == 0)
		{
			warkerKokim.Damage(CharacterSystem::GetInstance()->GetPlayerAddress()->GetAttackDamage());
			warkerKokim.SetDamageRecast(50);
			ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle(warkerKokim.GetModelData()->GetPos());
			PlaySoundMem(SoundLoader::GetInstance()->playerAttackHitSe.get());
			if(warkerKokim.GetHp() <= 0) ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(warkerKokim.GetModelData()->GetPos());
		}
	}
}

void CollisionJudge::EnemiesAttackVsPlayer()
{
	EnemyManager* enemyManager;
	enemyManager = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	WaveManager* waveManager;
	waveManager = enemyManager->GetWaveManager();

	Wave* waveData = &waveManager->GetWaves()[waveManager->GetWaveNowIndex()];

	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();


	for (auto& warkerKokim : waveData->GetWarker())
	{
		if (warkerKokim.GetState() != WARKER_STATE::STRIKE || warkerKokim.GetNowAsphyxia()) continue;

		if (Collision::SphereVsSphere(player->GetModelData().GetPos(), warkerKokim.GetWeaponCollision()->GetPos(), player->bodyCollision->GetCollisionScale().x, warkerKokim.GetWeaponCollision()->GetCollisionScale().x))
		{
			player->SufferDamage(MAX_PLAYER_DAMAGE * (0.7f + ((rand() % 500 + 1) / 1000.0f)));
			DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&player->GetModelData().GetPos());
			DirectX::XMVECTOR e = DirectX::XMLoadFloat3(&warkerKokim.GetWeaponCollision()->GetPos());
			DirectX::XMVECTOR d = DirectX::XMVectorSubtract(e, p);
			d = DirectX::XMVectorNegate(d);
			d = DirectX::XMVector3Normalize(d);
			DirectX::XMFLOAT3 sp = {};
			DirectX::XMStoreFloat3(&sp, d);
			CharacterSystem::GetInstance()->GetPlayerAddress()->SetMoveSpeed({sp.x * 10, 0, sp.z * 10});
		//	ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle(warkerKokim.GetModelData()->GetPos());
		}
	}
}

void CollisionJudge::BuffAreaVsPlayer()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	for (auto& it : ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->buffArea)
	{
		if (Collision::SphereVsSphere(player->GetModelData().GetPos(), it.pArea_collision->GetPos(), player->bodyCollision->GetCollisionScale().x, it.pArea_collision->GetCollisionScale().x))
		{
			ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->checkBuff(&it);
		}
	}
}

void CollisionJudge::PlayerVsStage()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	DirectX::XMFLOAT3 playerPosFloat3 = player->GetModelData().GetPos();
	DirectX::XMFLOAT2 playerPos = DirectX::XMFLOAT2(playerPosFloat3.x, playerPosFloat3.z);
	DirectX::XMFLOAT2 playerScale = DirectX::XMFLOAT2(player->bodyCollision->GetScale().x, player->bodyCollision->GetScale().z);


	BG* bg;
	bg = ObjectSystem::GetInstance()->GetBgAddress();

	DirectX::XMFLOAT2 bgPos   = DirectX::XMFLOAT2(bg->wallCollision->GetPos().x, bg->wallCollision->GetPos().z);
	DirectX::XMFLOAT2 bgScale = DirectX::XMFLOAT2(bg->wallCollision->GetCollisionScale().x, bg->wallCollision->GetCollisionScale().z);


	if (Collision::RectVsRectAndExtrusion(playerPos, bgPos, playerScale, bgScale))
	{
		player->SetModelPosition(DirectX::XMFLOAT3(playerPos.x, playerPosFloat3.y, playerPos.y));
	}
}

void CollisionJudge::EnemiesVsStage()
{
	EnemyManager* enemyManager;
	enemyManager = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	WaveManager* waveManager;
	waveManager = enemyManager->GetWaveManager();

	Wave* waveData = &waveManager->GetWaves()[waveManager->GetWaveNowIndex()];


	BG* bg;
	bg = ObjectSystem::GetInstance()->GetBgAddress();

	DirectX::XMFLOAT2 bgPos = DirectX::XMFLOAT2(bg->wallCollision->GetPos().x, bg->wallCollision->GetPos().z);
	DirectX::XMFLOAT2 bgScale = DirectX::XMFLOAT2(bg->wallCollision->GetScale().x, bg->wallCollision->GetScale().z);


	if (waveData->GetWarker().size() > 0)
	{
		for (auto& warkerKokim : waveData->GetWarker())
		{
			DirectX::XMFLOAT3 enemyPosFloat3 = warkerKokim.GetBodyCollision()->GetPos();
			DirectX::XMFLOAT2 enemyPos = DirectX::XMFLOAT2(enemyPosFloat3.x, enemyPosFloat3.z);
			DirectX::XMFLOAT2 enemyScale = DirectX::XMFLOAT2(warkerKokim.GetBodyCollision()->GetScale().x, warkerKokim.GetBodyCollision()->GetScale().z);

			if (Collision::RectVsRectAndExtrusion(enemyPos, bgPos, enemyScale, bgScale))
			{
				//warkerKokim.SetModelPosition(DirectX::XMFLOAT3(enemyPos.x, enemyPosFloat3.y, enemyPos.y));
			}
		}
	}
}