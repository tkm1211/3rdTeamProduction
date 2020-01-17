#pragma once
#include "FrameWork.h"
#include "SkinnedMeshBatch.h"
#include "OBJ3D.h"
#include "Model.h"
#include "MathFunction.h"
#include "CameraSystem.h"
#include "CameraControl.h"

#undef max
#undef min

#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/base_class.hpp>
#include <cereal/types/string.hpp>


class BGObject
{
private:
	int type;
	OBJ3D obj;

public:
	 BGObject() {}
	~BGObject() {}

public:
	void SetData(int _type, OBJ3D _obj)
	{
		type = _type;
		obj = _obj;
	}

	int GetType() { return type; }
	OBJ3D GetOBJ3D() { return obj; }
	void SetOBJ3D(OBJ3D _obj) { obj = _obj; }

public:
	template <class T>
	void serialize(T& archive)
	{
		archive
		(
			CEREAL_NVP(type),
			CEREAL_NVP(obj)
		);
	}
};

class BGEditor
{
private:
#if 0
	enum ModelType
	{
		WALL,  // ï«
		STONE, // êŒ
		GRASS, // ëê
		TREE,  // ñÿ
		END
	};
#else
	enum ModelType
	{
		STONE1, // êŒ1
		STONE2, // êŒ2
		GRASS,  // ëê
		TREE,   // ñÿ
		END
	};
#endif

	bool on;
	bool target;
	int type;
	int lookCnt;
	bool lookFlg;
	int clickCnt;
	int backUpCnt;

	std::vector<std::unique_ptr<Model>> bgModel;
	std::vector<BGObject> bgObject;

	std::unique_ptr<Model> ground;
	std::unique_ptr<Model> wall;

	OBJ3D groundData;
	OBJ3D wallData;

public:
	 BGEditor() {}
	~BGEditor() {}

	static BGEditor* GetInstance()
	{
		static BGEditor instance;
		return &instance;
	}

public:
	void Init();
	void UnInit();
	void Update();
	void Draw();

	bool GetOn() { return on; }

private:
	void LoadFile();
	void SaveFile();

	void LoadBackUpFile();
	void SaveBackUpFile();

	void GUI();
	void Click();
	void Edit(OBJ3D* obj);

	void LoadModel(int type)
	{
		if (type == ModelType::STONE1)
		{
			bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Rock01_MDL.fbx", true));
		}
		else if (type == ModelType::STONE2)
		{
			bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Rock02_MDL.fbx", true));
		}
		else if (type == ModelType::GRASS)
		{
			bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Grass_MDL.fbx", true));
		}
		else if (type == ModelType::TREE)
		{
			bgModel.push_back(std::make_unique<Model>("Data/Assets/Model/BG/Wood_MDL.fbx", true));
		}
	}

public:
	template <class T>
	void serialize(T& archive)
	{
		archive
		(
			CEREAL_NVP(bgObject)
		);
	}
};