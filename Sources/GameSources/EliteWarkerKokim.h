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




};