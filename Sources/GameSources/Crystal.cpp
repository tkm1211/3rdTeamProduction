#include "Crystal.h"
#include "FrameWork.h"
#include "CameraSystem.h"
#include "Blender.h"

void CrystalSystem::Init()
{
	crystal = std::make_unique<Model>("Data/Assets/Model/cl/crystal.fbx", false, true);
}

void CrystalSystem::Update()
{
	for (int i = 0; i < data.size(); i++)
	{
		if (!data.at(i).isExist) continue;
		data.at(i).crystalData.SetAngleY(data.at(i).crystalData.GetAngle().y + (2 * 0.01745f));
	}
}	

void CrystalSystem::Draw()
{
	//pModelBatch->Begin(ShaderSystem::GetInstance()->GetShaderOfStaticMeshBatch(), false);
	//for (int i = 0; i < MAX_INSTANCE; i++)
	//{
	//	pModelBatch->Render(batchData[i], /*modelBatchData[i].GetWorldMatrix(),*/ CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
	//}
	//pModelBatch->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	SetBlenderMode(BM_ALPHA);
	//crystal->Begin(ShaderSystem::GetInstance()->GetShaderOfStaticMeshBatch(), false);
	//for (int i = 0; i < data.size(); i++)
	//{
	//	if (!data.at(i).isExist) continue;
	//	data.at(i).crystalData.SetColor({3.0f, 3.0f ,3.0f, 0.6f});
	//	//data.at(i).crystalData.SetScale({10.0f, 10.0f, 10.0f});
	//	data.at(i).crystalData.SetPosY(80.0f);
	//	crystal->Render(data.at(i).crystalData, CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), FrameWork::GetInstance().GetElapsedTime());
	//}
	//crystal->End(DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.6f));
	SetBlenderMode(BM_NONE);
}

void CrystalSystem::PopCrystal(DirectX::XMFLOAT3 pos)
{
	CrystalData tmp;

	tmp.isExist = true;
	tmp.crystalData.SetPos(pos);

	for (int i = 0; i < data.size(); i++)
	{
		if (data.at(i).isExist) continue;
		data.at(i).SetCrystal(tmp);
		return;
	}

	data.push_back(tmp);

}

void CrystalSystem::CrystalDestroy()
{
	for (int i = 0; i < data.size(); i++)
	{
		if (!data.at(i).isExist) continue;
		data.at(i).Clear();
	}
}