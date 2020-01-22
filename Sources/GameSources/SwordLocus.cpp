#include "SwordLocus.h"
#include "CameraSystem.h"
#include "CharacterSystem.h"

void SwordLocus::Init()
{
	// geometry collision
	for (int i = 0; i < 9 * 11 + 1; i++)
	{
		ci[i].handPoint = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
		ci[i].handPoint->SetColor({ 1, 0, 0, 1 });

		ci[i].swordPoint = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
		ci[i].swordPoint->SetColor({ 0, 0, 1, 1 });
	}

	spr = std::make_unique<SwordLocusSprite>(FrameWork::GetInstance().GetDevice().Get(), L"Data/Assets/Texture/swordLocus.png");

	for (int i = 0; i < 9 * 11 + 1; i++)
	{
		spr->meshInfo[i].dPos = {0, 0, 0};
		spr->meshInfo[i].uPos = {0, 0, 0};
	}

}

void SwordLocus::Update()
{

}

void SwordLocus::Draw()
{
	//for (int i = 0; i < 10; i++)
	//{
	//	ci[i].handPoint->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	//	ci[i].swordPoint->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	//}
	if (CharacterSystem::GetInstance()->GetPlayerAddress()->GetisAttackLocusDisplay())
	{
		if (CharacterSystem::GetInstance()->GetPlayerAddress()->GetisDamage()) return;
		spr->Render(FrameWork::GetInstance().GetContext().Get(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), FrameWork::GetInstance().GetElapsedTime());
	}
}

void SwordLocus::UnInit()
{

}

void SwordLocus::SetEffectPoint(DirectX::XMFLOAT3 oldSword, DirectX::XMFLOAT3 oldHand, DirectX::XMFLOAT3 originPos)
{
	if (num >= 9 * 11 + 1) num = 0;

	if (0 < num)
	{
		DirectX::XMFLOAT3 newSword = oldSword;
		DirectX::XMFLOAT3 newHand = oldHand;

		for (int i = 1; i < 9; i++)
		{
			DirectX::XMFLOAT3 swordStorageVec, handStorageVec;
			float storageValue = static_cast<float>(i) / 10.0f;
			swordStorageVec = SphereLinear(originPos, ci[num - 1].swordPoint->GetPos(), newSword, storageValue);
			handStorageVec = SphereLinear(originPos, ci[num - 1].handPoint->GetPos(), newHand, storageValue);

			DirectX::XMFLOAT3 swordDir, handDir;
			swordDir.x = newSword.x - originPos.x;
			swordDir.y = newSword.y - originPos.y;
			swordDir.z = newSword.z - originPos.z;

			handDir.x = newHand.x - originPos.x;
			handDir.y = newHand.y - originPos.y;
			handDir.z = newHand.z - originPos.z;

			float swordLen = sqrtf((swordDir.x * swordDir.x) + (swordDir.y * swordDir.y) + (swordDir.z * swordDir.z));
			float handLen = sqrtf((handDir.x * handDir.x) + (handDir.y * handDir.y) + (handDir.z * handDir.z));

			DirectX::XMFLOAT3 swordStoragePos;
			if (swordStorageVec.x == 0.0f && swordStorageVec.y == 0.0f && swordStorageVec.z == 0.0f)
			{
				DirectX::XMFLOAT3 point = ci[num - 1].swordPoint->GetPos();
				swordStoragePos.x = point.x;
				swordStoragePos.y = point.y;
				swordStoragePos.z = point.z;
			}
			else
			{
				swordStoragePos.x = originPos.x + swordStorageVec.x * swordLen;
				swordStoragePos.y = originPos.y + swordStorageVec.y * swordLen;
				swordStoragePos.z = originPos.z + swordStorageVec.z * swordLen;
			}

			DirectX::XMFLOAT3 handStoragePos;
			if (handStorageVec.x == 0.0f && handStorageVec.y == 0.0f && handStorageVec.z == 0.0f)
			{
				DirectX::XMFLOAT3 point = ci[num - 1].handPoint->GetPos();
				handStoragePos.x = point.x;
				handStoragePos.y = point.y;
				handStoragePos.z = point.z;
			}
			else
			{
				handStoragePos.x = originPos.x + handStorageVec.x * handLen;
				handStoragePos.y = originPos.y + handStorageVec.y * handLen;
				handStoragePos.z = originPos.z + handStorageVec.z * handLen;
			}

			ci[num].handPoint->SetPos(handStoragePos);
			ci[num].swordPoint->SetPos(swordStoragePos);

			num++;
		}
	}

#if 1
	ci[num].handPoint->SetPos(oldHand);
	ci[num].swordPoint->SetPos(oldSword);
#endif


	int t = num;
	int max = 9 * 11 + 1;
	for (int i = 0; i < max; i++)
	{
		spr->meshInfo[i].dPos = ci[t].handPoint->GetPos();
		spr->meshInfo[i].uPos = ci[t].swordPoint->GetPos();

		t++;
		if (t >= 9 * 11 + 1) t = 0;

	}
	num++;

	spr->CreateMesh(FrameWork::GetInstance().GetDevice().Get(), { 1024, 0, 1024, 1024 });
}