#include "CollisionJudge.h"
#include "Collision.h"
#include "CharacterSystem.h"
#include "ObjectSystem.h"
#include "BG.h"
#include "EnemyManager.h"
#include "ParticleSystem.h"
#include "Wave.h"
#include "WaveManager.h"
#include "SoundLoader.h"
#include "CameraSystem.h"
#include "UiSystem.h"

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

	// Player Vs Warker
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

	// Player Vs Archer
	for (auto& archerKokim : waveData->GetArcher())
	{
		DirectX::XMFLOAT3 playerPosFloat3 = player->GetModelData().GetPos();
		DirectX::XMFLOAT2 playerPos = DirectX::XMFLOAT2(playerPosFloat3.x, playerPosFloat3.z);
		DirectX::XMFLOAT3 enmeyPosFloat3 = DirectX::XMFLOAT3(archerKokim.GetModelData()->GetPos().x, archerKokim.GetModelData()->GetPos().y, archerKokim.GetModelData()->GetPos().z);
		DirectX::XMFLOAT2 enmeyPos = DirectX::XMFLOAT2(enmeyPosFloat3.x, enmeyPosFloat3.z);

		if (archerKokim.state == ARCHER_STATE::RUN)
		{
			if (Collision::CircleVsCircleAndExtrusion(enmeyPos, archerKokim.GetBodyCollision()->GetCollisionScale().x, playerPos, player->bodyCollision->GetCollisionScale().x))
			{
				archerKokim.modelData->SetPos(DirectX::XMFLOAT3(enmeyPos.x, enmeyPosFloat3.y, enmeyPos.y));
			}
		}
		else
		{
			if (Collision::CircleVsCircleAndExtrusion(playerPos, player->bodyCollision->GetCollisionScale().x, enmeyPos, archerKokim.GetBodyCollision()->GetCollisionScale().x))
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
		if (warkerKokim.GetHp() <= 0) continue;
		if (Collision::SphereVsSphere(player->atkCollision->GetPos(), warkerKokim.GetModelData()->GetPos(), player->atkCollision->GetCollisionScale().x, warkerKokim.GetBodyCollision()->GetCollisionScale().x) && !warkerKokim.GetNowAsphyxia() && warkerKokim.GetDamageRecast() == 0)
		{
			warkerKokim.Damage(CharacterSystem::GetInstance()->GetPlayerAddress()->GetAttackDamage());
			warkerKokim.SetDamageRecast(50);
			DirectX::XMFLOAT3 emit = warkerKokim.GetModelData()->GetPos();
			ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle({ emit.x, emit.y + 20.0f, emit.z });
			PlaySoundMem(SoundLoader::GetInstance()->playerAttackHit.get());
			SetVolume(SoundLoader::GetInstance()->playerAttackHit.get(), 1.0f);
			if (warkerKokim.GetHp() <= 0)
			{
				UiSystem::GetInstance()->GetSpecialAttackGauge()->SetAttckPoint(/*MAX_PLAYER_DAMAGE * (0.7f + ((rand() % 500 + 1) / 1000.0f))*/5000);
				ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(warkerKokim.GetModelData()->GetPos());
			}
		}
	}

	for (auto& archerKokim : waveData->GetArcher())
	{
		if (archerKokim.GetHp() <= 0) continue;
		if (Collision::SphereVsSphere(player->atkCollision->GetPos(), archerKokim.GetModelData()->GetPos(), player->atkCollision->GetCollisionScale().x, archerKokim.GetBodyCollision()->GetCollisionScale().x) && !archerKokim.nowAsphyxia && archerKokim.damageRecast == 0)
		{
			archerKokim.Damage(CharacterSystem::GetInstance()->GetPlayerAddress()->GetAttackDamage());
			archerKokim.damageRecast = 50;
			DirectX::XMFLOAT3 emit = archerKokim.GetModelData()->GetPos();
			ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle({ emit.x, emit.y + 20.0f, emit.z });
			if (archerKokim.GetHp() <= 0)
			{
				UiSystem::GetInstance()->GetSpecialAttackGauge()->SetAttckPoint(MAX_PLAYER_DAMAGE * (0.7f + ((rand() % 500 + 1) / 1000.0f)));
				ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(archerKokim.GetModelData()->GetPos());
			}
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

		if (player->GetonGrdCollision())
		{
			DirectX::XMFLOAT3 grdCollisionPos = player->grdCollision->GetPos();
			grdCollisionPos.y = player->grdCollision->GetCollisionScale().x;
			if (Collision::SphereVsSphere(grdCollisionPos, warkerKokim.GetWeaponCollision()->GetPos(), player->grdCollision->GetCollisionScale().x, warkerKokim.GetWeaponCollision()->GetCollisionScale().x))
			{
				player->SuccessGuard();
			}
		}
		else
		{
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
				//	CharacterSystem::GetInstance()->GetPlayerAddress()->SetMoveSpeed({sp.x * 10, 0, sp.z * 10});
				//	ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle(warkerKokim.GetModelData()->GetPos());
			}
		}
	}

	for (auto& archerKokim : waveData->GetArcher())
	{
		if (archerKokim.state != ARCHER_STATE::STRIKE || archerKokim.nowAsphyxia) continue;

		if (player->guardCrash) return;
		if (player->GetonGrdCollision())
		{
			if (Collision::SphereVsSphere(player->grdCollision->GetPos(), archerKokim.GetWeaponCollision()->GetPos(), player->grdCollision->GetCollisionScale().x, archerKokim.GetWeaponCollision()->GetCollisionScale().x))
			{
				player->SuccessGuard();
				
				ParticleSystem::GetInstance()->SetSpark(archerKokim.GetWeaponCollision()->GetPos());
				
			}
		}
		else
		{
			if (player->guardCrash) return;
			DirectX::XMFLOAT3 tmp = archerKokim.GetWeaponCollision()->GetPos();
			tmp.y = 0.0f;
			if (Collision::SphereVsSphere(player->GetModelData().GetPos(), tmp, player->bodyCollision->GetCollisionScale().x, archerKokim.GetWeaponCollision()->GetCollisionScale().x))
			{
				player->SufferDamage(MAX_PLAYER_DAMAGE * (0.7f + ((rand() % 500 + 1) / 1000.0f)));
				//DirectX::XMVECTOR p = DirectX::XMLoadFloat3(&player->GetModelData().GetPos());
				//DirectX::XMVECTOR e = DirectX::XMLoadFloat3(&archerKokim.GetWeaponCollision()->GetPos());
				//DirectX::XMVECTOR d = DirectX::XMVectorSubtract(e, p);
				//d = DirectX::XMVectorNegate(d);
				//d = DirectX::XMVector3Normalize(d);
				//DirectX::XMFLOAT3 sp = {};
				//DirectX::XMStoreFloat3(&sp, d);
				//CharacterSystem::GetInstance()->GetPlayerAddress()->SetMoveSpeed({ sp.x * 10, 0, sp.z * 10 });
				//	ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle(warkerKokim.GetModelData()->GetPos());
			}
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

void CollisionJudge::EnemyVsEnemies()
{
	EnemyManager* enemyManager;
	enemyManager = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	WaveManager* waveManager;
	waveManager = enemyManager->GetWaveManager();

	Wave* waveData = &waveManager->GetWaves()[waveManager->GetWaveNowIndex()];

	std::vector<WarkerKokim> warkerKokim = waveData->GetWarker();
	std::vector<ArcherKokim> archerKokim = waveData->GetArcher();

	for (size_t i = 0; i < warkerKokim.size(); i++)
	{
		for (size_t j = 0; j < warkerKokim.size(); j++)
		{
			if (i == j) continue;

			DirectX::XMFLOAT3 pos1Float3 = warkerKokim[i].GetModelData()->GetPos();
			DirectX::XMFLOAT3 pos2Float3 = warkerKokim[j].GetModelData()->GetPos();
			DirectX::XMFLOAT2 pos1 = { pos1Float3.x, pos1Float3.z };
			DirectX::XMFLOAT2 pos2 = { pos2Float3.x, pos2Float3.z };
			if (Collision::SphereVsSphere(pos1Float3, pos2Float3, warkerKokim[i].GetBodyCollision()->GetCollisionScale().x, warkerKokim[j].GetBodyCollision()->GetCollisionScale().x))
			{
				Collision::CircleExtrusion(pos1, warkerKokim[i].GetBodyCollision()->GetCollisionScale().x, pos2, warkerKokim[j].GetBodyCollision()->GetCollisionScale().x);
				warkerKokim[i].GetModelData()->SetPos(DirectX::XMFLOAT3(pos1.x, pos1Float3.y, pos1.y));
			}
		}

		for (size_t j = 0; j < archerKokim.size(); j++)
		{
			DirectX::XMFLOAT3 pos1Float3 = warkerKokim[i].GetModelData()->GetPos();
			DirectX::XMFLOAT3 pos2Float3 = archerKokim[j].GetModelData()->GetPos();
			DirectX::XMFLOAT2 pos1 = { pos1Float3.x, pos1Float3.z };
			DirectX::XMFLOAT2 pos2 = { pos2Float3.x, pos2Float3.z };
			if (Collision::SphereVsSphere(pos1Float3, pos2Float3, warkerKokim[i].GetBodyCollision()->GetCollisionScale().x, archerKokim[j].GetBodyCollision()->GetCollisionScale().x))
			{
				Collision::CircleExtrusion(pos1, warkerKokim[i].GetBodyCollision()->GetCollisionScale().x, pos2, archerKokim[j].GetBodyCollision()->GetCollisionScale().x);
				warkerKokim[i].GetModelData()->SetPos(DirectX::XMFLOAT3(pos1.x, pos1Float3.y, pos1.y));
			}
		}
	}

	for (size_t i = 0; i < archerKokim.size(); i++)
	{
		for (size_t j = 0; j < archerKokim.size(); j++)
		{
			if (i == j) continue;

			DirectX::XMFLOAT3 pos1Float3 = archerKokim[i].GetModelData()->GetPos();
			DirectX::XMFLOAT3 pos2Float3 = archerKokim[j].GetModelData()->GetPos();
			DirectX::XMFLOAT2 pos1 = { pos1Float3.x, pos1Float3.z };
			DirectX::XMFLOAT2 pos2 = { pos2Float3.x, pos2Float3.z };
			if (Collision::SphereVsSphere(pos1Float3, pos2Float3, archerKokim[i].GetBodyCollision()->GetCollisionScale().x, archerKokim[j].GetBodyCollision()->GetCollisionScale().x))
			{
				Collision::CircleExtrusion(pos1, archerKokim[i].GetBodyCollision()->GetCollisionScale().x, pos2, archerKokim[j].GetBodyCollision()->GetCollisionScale().x);
				archerKokim[i].GetModelData()->SetPos(DirectX::XMFLOAT3(pos1.x, pos1Float3.y, pos1.y));
			}
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

void CollisionJudge::CameraVsStage()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	DirectX::XMFLOAT3 playerPosFloat3 = CameraSystem::GetInstance()->mainView.GetPos();
	DirectX::XMFLOAT2 playerPos = DirectX::XMFLOAT2(playerPosFloat3.x, playerPosFloat3.z);
	DirectX::XMFLOAT2 playerScale = DirectX::XMFLOAT2(10.0f, 10.0f);


	BG* bg;
	bg = ObjectSystem::GetInstance()->GetBgAddress();

	DirectX::XMFLOAT2 bgPos = DirectX::XMFLOAT2(bg->wallCollision->GetPos().x, bg->wallCollision->GetPos().z);
	DirectX::XMFLOAT2 bgScale = DirectX::XMFLOAT2(bg->wallCollision->GetCollisionScale().x + 200, bg->wallCollision->GetCollisionScale().z + 200);


	if (Collision::RectVsRectAndExtrusion(playerPos, bgPos, playerScale, bgScale))
	{
		CameraSystem::GetInstance()->mainView.SetPos(DirectX::XMFLOAT3(playerPos.x, playerPosFloat3.y, playerPos.y));
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

	if (waveData->GetArcher().size() > 0)
	{
		for (auto& archerKokim : waveData->GetArcher())
		{
			DirectX::XMFLOAT3 enemyPosFloat3 = archerKokim.GetBodyCollision()->GetPos();
			DirectX::XMFLOAT2 enemyPos = DirectX::XMFLOAT2(enemyPosFloat3.x, enemyPosFloat3.z);
			DirectX::XMFLOAT2 enemyScale = DirectX::XMFLOAT2(archerKokim.GetBodyCollision()->GetScale().x, archerKokim.GetBodyCollision()->GetScale().z);

			if (Collision::RectVsRectAndExtrusion(enemyPos, bgPos, enemyScale, bgScale))
			{
				//warkerKokim.SetModelPosition(DirectX::XMFLOAT3(enemyPos.x, enemyPosFloat3.y, enemyPos.y));
			}
		}
	}
}

void CollisionJudge::DeathBlowVsEnemies()
{
	Player* player;
	player = CharacterSystem::GetInstance()->GetPlayerAddress();

	if (!player->GetOnBlowCollision()) return;

	DirectX::XMFLOAT2 deathBlowPos = { player->blowCollision->GetPos().x, player->blowCollision->GetPos().z };
	float  deathBlowScale = player->blowCollision->GetScale().x;

	EnemyManager* enemyManager;
	enemyManager = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	WaveManager* waveManager;
	waveManager = enemyManager->GetWaveManager();

	Wave* waveData = &waveManager->GetWaves()[waveManager->GetWaveNowIndex()];


	if (waveData->GetWarker().size() > 0)
	{
		for (auto& warkerKokim : waveData->GetWarker())
		{
			DirectX::XMFLOAT3 enemyPosFloat3 = warkerKokim.GetBodyCollision()->GetPos();
			DirectX::XMFLOAT2 enemyPos = DirectX::XMFLOAT2(enemyPosFloat3.x, enemyPosFloat3.z);
			float enemyScale = warkerKokim.GetBodyCollision()->GetScale().x;

			if (Collision::CircleVsCircleAndExtrusion(deathBlowPos, deathBlowScale, enemyPos, enemyScale))
			{
				warkerKokim.Damage(10000);
				warkerKokim.SetDamageRecast(50);
				DirectX::XMFLOAT3 emit = warkerKokim.GetModelData()->GetPos();
				ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle({ emit.x, emit.y + 20.0f, emit.z });
				PlaySoundMem(SoundLoader::GetInstance()->playerAttackHit.get());
				SetVolume(SoundLoader::GetInstance()->playerAttackHit.get(), 1.0f);
				if (warkerKokim.GetHp() <= 0)
				{
					UiSystem::GetInstance()->GetSpecialAttackGauge()->SetAttckPoint(/*MAX_PLAYER_DAMAGE * (0.7f + ((rand() % 500 + 1) / 1000.0f))*/5000);
					ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(warkerKokim.GetModelData()->GetPos());
				}
			}
		}
	}

	if (waveData->GetArcher().size() > 0)
	{
		for (auto& archerKokim : waveData->GetArcher())
		{
			DirectX::XMFLOAT3 enemyPosFloat3 = archerKokim.GetBodyCollision()->GetPos();
			DirectX::XMFLOAT2 enemyPos = DirectX::XMFLOAT2(enemyPosFloat3.x, enemyPosFloat3.z);
			float enemyScale = archerKokim.GetBodyCollision()->GetScale().x;

			if (Collision::CircleVsCircleAndExtrusion(deathBlowPos, deathBlowScale, enemyPos, enemyScale))
			{
				archerKokim.Damage(10000);
				archerKokim.damageRecast = 50;
				DirectX::XMFLOAT3 emit = archerKokim.GetModelData()->GetPos();
				ParticleSystem::GetInstance()->SetPlayerAttackSlashParticle({ emit.x, emit.y + 20.0f, emit.z });
				if (archerKokim.GetHp() <= 0)
				{
					UiSystem::GetInstance()->GetSpecialAttackGauge()->SetAttckPoint(MAX_PLAYER_DAMAGE * (0.7f + ((rand() % 500 + 1) / 1000.0f)));
					ObjectSystem::GetInstance()->GetBuffAreaSystemAddress()->SetBuffArea(archerKokim.GetModelData()->GetPos());
				}
			}
		}
	}
}