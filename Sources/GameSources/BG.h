#pragma once
#include "FrameWork.h"
#include "SkinnedMeshBatch.h"
#include "OBJ3D.h"
#include "Model.h"
#include "MathFunction.h"
#include "CameraSystem.h"
#include "CameraControl.h"
#include "BGEditor.h"

#undef max
#undef min

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/string.hpp>

class BGModelManager
{
public:
	std::unique_ptr<Model> ground;
	std::unique_ptr<Model> wall;

public:
	BGModelManager() {}
	~BGModelManager() {}

	static BGModelManager* GetInstance()
	{
		static BGModelManager instance;
		return &instance;
	}

public:
	void Init();
};


class BgData
{
private:
public:
	int type;
	OBJ3D obj;
	int GetType() { return type; }
	OBJ3D GetOBJ3D() { return obj; }
	void SetOBJ3D(OBJ3D _obj) { obj = _obj; }

};

class BG
{

private:

	enum ModelType
	{
		STONE1, // êŒ1
		STONE2, // êŒ2
		GRASS,  // ëê
		TREE,   // ñÿ
		END
	};

	std::vector<std::unique_ptr<Model>> bgModel;
	std::vector<BgData> bgObject;
	OBJ3D groundData;
	OBJ3D wallData;

public:
	std::unique_ptr<CollisionPrimitive> wallCollision;

public:
	BG() {}
	~BG() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void ImGui();

	void LoadModel(int type)
	{
		if (type == ModelType::STONE1)
		{
			//bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Rock01_MDL.fbx", true));
		}
		else if (type == ModelType::STONE2)
		{
			//bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Rock02_MDL.fbx", true));
		}
		else if (type == ModelType::GRASS)
		{
			bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Grass_MDL.fbx", true));
		}
		else if (type == ModelType::TREE)
		{
			//bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Wood_MDL.fbx", true));
		}
	}

};


