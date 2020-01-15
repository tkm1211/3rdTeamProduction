#include "BGEditor.h"


void BGEditor::Init()
{
	// Editor On
	on = true;

	// Load Models
	//bgModels[ModelType::WALL]  = std::make_unique<Model>("Data/Assets/Model/Boss/Boss02/MDL_Boss02_Wait.fbx", false, true);
	//bgModels[ModelType::STONE] = std::make_unique<Model>("Data/Assets/Model/Boss/Boss03/MDL_Boss03_Wait.fbx", false, true);
	//bgModels[ModelType::GRASS] = std::make_unique<Model>("Data/Assets/Model/Enemys/WarkerWait.fbx"          , false, true);
	//bgModels[ModelType::TREE]  = std::make_unique<Model>("Data/Assets/Model/danbo_fbx/danbo_atk.fbx", false, true);

	// Load Data
	LoadFile();
}
void BGEditor::Update()
{
	// [Ctrl + S] Save File
	if (GetKeyState(VK_CONTROL) < 0)
	{
		if (GetKeyState('S') < 0)
		{
			SaveFile();
		}
	}

	GUI();
	Click();
}
void BGEditor::GUI()
{
	ImGuiCond ImGuiSetCondOnce = 0;
	ImGui::SetNextWindowPos(ImVec2(0, 0)     , ImGuiSetCondOnce);
	ImGui::SetNextWindowSize(ImVec2(500, 200), ImGuiSetCondOnce);

	ImGui::Begin("GUI 1");

#if 0
	const char* names[] = { u8"石1", u8"石2", u8"草", u8"木" };
#else 
	const char* names[] = { u8"石1", u8"石2", u8"草" };
#endif
	//static int selected = -1;
	if (ImGui::Button(u8"モデル一覧"))
	{
		// "選択.."ボタンがクリックされた場合にここにきます。
		// 引数の"popupID"と同じID名のBeginPopupをポップアップとして表示します。
		ImGui::OpenPopup("popupID");
	}

	if (ImGui::BeginPopup("popupID"))
	{
		ImGui::Text(u8"選択項目");
		ImGui::Separator();
		for (int i = 0; i < IM_ARRAYSIZE(names); i++)
		{
			if (ImGui::Selectable(names[i]))
			{
				BGObject _bgObject;
				OBJ3D obj3d;

				obj3d.SetPos(CameraSystem::GetInstance()->bgEditorView.GetTarget());
				_bgObject.SetData(i, obj3d);

				bgObject.push_back(_bgObject);

				LoadModel(i);
			}
		}
		ImGui::EndPopup();
	}

	ImGui::End();
}
void BGEditor::Click()
{
	static bool target = false;
	static int type = -1;
	OBJ3DInstance obj;

	DirectX::XMFLOAT3 nearPos, farPos;

	POINT cursor;
	GetCursorPos(&cursor);
	DirectX::XMFLOAT2 cursorPos = DirectX::XMFLOAT2(static_cast<float>(cursor.x), static_cast<float>(cursor.y));

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = FrameWork::GetInstance().GetContext();
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	immediateContext->RSGetViewports(&numViewports, &viewport);

	CalcScreenToWorld(&nearPos, cursorPos.x, cursorPos.y, 0.0f, viewport.Width, viewport.Height, &CameraSystem::GetInstance()->bgEditorView.GetViewMatrix(), &CameraSystem::GetInstance()->bgEditorView.GetProjectionMatrix());
	CalcScreenToWorld(&farPos , cursorPos.x, cursorPos.y, 1.0f, viewport.Width, viewport.Height, &CameraSystem::GetInstance()->bgEditorView.GetViewMatrix(), &CameraSystem::GetInstance()->bgEditorView.GetProjectionMatrix());

	ImGui::Begin("mouse pos");
	ImGui::Text("posX : %f, posY : %f", cursorPos.x, cursorPos.y);
	ImGui::Text("nearX : %f, nearY : %f, nearZ : %f", nearPos.x, nearPos.y, nearPos.z);
	ImGui::Text("farX : %f, farY : %f, farZ : %f", farPos.x, farPos.y, farPos.z);
	ImGui::Text("cameraPosX : %f, cameraPosY : %f, cameraPosZ : %f", CameraSystem::GetInstance()->bgEditorView.GetPos().x, CameraSystem::GetInstance()->bgEditorView.GetPos().y, CameraSystem::GetInstance()->bgEditorView.GetPos().z);
	ImGui::End();

	DirectX::XMFLOAT3 outPosition;
	DirectX::XMFLOAT3 outNormal;
	float outDistance;

	if (!CameraSystem::GetInstance()->bgEditorView.GetUpdateNow() && GetKeyState(VK_LBUTTON) < 0)
	{
		float minLength = 0.0f;
		bool onFlg = false;

		for (size_t i = 0; i < bgModel.size(); i++)
		{
			if (-1 != bgModel[i]->RayPick(nearPos, farPos, bgObject[i].GetOBJ3D().GetWorldMatrix(), &outPosition, &outNormal, &outDistance))
			{
				float oldMinlength = minLength;
				DirectX::XMFLOAT3 pos = bgObject[i].GetOBJ3D().GetPos();
				DirectX::XMFLOAT3 distance;
				distance.x = pos.x - nearPos.x;
				distance.y = pos.y - nearPos.y;
				distance.z = pos.z - nearPos.z;
				minLength = sqrtf((distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z));

				if (type == i) continue;
				if (ImGuizmo::IsOver())continue;
				if (oldMinlength != 0.0f && oldMinlength < minLength) continue;

				type = i;
				target = true;
				onFlg = true;
			}
			else if (!onFlg && !ImGuizmo::IsOver())
			{
				type = -1;
				target = false;
			}
		}
	}

	if (ImGuizmo::IsOver())
	{
		CameraSystem::GetInstance()->bgEditorView.SetUpdateLook(true);
	}
	else
	{
		CameraSystem::GetInstance()->bgEditorView.SetUpdateLook(false);
	}

	if (target)
	{
		OBJ3D obj = bgObject[type].GetOBJ3D();

		Edit(&obj);

		bgObject[type].SetOBJ3D(obj);
	}
}
void BGEditor::Edit(OBJ3D* obj)
{
	DirectX::XMMATRIX worldMatrix = obj->GetWorldMatrix();
	DirectX::XMMATRIX viewMatrix = CameraSystem::GetInstance()->bgEditorView.GetViewMatrix();
	DirectX::XMMATRIX projectionMatrix = CameraSystem::GetInstance()->bgEditorView.GetProjectionMatrix();

	DirectX::XMFLOAT4X4 worldFloat4x4;
	DirectX::XMFLOAT4X4 viewFloat4x4;
	DirectX::XMFLOAT4X4 projectionFloat4x4;

	DirectX::XMStoreFloat4x4(&worldFloat4x4, worldMatrix);
	DirectX::XMStoreFloat4x4(&viewFloat4x4, viewMatrix);
	DirectX::XMStoreFloat4x4(&projectionFloat4x4, projectionMatrix);

	float worldM16[16];
	float viewM16[16];
	float projectionM16[16];

	int l = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			worldM16[l] = worldFloat4x4.m[i][j];
			viewM16[l] = viewFloat4x4.m[i][j];
			projectionM16[l] = projectionFloat4x4.m[i][j];
			l++;
		}
	}

	unsigned int color = 50;
	ImGuizmo::ViewManipulate(viewM16, 10.0f, { 0.0f, 0.0f }, { 300.0f, 300.0f }, color);

	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::WORLD);
	if (ImGui::IsKeyPressed(90))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	if (ImGui::IsKeyPressed(69))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	if (ImGui::IsKeyPressed(82)) // r Key
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	if (ImGui::RadioButton("Translate", mCurrentGizmoOperation == ImGuizmo::TRANSLATE))
		mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", mCurrentGizmoOperation == ImGuizmo::ROTATE))
		mCurrentGizmoOperation = ImGuizmo::ROTATE;
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", mCurrentGizmoOperation == ImGuizmo::SCALE))
		mCurrentGizmoOperation = ImGuizmo::SCALE;
	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(worldM16, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, worldM16);

	obj->SetPos({ matrixTranslation[0], matrixTranslation[1], matrixTranslation[2] });
	//obj->SetAngle({ matrixRotation[0] * 0.01745f, matrixRotation[1] * 0.01745f, matrixRotation[2] * 0.01745f });
	obj->SetScale({ matrixScale[0], matrixScale[1], matrixScale[2] });


	if (mCurrentGizmoOperation != ImGuizmo::SCALE)
	{
		if (ImGui::RadioButton("Local", mCurrentGizmoMode == ImGuizmo::LOCAL))
			mCurrentGizmoMode = ImGuizmo::LOCAL;
		ImGui::SameLine();
		if (ImGui::RadioButton("World", mCurrentGizmoMode == ImGuizmo::WORLD))
			mCurrentGizmoMode = ImGuizmo::WORLD;
	}
	static bool useSnap(false);
	if (ImGui::IsKeyPressed(83))
		useSnap = !useSnap;
	ImGui::Checkbox("", &useSnap);
	ImGui::SameLine();
	DirectX::XMFLOAT3 snap;
	switch (mCurrentGizmoOperation)
	{
	case ImGuizmo::TRANSLATE:
		snap = obj->GetPos();
		ImGui::InputFloat3("Snap", &snap.x);
		break;
	case ImGuizmo::ROTATE:
		snap = obj->GetAngle();
		ImGui::InputFloat("Angle Snap", &snap.x);
		break;
	case ImGuizmo::SCALE:
		snap = obj->GetScale();
		ImGui::InputFloat("Scale Snap", &snap.x);
		break;
	}

	bool cameraUpdate = CameraSystem::GetInstance()->bgEditorView.GetUpdateLook();
	ImGui::Checkbox("Camera Update Flg", &cameraUpdate);
	CameraSystem::GetInstance()->bgEditorView.SetUpdateLook(cameraUpdate);

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
	ImGuizmo::Manipulate(viewM16, projectionM16, mCurrentGizmoOperation, mCurrentGizmoMode, worldM16, NULL, useSnap ? &snap.x : NULL);
	// TODO : scaleを変更するとrotaが初期化される
	ImGuizmo::DecomposeMatrixToComponents(worldM16, matrixTranslation, matrixRotation, matrixScale);
	obj->SetPos({ matrixTranslation[0], matrixTranslation[1], matrixTranslation[2] });
	//obj->SetAngle({ matrixRotation[0] * 0.01745f, matrixRotation[1] * 0.01745f, matrixRotation[2] * 0.01745f });
	obj->SetScale({ matrixScale[0], matrixScale[1], matrixScale[2] });

	l = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			viewFloat4x4.m[i][j] = viewM16[l];
			worldFloat4x4.m[i][j] = worldM16[l];
			l++;
		}
	}

	if (CameraSystem::GetInstance()->bgEditorView.GetUpdateLook())
	{
		viewMatrix = DirectX::XMLoadFloat4x4(&viewFloat4x4);
		CameraSystem::GetInstance()->bgEditorView.SetViewMatrix(viewMatrix);
	}

	DirectX::XMMATRIX rotaMatrix = ExtractRotation(DirectX::XMLoadFloat4x4(&worldFloat4x4));
	DirectX::XMFLOAT4X4 rotaFloat4x4;
	DirectX::XMStoreFloat4x4(&rotaFloat4x4, rotaMatrix);

	DirectX::XMFLOAT3 rota;
