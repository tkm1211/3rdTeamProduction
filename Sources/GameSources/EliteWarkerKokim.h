#pragma once
#include "AI.h"
#include "Kokim.h"



class EliteWarkerKokim:
	 public AI,public Kokim
{
public:
	EliteWarkerKokim() {};
	EliteWarkerKokim(int num);
	virtual ~EliteWarkerKokim() {};

	void Init();

	void Update();


private:



public:
	//template<class Archive>
	//void serialize(Archive & archive)
	//{
	//	archive(
	//		cereal::make_nvp("modelData", modelData),
	//		cereal::make_nvp("index", index),
	//		cereal::make_nvp("hp", hp),
	//		cereal::make_nvp("velocity", velocity));
	//}

};