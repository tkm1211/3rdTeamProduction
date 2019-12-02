#include "BuffArea.h"
#include "easing.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Blender.h"


void BuffArea::Init()
{
	//モデルのロード
	pArea = std::make_unique<Model>("Data/Assets/Model/val/auraeffect.fbx", false);
}

void BuffArea::UnInit()
{
}

void BuffArea::Update()
{
	float s = 0;	//スケールを置く用
	for (auto &ba : buffArea)
	{
		if (!ba.isExist) continue;
		switch (ba.state)
		{
		case 0: //出現
			s = easing::OutQuint(static_cast<float>(ba.timer), 30.0f, ba.radius, 0.0f); //任意の大きさまで大きくする
			ba.modelData.SetScale({s, s ,s});
			ba.timer++;
			if (ba.timer > 30) ba.state++;
			break;
		case 1:	 //更新
			if (ba.stopFlg) break;	//即break

			s = ba.subRadius;
			ba.modelData.SetScale({ ba.modelData.GetScale().x - s, ba.modelData.GetScale().y - s ,ba.modelData.GetScale().z - s }); //縮む処理
			if (ba.modelData.GetScale().x <= 0) //大きさが０以下なら存在を消す
			{
				ba.isExist = false;
				BreakBuffArea();
			}
			break;
		}

		//常時回転させる
		ba.modelData.SetAngleY(ba.modelData.GetAngle().y + ba.addRota);
		ba.modelData.SetPos(ba.pos);
	}

}

void BuffArea::Draw()
{
	pArea->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	
	SetBlenderMode(BM_ADD);
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		pArea->Render(ba.modelData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), ba.modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	}
	SetBlenderMode(BM_ALPHA);

}

void BuffArea::SetBuffArea(BuffAreaInfo &b)
{
	//これから生成するやつ以外は動きを止める
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.stopFlg = true;
	}

	//生成
	for (auto& ba : buffArea)
	{
		if (ba.isExist) continue; //存在フラグがfalseがいるならそいつを生成させる
		ba.Init(b);
		return;
	}
	//それ以外ならpush backして増やす
	buffArea.push_back(b);
}


void BuffArea::SetBuffArea(DirectX::XMFLOAT3 pos, float rad, float subRad)
{
	BuffAreaInfo ba;
	ba.Init(pos, rad, subRad);
	ba.addRota = (rand() % 12 - 6 ) * 0.01745f;
	SetBuffArea(ba);
}

void BuffArea::BreakBuffArea()
{
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.isExist = false;
	}
}