#if 0 //ZXY回転
	rota.x = -asinf(DirectX::XMVectorGetY(rotaMatrix.r[2]));
	rota.y = atan2f(DirectX::XMVectorGetX(rotaMatrix.r[2]), DirectX::XMVectorGetZ(rotaMatrix.r[2]));
	rota.z = atan2f(DirectX::XMVectorGetY(rotaMatrix.r[0]), DirectX::XMVectorGetY(rotaMatrix.r[1]));
#elif 1 //ZYX回転
	rota.x = -atan2f(DirectX::XMVectorGetY(rotaMatrix.r[2]), DirectX::XMVectorGetZ(rotaMatrix.r[2]));
	rota.y = asinf(DirectX::XMVectorGetX(rotaMatrix.r[2]));
	rota.z = -atan2f(DirectX::XMVectorGetX(rotaMatrix.r[1]), DirectX::XMVectorGetX(rotaMatrix.r[0]));
#elif 0 //XYZ回転
	rota.x = atan2f(DirectX::XMVectorGetZ(rotaMatrix.r[1]), DirectX::XMVectorGetZ(rotaMatrix.r[2]));
	rota.y = -asinf(DirectX::XMVectorGetZ(rotaMatrix.r[0]));
	rota.z = atan2f(DirectX::XMVectorGetY(rotaMatrix.r[0]), DirectX::XMVectorGetX(rotaMatrix.r[0]));
#endif
	obj->SetAngle({ rota.x, rota.y, rota.z });

	if (ImGui::TreeNode(u8"初期化"))
	{
		if (ImGui::Button(u8"初期化"))
		{
			obj->SetPos({ 0.0f, 0.0f, 0.0f });
			obj->SetAngle({ 0.0f, 0.0f, 0.0f });
			obj->SetScale({ 1.0f, 1.0f, 1.0f });
		}
		ImGui::TreePop();
	}
}

void BGEditor::Draw()  
{
	SetRasterizerState(FrameWork::GetInstance().RS_CULL_BACK_FALSE);

	for (size_t i = 0; i < bgObject.size(); i++)
	{
		bgModel[i]->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
		bgModel[i]->Render(bgObject[i].GetOBJ3D().GetWorldMatrix(), CameraSystem::GetInstance()->bgEditorView.GetViewMatrix(), CameraSystem::GetInstance()->bgEditorView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), bgObject[i].GetOBJ3D().GetColor(), FrameWork::GetInstance().GetElapsedTime());
	}
}


void BGEditor::LoadFile()
{

}
void BGEditor::SaveFile()
{

}





void BGEditor::UnInit() {}