#pragma once

#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
class Kokim
{
public:

	int GetIndex() { return index; };
	int GetHp() { return hp; };
	float& GetVelocity() { return velocity; };
	std::shared_ptr<OBJ3D> GetModelData() { return modelData; };
	CollisionPrimitive* GetBodyCollision() { return bodyCol.get(); };
	CollisionPrimitive* GetWeaponCollision() { return weaponCol.get(); };


	int Damage(int damage) { hp-=damage; };
	void SetHp(int hp) { this->hp = hp; };
	void SetVelocity(float velocity) { this->velocity = velocity; };

	std::shared_ptr<CollisionPrimitive> bodyCol;
	std::shared_ptr<CollisionPrimitive> weaponCol;
	std::shared_ptr<OBJ3D> modelData;

	int index=0;
	int hp=10;
	float velocity = 10;

	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(
			cereal::make_nvp("modelData", modelData),
			cereal::make_nvp("index", index),
			cereal::make_nvp("hp", hp),
			cereal::make_nvp("velocity", velocity)
			);
	}
};