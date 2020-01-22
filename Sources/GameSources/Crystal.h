#pragma once

#include "SkinnedMeshBatch.h"
#include "Model.h"

class CrystalData
{
public:
	OBJ3DInstance crystalData;
	bool isExist;

public:
	CrystalData() {}
	~CrystalData() {}
	CrystalData(const CrystalData& obj)
	{
		crystalData.Init();
		crystalData.SetIsAnimation(false);
		crystalData = obj.crystalData;
		isExist = obj.isExist;
	}

	void Clear()
	{
		crystalData.Init();
		crystalData.SetIsAnimation(false);
		isExist = false;
	}

	void SetCrystal(CrystalData& obj)
	{
		crystalData.Init();
		crystalData = obj.crystalData;
		isExist = obj.isExist;
	}

};

class CrystalSystem
{

private:
	std::unique_ptr<Model> crystal;
	std::vector<CrystalData> data;

public:
	CrystalSystem() {}
	~CrystalSystem() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void CrystalDestroy();
	void PopCrystal(DirectX::XMFLOAT3 pos);

	static CrystalSystem* GetInstance()
	{
		static CrystalSystem instance;
		return &instance;
	}

};