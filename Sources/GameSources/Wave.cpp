#include "Wave.h"
#include "CharacterSystem.h"
#include "Editer.h"
Wave::Wave()
{


}


Wave::~Wave()
{


}

void Wave::Update()
{
	EnemyManager* enmMgr = CharacterSystem::GetInstance()->GetEnemyManagerAddress();

	for (auto &arc : archer)
	{
		arc.Update();
		if (arc.arrow)
		{
			arc.arrow->Update();
		}
	}
	for (auto &wrk : warker)
	{
		wrk.Update();
	}
	for (auto &ewrk : eliteWarker)
	{
		ewrk.Update();
	}

	timer++;

}
