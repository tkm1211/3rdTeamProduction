#include "WaveManager.h"
#include "Wave.h"
#include "CharacterSystem.h"
WaveManager::WaveManager()
{

	for (auto &w : wave)
	{
		w.SetTimer(0);
	}
	std::ifstream ifs;
	ifs.open("Waves.bin", std::ios::binary);
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(wave);
	}
	ifs.close();

	for (auto& w : wave.at(waveNowIndex).GetWarker())
	{
		w.Init();
	}
	for (auto& a : wave.at(waveNowIndex).GetArcher())
	{
		a.Init();
	}
	for (auto& ew : wave.at(waveNowIndex).GetEliteWarker())
	{
		ew.Init();
	}
}

WaveManager::~WaveManager()
{


}


void WaveManager::Save()
{
	std::ofstream ofs;
	ofs.open("Waves.bin", std::ios::binary);
	{
		cereal::JSONOutputArchive o_archive(ofs);
		o_archive(wave);
	}
	ofs.close();
}

void WaveManager::Load()
{
	std::ifstream ifs;
	ifs.open("Waves.bin", std::ios::binary);
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(wave);
	}
	ifs.close();

	CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex() = 0;
}