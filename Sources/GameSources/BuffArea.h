#pragma once
#include "Model.h"
#include "OBJ3D.h"

class BuffArea
{
private:
	struct BuffAreaInfo
	{
		DirectX::XMFLOAT3 pos;		//SΐW
		float radius;							//Όa
		float subRadius;					//ΌaͺkήXs[h
		float addRota;						//ρ]
		int state;
		int timer;								//o»Μeasingp
		bool isExist;							//ΆΆtO
		bool stopFlg;						//ΌaΜkήΜπ~ίιtO
		OBJ3D modelData;

		void Init(DirectX::XMFLOAT3 p, float r, float sr)
		{
			pos = p;
			radius = r;
			subRadius = sr;
			addRota = 0.0f;
			isExist = true;
			stopFlg = false;
			state = 0;
			timer = 0;
			modelData.Init();
			modelData.SetScale({ 0.0f, 0.0f, 0.0f });
		}
		void Init(BuffAreaInfo &ba)
		{
			pos = ba.pos;
			radius = ba.radius;
			subRadius = ba.subRadius;
			addRota = ba.addRota;
			isExist = true;
			stopFlg = false;
			state = 0;
			timer = 0;
			modelData.Init();
			modelData.SetScale({ 0.0f, 0.0f, 0.0f });
		}

	};
	std::vector<BuffAreaInfo> buffArea;

	std::unique_ptr<Model> pArea;

private:
	void SetBuffArea(BuffAreaInfo &b);
	void BreakBuffArea();
public:

	BuffArea() {}
	~BuffArea() {}


	void Init();
	void Update();
	void Draw();
	void UnInit();

	void SetBuffArea(DirectX::XMFLOAT3 pos, float rad, float subRad);//pos : SΐW, rad : Όa, subRad : 1t[ΙkήΌa


};