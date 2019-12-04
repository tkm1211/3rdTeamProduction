#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
class BuffArea
{
private:
	struct BuffAreaInfo
	{
		DirectX::XMFLOAT3 pos;		//中心座標
		float radius;							//半径
		float subRadius;					//半径が縮むスピード
		float addRota;						//回転
		int state;
		int timer;								//出現時のeasing用
		bool isExist;							//生存フラグ
		bool stopFlg;						//半径の縮むのを止めるフラグ
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
	std::unique_ptr<CollisionPrimitive> pArea_collision;

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

	void SetBuffArea(DirectX::XMFLOAT3 pos, float rad, float subRad);//pos : 中心座標, rad : 半径, subRad : 1フレームに縮む半径


};