#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
#include "Billboard.h"

class  BuffAreaInfo
{
public:
	DirectX::XMFLOAT3 pos;				//中心座標
	float radius;						//半径
	float subRadius;					//半径が縮むスピード
	float addRota;						//回転
	int state;
	int timer;							//出現時のeasing用
	int lightNum;
	bool isExist;						//生存フラグ
	bool stopFlg;						//半径の縮むのを止めるフラグ
	bool enableBuff;
	OBJ3D modelData;
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
		pArea_collision = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(1.8 * 200, 200, 1.8 * 200));
		pArea_collision->SetColor({ 1, 0, 0, 1 });
	}

};

class BuffAreaSystem
{
private:

	std::unique_ptr<Model> pArea;

	int onceLightNum;
	int enabledBuffAreaNum;
	bool onCollision;
public:
	std::vector<BuffAreaInfo> buffArea;
	std::unique_ptr<Billboard> texture;
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

	void SetBuffArea(DirectX::XMFLOAT3 pos, float rad, float subRad);//pos : 中心座標, rad : 半径, subRad : 1フレームに縮む半径

	void checkBuff(BuffAreaInfo* obj)
	{
		if (obj->enableBuff) return;

		obj->enableBuff = true;
		enabledBuffAreaNum++;
	}

};