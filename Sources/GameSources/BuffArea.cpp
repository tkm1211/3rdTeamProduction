#include "BuffArea.h"
#include "easing.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Blender.h"
#include "ParticleSystem.h"
#include "Light.h"
#include "CameraSystem.h"
#include "SoundLoader.h"
#include <fstream>
#include <string>
#include "CharacterSystem.h"
#include "Crystal.h"

void BuffAreaSystem::Init()
{
	//モデルのロード
	pArea = std::make_unique<Model>("Data/Assets/Model/val/AreaFrame.fbx", false);
	areaModelData.areaModelData.Init();
	areaModelData.state = 0;
	areaModelData.timer = 0;
	areaModelData.addRad = 0;

	areaFrameSubRad = 0.0f;

	pCrystal = std::make_unique<Model>("Data/Assets/Model/val/crystal.fbx", false);
	texture = std::make_unique<Billboard>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/ParticleTexure.png");
	onceLightNum = 0;
	enabledBuffAreaNum = 0;
	onCollision = false;
	allArea = 0;
	// json読み込み
	std::ifstream ifs;
	ifs.open("./Data/Document/BuffArea.json", std::ios::out);
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(*this);
	}
	ifs.close();

}

void BuffAreaSystem::UnInit()
{
}

void BuffAreaSystem::Update()
{
	float s = 0;	//スケールを置く用
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		switch (ba.state)
		{
		case 0: //出現
			s = easing::OutQuint((float)(ba.timer), 30.0f, ba.radius, 0.0f); //任意の大きさまで大きくする
			ba.modelData.SetScale({ s, s ,s });
			ba.timer++;
			if (ba.timer > 30)
			{
				ba.state++;
			}
			break;
		case 1:	 //更新

			//if( rand() % 100 == 33 ) ParticleSystem::GetInstance()->SetBuffAreaParticle(ba.pos, ba.radius);
			if (rand() % 100 >= 80) ParticleSystem::GetInstance()->SetBuffAreaParticle({ ba.modelData.GetPos().x, ba.modelData.GetPos().y + 20, ba.modelData.GetPos().z }, ba.modelData.GetScale().x);

			if (ba.stopFlg)
			{
				break;	//即break
			}
			ba.pArea_collision->SetPos(ba.modelData.GetPos());
			ba.pArea_collision->SetScale({ ba.modelData.GetScale().x , 200, ba.modelData.GetScale().z });


			s = ba.subRadius;
			ba.modelData.SetScale({ ba.modelData.GetScale().x - s, ba.modelData.GetScale().y - s ,ba.modelData.GetScale().z - s }); //縮む処理
			if (ba.modelData.GetScale().x <= 0) //大きさが０以下なら存在を消す
			{
				//PlaySoundMem(SoundLoader::GetInstance()->magicDestroySe.get());
				//PlaySoundMem(SoundLoader::GetInstance()->crystalBreakSe.get());
				enabledBuffAreaNum = 0;
				BreakBuffArea();
				ba.isExist = false;
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
		ba.cryData.SetPos({ ba.pos.x, ba.pos.y + 50, ba.pos.z });
		ba.cryData.SetScale({ 30, 30, 30 });
		ba.cryData.SetColor({ 1, 1, 1, 0.5f });

	}

	CharacterSystem::GetInstance()->GetPlayerAddress()->SetAttackMag(enabledBuffAreaNum);

	if (areaModelData.state == 1)
	{
		s = easing::OutQuint(areaModelData.timer, 30.0f,RADIUS, 0.0f); //任意の大きさまで大きくする
		areaModelData.areaModelData.SetScale({ s, s ,s });
		areaModelData.timer++;
		areaModelData.areaModelData.SetAngleY(areaModelData.areaModelData.GetAngle().y + areaModelData.addRad);
		if (areaModelData.timer > 30)
		{
			areaModelData.state = 2;
		}
	}
	else if (areaModelData.state == 2)
	{
		areaModelData.areaModelData.SetAngleY(areaModelData.areaModelData.GetAngle().y + areaModelData.addRad);
		s = areaModelData.areaModelData.GetScale().x;
		areaModelData.areaModelData.SetScale({ s - areaFrameSubRad, s - areaFrameSubRad, s - areaFrameSubRad });
	}
	//ImGui();
}

void BuffAreaSystem::Draw()
{
	if (areaModelData.state >= 1)
	{
		//areaModelData.areaModelData.SetScale({ 30, 30, 30 } );
		SetRasterizerState(FrameWork::RS_CULL_NONE_TRUE);
		pArea->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		pArea->Render(areaModelData.areaModelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), areaModelData.areaModelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		SetRasterizerState(FrameWork::RS_CULL_BACK_TRUE);
	}

	SetBlenderMode(BM_ALPHA);
	//pCrystal->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	//for (auto& ba : buffArea)
	//{
	//	if (!ba.isExist) continue;
	//	//if (ba.stopFlg) continue;
	//	pCrystal->Render(ba.cryData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
	//		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), ba.cryData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	//}

	//SetBlenderMode(BM_ADD);
	texture->Begin(FrameWork::GetInstance().GetContext().Get());
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		{
			texture->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
				{ ba.pos.x, ba.pos.y + 10, ba.pos.z }, 1024 * 2, 0, 1024, 1024,
				{ DirectX::XMConvertToRadians(90) + CameraSystem::GetInstance()->mainView.GetRotateX(), 0, 0 }, { ba.modelData.GetScale().x * 3.0f, ba.modelData.GetScale().y * 3.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
			if (onCollision) ba.pArea_collision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime(), false);
		}
	}
	texture->End();


	//SetBlenderMode(BM_ALPHA);


}

