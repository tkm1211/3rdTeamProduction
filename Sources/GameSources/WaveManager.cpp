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
	ifs.open("./Data/Document/Waves.bin", std::ios::binary);
	if(ifs)
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(wave);
	}
	ifs.close();

	if (wave.size() > 0)
	{
		for (int i =0; i< wave.size(); i++)
		{
			for (auto& w : wave.at(i).GetWarker())
			{
				w.Init();
			}
			for (auto& a : wave.at(i).GetArcher())
			{
				a.Init();
			}
			for (auto& ew : wave.at(i).GetEliteWarker())
			{
				ew.Init();
			}
		}
	}
}

WaveManager::~WaveManager()
{


}


void WaveManager::Save()
{
	std::ofstream ofs;
	ofs.open("./Data/Document/Waves.bin", std::ios::binary);
	{
		cereal::JSONOutputArchive o_archive(ofs);
		o_archive(wave);
	}
	ofs.close();
}

void WaveManager::Load()
{
	std::ifstream ifs;
	ifs.open("./Data/Document/Waves.bin", std::ios::binary);
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(wave);
	}
	ifs.close();

	CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetWaveManager()->GetWaveNowIndex() = 0;
}