#include "SceneLabo.h"
#include "FrameWork.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SkinnedMesh.h"


void SceneLabo::Init()  
{
	//player.Init();
	pPlayer = std::make_unique<Model>("Data/Assets/Model/enemy1.fbx", false);
	playerData.Init();
	playerData.SetPosZ(35.0f);
	radius = 5.0f;

	pItem = std::make_unique<Model>("Data/Assets/Model/Life.fbx", false);
	itemData.Init();
	itemData.SetScale({ 10.0f,10.0f,10.0f });

	pPlayerCube = std::make_unique<CollisionPrimitive>(CollisionPrimitive::CUBE, false, DirectX::XMFLOAT3( 10.0f, 5.0f, 10.0f ));
	pGroundCube = std::make_unique<CollisionPrimitive>(CollisionPrimitive::CUBE, false, DirectX::XMFLOAT3( 100.0f, 5.0f, 200.0f ));

	pPlayerCylinder = std::make_unique<CollisionPrimitive>(CollisionPrimitive::CYLINDER, false, DirectX::XMFLOAT3(10.0f, 5.0f, 0.0f));
	pGroundCylinder = std::make_unique<CollisionPrimitive>(CollisionPrimitive::CYLINDER, false, DirectX::XMFLOAT3(20.0f, 5.0f, 0.0f));
}
void SceneLabo::Update()
{
	if (GetKeyState('N') < 0)
	{
		SceneManager::GetInstance()->SetScene(new SceneTitle());
	}

	ImGui::Begin("Scene");

	ImGui::End();

	static DirectX::XMFLOAT3 _pos = { 0.0f, 1.0f, 0.0f };
	DirectX::XMFLOAT3 addModelPos = _pos;
	DirectX::XMFLOAT3 modelPos = playerData.GetPos();
	DirectX::XMFLOAT3 oldModelPos = playerData.GetPos();

	ImGui::Begin("Test Model");
	ImGui::DragFloat3("pos", &_pos.x);
	ImGui::DragFloat3("model pos", &modelPos.x);
	ImGui::DragFloat("draw radius", &radius);

	if (ImGui::Button("Anim Start"))
	{
		pPlayer->StartAnimation(0, true);
	}
	if (ImGui::Button("Anim ReStart"))
	{
		pPlayer->ReStartAnimation();
	}
	if (ImGui::Button("Anim Stop"))
	{
		pPlayer->PauseAnimation();
	}
	ImGui::End();


	playerData.SetPos(modelPos);


	DirectX::XMFLOAT2 _collisionPos = { playerData.GetPos().x, playerData.GetPos().z };
	Collision::RectVsRectAndExtrusion(_collisionPos, DirectX::XMFLOAT2(pPlayerCube->GetCollisionScale().x, pPlayerCube->GetCollisionScale().z),
		DirectX::XMFLOAT2(pGroundCube->GetPos().x, pGroundCube->GetPos().z), DirectX::XMFLOAT2(pGroundCube->GetCollisionScale().x, pGroundCube->GetCollisionScale().z));

	playerData.SetPosX(_collisionPos.x);
	playerData.SetPosZ(_collisionPos.y);
	pPlayerCube->SetPosX(_collisionPos.x);
	pPlayerCube->SetPosZ(_collisionPos.y);
	pPlayerCylinder->SetPosX(_collisionPos.x);
	pPlayerCylinder->SetPosZ(_collisionPos.y);

#if 1
	_collisionPos = { playerData.GetPos().x, playerData.GetPos().z };
	Collision::CircleVsCircleAndExtrusion(_collisionPos, pPlayerCylinder->GetScale().x,
		DirectX::XMFLOAT2(pGroundCylinder->GetPos().x, pGroundCylinder->GetPos().z), pGroundCylinder->GetScale().x);

	playerData.SetPosX(_collisionPos.x);
	playerData.SetPosZ(_collisionPos.y);
	pPlayerCube->SetPosX(_collisionPos.x);
	pPlayerCube->SetPosZ(_collisionPos.y);
	pPlayerCylinder->SetPosX(_collisionPos.x);
	pPlayerCylinder->SetPosZ(_collisionPos.y);
#elif 0
	DirectX::XMFLOAT3 _collisionPosFloat3 = { playerData.GetPos().x, 0.0f, playerData.GetPos().z };
	Collision::CapsuleVsCircleAndExtrusion(_collisionPosFloat3, DirectX::XMFLOAT3(oldModelPos.x, 0.0f, oldModelPos.z), pPlayerCylinder->GetScale().x,
		DirectX::XMFLOAT3(pGroundCylinder->GetPos().x, 0.0f, pGroundCylinder->GetPos().z), pGroundCylinder->GetScale().x);

	playerData.SetPosX(_collisionPosFloat3.x);
	playerData.SetPosZ(_collisionPosFloat3.z);
	pPlayerCube->SetPosX(_collisionPosFloat3.x);
	pPlayerCube->SetPosZ(_collisionPosFloat3.z);
	pPlayerCylinder->SetPosX(_collisionPosFloat3.x);
	pPlayerCylinder->SetPosZ(_collisionPosFloat3.z);
#else
	DirectX::XMFLOAT3 _collisionPosFloat3 = { playerData.GetPos().x, 0.0f, playerData.GetPos().z };
	Collision::SphereVsCapsule(_collisionPosFloat3, DirectX::XMFLOAT3(oldModelPos.x, 0.0f, oldModelPos.z), pPlayerCylinder->GetScale().x,
		DirectX::XMFLOAT3(pGroundCylinder->GetPos().x, 0.0f, pGroundCylinder->GetPos().z), pGroundCylinder->GetScale().x);

	playerData.SetPosX(_collisionPosFloat3.x);
	playerData.SetPosZ(_collisionPosFloat3.z);
	pPlayerCube->SetPosX(_collisionPosFloat3.x);
	pPlayerCube->SetPosZ(_collisionPosFloat3.z);
	pPlayerCylinder->SetPosX(_collisionPosFloat3.x);
	pPlayerCylinder->SetPosZ(_collisionPosFloat3.z);
#endif


	pPlayer->GetBoneTransform(std::string("pCube1"), addModelPos);

	DirectX::XMMATRIX M = DirectX::XMMatrixTranslation(addModelPos.x, addModelPos.y, addModelPos.z);
	DirectX::XMFLOAT4X4 _M;
	DirectX::XMStoreFloat4x4(&_M, M * playerData.GetWorldMatrix());

	itemData.SetPos({ _M._41, _M._42, _M._43 });


	//player.Update();
}
void SceneLabo::Render()
{
	//player.Draw();
	pPlayer->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	pPlayer->Render(playerData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), playerData.GetColor(), FrameWork::GetInstance().GetElapsedTime(), radius);

	pItem->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	pItem->Render(itemData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), itemData.GetColor(), FrameWork::GetInstance().GetElapsedTime());

	pPlayerCube->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

	pGroundCube->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

	pPlayerCylinder->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

	pGroundCylinder->Render(camera.GetViewMatrix(), camera.GetProjectionMatrix(),
		DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
}
void SceneLabo::ImGui()
{
	/*ImGui::Begin("Scene");

	ImGui::End();

	static DirectX::XMFLOAT3 _pos = { 0.0f, 1.0f, 0.0f };
	DirectX::XMFLOAT3 addModelPos = _pos;
	DirectX::XMFLOAT3 modelPos = backData.GetPos();

	ImGui::Begin("Test Model");
	ImGui::DragFloat3("pos", &_pos.x);
	ImGui::DragFloat3("model pos", &modelPos.x);
	ImGui::DragFloat("draw radius", &radius);

	if (ImGui::Button("Anim Start"))
	{
		pBack->StartAnimation(0, true);
	}
	if (ImGui::Button("Anim ReStart"))
	{
		pBack->ReStartAnimation();
	}
	if (ImGui::Button("Anim Stop"))
	{
		pBack->PauseAnimation();
	}
	ImGui::End();

	pBack->GetBoneTransform(std::string("pCube1"), addModelPos);
	backData.SetPos(modelPos);

	DirectX::XMMATRIX M = DirectX::XMMatrixTranslation(addModelPos.x, addModelPos.y, addModelPos.z);
	DirectX::XMFLOAT4X4 _M;
	DirectX::XMStoreFloat4x4(&_M, M * backData.GetWorldMatrix());

	itemData.SetPos({ _M._41, _M._42, _M._43 });*/

	//player.ImGui();
}



void SceneLabo::UnInit() {}