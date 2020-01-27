#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
#include "Billboard.h"

class BuffModelManager
{
public:
	std::unique_ptr<Model> pArea;
	std::unique_ptr<Model> pMainArea;
	std::unique_ptr<Billboard> texture;

public:
	BuffModelManager() {}
	~BuffModelManager() {}

	static BuffModelManager* GetInstance()
	{
		static BuffModelManager instance;
		return &instance;
	}

public:
	void Init();
};


class  BuffAreaInfo
{
public:
	DirectX::XMFLOAT3 pos;				//íÜêSç¿ïW
	float radius;						//îºåa
	float subRadius;					//îºåaÇ™èkÇﬁÉXÉsÅ[Éh
	float addRota;						//âÒì]
	int state;
	int timer;							//èoåªéûÇÃeasingóp
	int lightNum;
	bool isExist;						//ê∂ë∂ÉtÉâÉO
	bool stopFlg;						//îºåaÇÃèkÇﬁÇÃÇé~ÇﬂÇÈÉtÉâÉO
	bool enableBuff;
	OBJ3D modelData;
	OBJ3D cryData;
	std::unique_ptr<CollisionPrimitive> pArea_collision;

public:
	BuffAreaInfo() {}
	~BuffAreaInfo() {}

	BuffAreaInfo(const BuffAreaInfo& ba)
	{ 
		pos = ba.pos;
		radius = ba.radius;
		subRadius = ba.subRadius;
		addRota = ba.addRota;
		lightNum = ba.lightNum;
		isExist = true;
		stopFlg = ba.stopFlg;
		state = ba.state;
		timer = ba.timer;
		enableBuff = ba.enableBuff;
		modelData = ba.modelData;
		cryData = ba.cryData;
		pArea_collision = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(1.8 * 200, 200, 1.8 * 200));
		pArea_collision->SetColor({ 1, 0, 0, 1 });
	}
	void Init(BuffAreaInfo ba)
	{
		pos = ba.pos;
		radius = ba.radius;
		subRadius = ba.subRadius;
		addRota = ba.addRota;
		lightNum = ba.lightNum;
		isExist = true;
		stopFlg = false;
		enableBuff = false;
		state = 0;
		timer = 0;
		modelData.Init();
		modelData.SetScale({ 0.0f, 0.0f, 0.0f });
		cryData.Init();
		cryData.SetScale({ 0.0f, 0.0f, 0.0f });
		pArea_collision = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(1.8 * 200, 200, 1.8 * 200));
		pArea_collision->SetColor({ 1, 0, 0, 1 });
	}
	void Init(DirectX::XMFLOAT3 p, float r, float sr)
	{
		pos = p;
		radius = r;
		subRadius = sr;
		addRota = 0.0f;
		isExist = true;
		stopFlg = false;
		enableBuff = false;
		state = 0;
		timer = 0;
		lightNum = -1;
		modelData.Init();
		modelData.SetScale({ 0.0f, 0.0f, 0.0f });
		cryData.Init();
		cryData.SetScale({ 0.0f, 0.0f, 0.0f });
		pArea_collision = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(1.8 * 200, 200, 1.8 * 200));
		pArea_collision->SetColor({ 1, 0, 0, 1 });
	}

};

class BuffAreaSystem
{
private:
	struct AreaModelData
	{
		float timer;
		int state;
		OBJ3D areaModelData;
		float addRad;
	};

	float MAG = 0.01f;
	float SUB_RAD = 0.1f;
	float RADIUS = 500.0f;

	AreaModelData areaModelData;


	int onceLightNum;
	int enabledBuffAreaNum;
	bool onCollision;
	int allArea;
	float areaFrameSubRad;
public:
	std::vector<BuffAreaInfo> buffArea;

	int num;
private:
	void SetBuffArea(BuffAreaInfo b);
	void BreakBuffArea();
public:
	BuffAreaSystem(const BuffAreaSystem& obj) {}
	BuffAreaSystem() {}
	~BuffAreaSystem() {}


	void Init();
	void Update();
	void Draw();
	void UnInit();

	void ImGui();

	void SetBuffArea(DirectX::XMFLOAT3 pos);//pos : íÜêSç¿ïW, rad : îºåa, subRad : 1ÉtÉåÅ[ÉÄÇ…èkÇﬁîºåa

	void checkBuff(BuffAreaInfo* obj)
	{
		if (obj->enableBuff) return;

		obj->enableBuff = true;
		enabledBuffAreaNum++;
	}


	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			cereal::make_nvp("î{ó¶", MAG),
			cereal::make_nvp("å∏ÇÈó ", SUB_RAD),
			cereal::make_nvp("îºåa", RADIUS)
		);
	}


};