#include "BuffArea.h"
#include "easing.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Blender.h"
#include "ParticleSystem.h"
#include "Light.h"
#include "CameraSystem.h"
#include "SoundLoader.h"


void BuffArea::Init()
{
	//モデルのロード
	pArea = std::make_unique<Model>("Data/Assets/Model/val/AreaFrame.fbx", false);
	texture = std::make_unique<Billboard>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/ParticleTexure.png");
	onceLightNum = 0;
	onCollision  = false;
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
			s = easing::OutQuint((float)(ba.timer), 30.0f, ba.radius, 0.0f); //任意の大きさまで大きくする
			ba.modelData.SetScale({s, s ,s});
			ba.timer++;
			if (ba.timer > 30)
			{
				ba.state++;
			}
			break;
		case 1:	 //更新

			//if( rand() % 100 == 33 ) ParticleSystem::GetInstance()->SetBuffAreaParticle(ba.pos, ba.radius);
			if(rand() % 100 >= 80) ParticleSystem::GetInstance()->SetBuffAreaParticle({ ba.modelData.GetPos() .x, ba.modelData.GetPos() .y + 20, ba.modelData.GetPos().z}, ba.modelData.GetScale().x);

			if (ba.stopFlg) break;	//即break

			ba.pArea_collision->SetPos(ba.modelData.GetPos());
			ba.pArea_collision->SetScale({ba.modelData.GetScale().x , 200, ba.modelData.GetScale().z });


			s = ba.subRadius;
			ba.modelData.SetScale({ ba.modelData.GetScale().x - s, ba.modelData.GetScale().y - s ,ba.modelData.GetScale().z - s }); //縮む処理
			if (ba.modelData.GetScale().x <= 0) //大きさが０以下なら存在を消す
			{
				PlaySoundMem(SoundLoader::GetInstance()->magicDestroySe.get());
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

		//Light::GetInstance()->pointLight[ba.lightNum].range = ba.modelData.GetScale().x * 1.8f;
		//常時回転させる
		ba.modelData.SetAngleY(ba.modelData.GetAngle().y + ba.addRota);
		ba.modelData.SetPos({ ba.pos.x, ba.pos.y + 20, ba.pos.z });
	}

#ifdef _DEBUG
	ImGui();
#endif // _DEBUG


}

void BuffArea::Draw()
{
	pArea->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	SetRasterizerState(FrameWork::RS_CULL_BACK_TRUE);
	SetBlenderMode(BM_ALPHA);
	for (auto& ba : buffArea)
	{
		if (!ba.isExist || ba.stopFlg) continue;
		//if (ba.stopFlg) continue;
		pArea->Render(ba.modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), ba.modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	}
	SetRasterizerState(FrameWork::RS_CULL_BACK_TRUE);

	//SetBlenderMode(BM_ADD);
	texture->Begin(FrameWork::GetInstance().GetContext().Get());
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				{ba.pos.x, ba.pos.y + 10, ba.pos.z}, 1024 * 2, 0, 1024, 1024,
				{ DirectX::XMConvertToRadians(90) + CameraSystem::GetInstance()->mainView.GetRotateX(), 0, 0 }, {ba.modelData.GetScale().x * 3.0f, ba.modelData.GetScale().y * 3.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
			if(onCollision) ba.pArea_collision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime(), false);
		}
	}
	texture->End();


	//SetBlenderMode(BM_ALPHA);


}

void BuffArea::SetBuffArea(BuffAreaInfo b)
{
	PlaySoundMem(SoundLoader::GetInstance()->magicCreateSe.get());
	//これから生成するやつ以外は動きを止める
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.stopFlg = true;
	}
	//if (onceLightNum < 96)
	//{
	//	Light::GetInstance()->SetPointLight(onceLightNum, { b.pos.x, b.pos.y + 11, b.pos.z }, { 54.0f, 96.0f, 110.0f }, 0);
	//	b.lightNum = onceLightNum;
	//	onceLightNum++;
	//}
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

void BuffArea::ImGui()
{
	ImGui::Begin(u8"BuffArea");

	ImGui::Checkbox(u8"当たり判定表示##BuffArea", &onCollision);

	ImGui::End();

}