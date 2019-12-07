#include "Editer.h"
#include "Camera.h"
#include "Collision.h"
#include "CameraSystem.h"
#include "CharacterSystem.h"

Editer::Editer()
{
	nowEditer = false;
	nowCatch = false;
	catchIndex = -1;
	distance = 2500;
}

void Editer::Update()
{
	POINT cursor;
	::GetCursorPos(&cursor);

	oldCursor = newCursor;
	newCursor = DirectX::XMFLOAT2(static_cast<float>(cursor.x), static_cast<float>(cursor.y));


	
	DirectX::XMMATRIX view = CameraSystem::GetInstance()->enemyEditorView.GetViewMatrix();
	DirectX::XMMATRIX proj = CameraSystem::GetInstance()->enemyEditorView.GetProjectionMatrix();
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMVECTOR screen_start = DirectX::XMVectorSet(newCursor.x, newCursor.y, 0.0f, 0.0f);
	DirectX::XMVECTOR screen_end = DirectX::XMVectorSet(newCursor.x, newCursor.y, 1.0f, 0.0f);
	/*const D3D11_VIEWPORT& vp = camera;*/
	DirectX::XMVECTOR world_start = DirectX::XMVector3Unproject(screen_start,
		0, 0, 1920, 1080, 0.1f, 1000000.0f,
		proj, view, world);

	DirectX::XMVECTOR world_end = DirectX::XMVector3Unproject(screen_end,
		0, 0, 1920, 1080, 0.1f, 1000000.0f,
		proj, view, world);

	

	DirectX::XMStoreFloat3(&screenWorld, world_start);
	DirectX::XMStoreFloat3(&screenWorld2, world_end);

	
	if (nowCatch)
	{
		if (GetAsyncKeyState(VK_RBUTTON) & 1)
		{
			nowCatch = false;
			for (size_t i =0; i<CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetEnemyList().size();i++)
			{
				CharacterSystem::GetInstance()->GetEnemyManagerAddress()->nowCatch.at(i) = false;
			}
		}
	}
	else
	{
		float distance = NULL;
		if (::GetAsyncKeyState(VK_MENU) == 0)
		{
			for (size_t i =0; i<CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetEnemyList().size();i++)
			{
				if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					DirectX::XMFLOAT2 screenEnm;
					DirectX::XMStoreFloat2(&screenEnm,
						DirectX::XMVector3Project(
							DirectX::XMLoadFloat3(&CharacterSystem::GetInstance()->GetEnemyManagerAddress()->GetEnemyList().at(i).modelData->GetPos()),
							0, 0, 1920, 1080, 0.1f, 1000000.0f,
							proj, view, world));
					/*for (int j = 0; (unsigned)j < EnemyManager::GetInstance()->GetEnemyList().size(); j++)
					{*/
						if (collision.SphereVsSphere(DirectX::XMFLOAT3(newCursor.x,0, newCursor.y),
							DirectX::XMFLOAT3(screenEnm.x, 0, screenEnm.y),1,100))
						{

							int i = 0;

							//DirectX::XMFLOAT3 point;
							//DirectX::XMStoreFloat3(&point,
							//	DirectX::XMVectorSubtract(
							//		DirectX::XMLoadFloat3(&RayCastHitCoordinate(screenWorld, screenWorld2, vertexScale[0], vertexScale[1], vertexScale[2])),
							//		DirectX::XMLoadFloat3(&camera.GetEye())));

							//float pointLar = point.x*point.x + point.y*point.y + point.z*point.z;

							//if (distance > pointLar)
							//{
							//	for (auto&o : objMgr.obj)
							//	{
							//		o->nowCatch = false;
							//	}

							//	distance = pointLar;

							//	target = point;
							//	DirectX::XMFLOAT3 v = {};

							//	v.x = o->GetComponent<Transform>()->position.x - camera.GetEye().x;
							//	v.y = o->GetComponent<Transform>()->position.y - camera.GetEye().y;
							//	v.z = o->GetComponent<Transform>()->position.z - camera.GetEye().z;

							//	float vLar = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);

							//	/*camera.SetDistance(vLar);*/
							//	nowCatch = true;


							//	o->nowCatch = true;
							//	break;
							//}
							//else if (distance <= 0)
							//{
							//	distance = pointLar;

							//	target = point;
							//	DirectX::XMFLOAT3 v = {};

							//	v.x = o->GetComponent<Transform>()->position.x - camera.GetEye().x;
							//	v.y = o->GetComponent<Transform>()->position.y - camera.GetEye().y;
							//	v.z = o->GetComponent<Transform>()->position.z - camera.GetEye().z;

							//	float vLar = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);

							//	/*camera.SetDistance(vLar);*/
							//	nowCatch = true;


							//	o->nowCatch = true;
							//	break;
							//}
						}
						else
						{
						/*	o->nowCatch = false;*/
						}
					
				}
			}
		}

		
	}

	/*for (int i = 0; (unsigned)i < objMgr.obj.size(); i++)
	{
		if (!objMgr.obj.at(i)->nowCatch) { continue; }

		if (GetAsyncKeyState(VK_MENU) < 0&&GetAsyncKeyState('A') < 0)
		{
			objMgr.obj.erase(objMgr.obj.begin()+i);
			nowCatch = false;
		}
		if (GetAsyncKeyState(VK_MENU) < 0 && GetAsyncKeyState('S') & 1)
		{
			Object* a = new Object((char*)objMgr.obj.at(i)->GetResourceName(), (char*)objMgr.obj.at(i)->GetTag(), &objMgr);
			objMgr.obj.emplace_back(a);
		}
	}
	
	if (GetAsyncKeyState('Q') < 0)
	{
		distance += 500;
	}
	if (GetAsyncKeyState('W') < 0)
	{
		distance -= 500;

	}*/

	Imgui();
}


void Editer::Imgui()
{
	ImGui::Begin("edit");

	ImGui::InputFloat3("ScreenWorld", &screenWorld.x);
	ImGui::InputFloat3("ScreenWorld2", &screenWorld2.x);


	ImGui::End();
}