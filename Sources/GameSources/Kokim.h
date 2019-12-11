#pragma once

#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
class Kokim
{
public:

	int GetIndex() { return index; };
	int GetHp() { return hp; };
	std::shared_ptr<OBJ3D> GetModelData() { return modelData; };
	CollisionPrimitive* GetBodyCollision() { return bodyCol.get(); };

	int Damage(int damage) { hp-=damage; };
	void SetHp(int hp) { this->hp = hp; };

	std::shared_ptr<CollisionPrimitive> bodyCol;
	std::shared_ptr<OBJ3D> modelData;

	int index=0;
	int hp=0;


	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			cereal::make_nvp("modelData", modelData),
			cereal::make_nvp("index", index),
			cereal::make_nvp("hp", hp));
	}
};