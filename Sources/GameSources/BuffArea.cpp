#include "BuffArea.h"
#include "easing.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Blender.h"
#include "ParticleSystem.h"
#include "Light.h"

void BuffArea::Init()
{
	//モデルのロード
	pArea = std::make_unique<Model>("Data/Assets/Model/val/auraeffect.fbx", false);
	pArea_collision = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(1.8*200, 200, 1.8*200));
	pArea_collision->SetColor({ 1, 0, 0, 1 });
	onceLightNum = 0;
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
			s = easing::OutQuint(ba.timer, 30.0f, ba.radius, 0.0f); //任意の大きさまで大きくする
			ba.modelData.SetScale({s, s ,s});
			ba.timer++;
			if (ba.timer > 30)
			{
				ba.state++;
			}
			break;
		case 1:	 //更新

			if (ba.stopFlg) break;	//即break

			pArea_collision->SetPos(ba.modelData.GetPos());
			pArea_collision->SetScale({ba.modelData.GetScale().x * 1.8f, 200, ba.modelData.GetScale().z * 1.8f });

			ParticleSystem::GetInstance()->SetBuffAreaParticle({ ba.modelData.GetPos() .x, ba.modelData.GetPos() .y + 20, ba.modelData.GetPos().z}, ba.modelData.GetScale().x*1.8f);

			s = ba.subRadius;
			ba.modelData.SetScale({ ba.modelData.GetScale().x - s, ba.modelData.GetScale().y - s ,ba.modelData.GetScale().z - s }); //縮む処理
			if (ba.modelData.GetScale().x <= 0) //大きさが０以下なら存在を消す
			{
				ba.isExist = false;
				BreakBuffArea();
				for (int i = 0; i < onceLightNum; i++)
				{
					Light::GetInstance()->pointLight[i].range = 0;
				}
				onceLightNum = 0;
			}
			break;
		}

		Light::GetInstance()->pointLight[ba.lightNum].range = ba.modelData.GetScale().x * 1.8f;
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

	//pArea_collision->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

}

void BuffArea::SetBuffArea(BuffAreaInfo &b)
{
	//これから生成するやつ以外は動きを止める
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.stopFlg = true;
	}
	if (onceLightNum < 96)
	{
		Light::GetInstance()->SetPointLight(onceLightNum, { b.pos.x, b.pos.y + 11, b.pos.z }, { 54.0f, 96.0f, 110.0f }, 0);
		b.lightNum = onceLightNum;
		onceLightNum++;
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
