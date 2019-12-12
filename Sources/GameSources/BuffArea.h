#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
#include "Billboard.h"

class  BuffAreaInfo
{
public:
	DirectX::XMFLOAT3 pos;				//���S���W
	float radius;						//���a
	float subRadius;					//���a���k�ރX�s�[�h
	float addRota;						//��]
	int state;
	int timer;							//�o������easing�p
	int lightNum;
	bool isExist;						//�����t���O
	bool stopFlg;						//���a�̏k�ނ̂��~�߂�t���O
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

	void SetBuffArea(DirectX::XMFLOAT3 pos, float rad, float subRad);//pos : ���S���W, rad : ���a, subRad : 1�t���[���ɏk�ޔ��a

	void checkBuff(BuffAreaInfo* obj)
	{
		if (obj->enableBuff) return;

		obj->enableBuff = true;
		enabledBuffAreaNum++;
	}

};