void BuffAreaSystem::SetBuffArea(BuffAreaInfo b)
{
	//PlaySoundMem(SoundLoader::GetInstance()->magicCreateSe.get());
	//SetVolume(SoundLoader::GetInstance()->magicCreateSe.get(), 0.1f);

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


void BuffAreaSystem::SetBuffArea(DirectX::XMFLOAT3 pos)
{
	CrystalSystem::GetInstance()->PopCrystal(pos);

	PlaySoundMem(SoundLoader::GetInstance()->crystalStart.get());

	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		allArea++;
	}

	float rad = RADIUS;
	float subRad = SUB_RAD + (1 + (MAG * (allArea + 1)));
	allArea = 0;
	BuffAreaInfo ba;
	ba.Init(pos, rad, subRad);
	ba.addRota = 4 * 0.01745f;
	SetBuffArea(ba);
	areaModelData.state = 1;
	areaModelData.timer = 0;
	areaModelData.areaModelData.SetPos({pos.x, pos.y + 10, pos.z});
	areaModelData.areaModelData.SetScale({0, 0, 0});
	areaModelData.addRad = ba.addRota;
	areaFrameSubRad = subRad;
}

void BuffAreaSystem::BreakBuffArea()
{
	PlaySoundMem(SoundLoader::GetInstance()->crystalCrash.get());

	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.isExist = false;
		ParticleSystem::GetInstance()->SetCrystalDestroy({ba.pos.x, ba.pos.y + 80, ba.pos.z});
	}
	areaModelData.state = 0;
	CrystalSystem::GetInstance()->CrystalDestroy();
	CharacterSystem::GetInstance()->GetEnemyManagerAddress()->AllDelete();
}

void BuffAreaSystem::ImGui()
{
	ImGui::Begin(u8"BuffArea");

	ImGui::Text(u8"当たった数   : %d", enabledBuffAreaNum);
	ImGui::Text(u8"出てる数   : %d", allArea);
	ImGui::Checkbox(u8"当たり判定表示##BuffArea", &onCollision);

	ImGui::DragFloat(u8"倍率##BuffArea"  , &MAG);
	ImGui::DragFloat(u8"減る量##BuffArea", &SUB_RAD);
	ImGui::DragFloat(u8"半径##BuffArea"  , &RADIUS);

	if (ImGui::Button(u8"生成##BuffArea"))
	{
		SetBuffArea(CharacterSystem::GetInstance()->GetPlayerAddress()->GetModelData().GetPos());
	}

	//cereal でjson とbinary に保存
	static std::string data_name;
	if (ImGui::Button("SAVE"))
	{
		data_name = "./Data/Document/BuffArea.json";
		std::ofstream ofs;
		ofs.open(data_name.c_str(), std::ios::out);
		{
			cereal::JSONOutputArchive o_archive(ofs);
			o_archive(*this);
		}
		ofs.close();
	}

	ImGui::End();

}