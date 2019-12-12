#pragma once
#include <fstream>


#include <cereal/cereal.hpp>

#include <cereal/types/string.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/base_class.hpp>
class Wave;
class WaveManager
{
public:
	WaveManager();
	~WaveManager();

	void Save();
	void Load();


	std::vector<Wave>& GetWaves() 
	{
		return wave; 
	};

	int& GetWaveNowIndex() 
	{
		return waveNowIndex;
	};

private:
	std::vector<Wave> wave;
	int waveNowIndex=0;
	
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::make_nvp("wave", wave));
	}
};