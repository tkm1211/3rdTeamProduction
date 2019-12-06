#include "Player.h"
#include "Camera.h"
#include "FrameWork.h"
#include "InputDevice.h"
#include "Shader.h"
#include "CameraSystem.h"

#include <fstream>
#include <string>


void Player::Init()
{
	pT         = std::make_unique<Model>("Data/Assets/Model/val/Player_Tpose.fbx"   , false);
	pWait      = std::make_unique<Model>("Data/Assets/Model/val/Player_taiki.fbx"   , false);
	pRun       = std::make_unique<Model>("Data/Assets/Model/val/Player_idou.fbx"    , false);
	pAttack[0] = std::make_unique<Model>("Data/Assets/Model/val/Player_attack01.fbx", false);
	pAttack[1] = std::make_unique<Model>("Data/Assets/Model/val/Player_attack02.fbx", false);
	pAttack[2] = std::make_unique<Model>("Data/Assets/Model/val/Player_attack03.fbx", false);

	modelData.Init();
	SwitchMotion(ModelState::WAIT);

	atkCollision = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(50, 50, 50));
	atkCollision->SetColor({ 0, 1, 0, 1 });
	bodyCollision = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(30, 160, 30));
	bodyCollision->SetColor({ 0, 1, 0, 1 });
	SSS = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	SSS->SetColor({ 0, 1, 1, 1 });

	leftStickVec                    = {0, 0};
						            
	moveSpeed                       = {0, 0, 0};
						            
	attackCnt                       = 0;
						            
	attackInfo[0].power             = 0.0f;
	attackInfo[1].power             = 0.0f;
	attackInfo[2].power             = 0.0f;
	attackInfo[0].inputAttackButton = 5;
	attackInfo[1].inputAttackButton = 5;
	attackInfo[2].inputAttackButton = 5;

	attackState         = AttackState::ATK1ST;

	isMove              = false;
	isAttack            = false;
	enableNextAttack    = false;


	hosei = 0;
	//json読み込み
	std::ifstream ifs;
	ifs.open("./Data/Document/Player.json", std::ios::binary);
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(*this);
	}
	ifs.close();

}

void Player::UnInit()
{
	pT         = nullptr;
	pWait      = nullptr;
	pRun       = nullptr;
	pAttack[0] = nullptr;
	pAttack[1] = nullptr;
	pAttack[2] = nullptr;

	modelData.UnInit();
}

void Player::Update()
{

	Move();

	Attack();

	modelData.SetPosX( modelData.GetPos().x + moveSpeed.x );
	modelData.SetPosZ( modelData.GetPos().z + moveSpeed.z );

	//Collsion
	switch (motionState)
	{
	case ModelState::WAIT:
		atkCollision->SetPos(pWait->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 9));
		bodyCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 1688));
		break;
	case ModelState::RUN:
		atkCollision->SetPos(pRun->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 9));
		bodyCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 1688));
		break;
	case ModelState::ATTACK1:
		atkCollision->SetPos(pAttack[0]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 9));
		bodyCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 1688));
		break;
	case ModelState::ATTACK2:
		atkCollision->SetPos(pAttack[1]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 9));
		bodyCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 1688));
		break;
	case ModelState::ATTACK3:
		atkCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 9));
		bodyCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), addModelPos, modelData.GetWorldMatrix(), 1688));
		break;
	}


	DirectX::XMFLOAT3 out = {};
	SphereLinear({ 50, 70, 50 }, atkCollision->GetPos(), hosei);
	SSS->SetPos(out);

#if _DEBUG
	ImGui();
#endif
}


void Player::Draw()
{
	switch ( motionState )
	{
	case ModelState::WAIT:
		pWait->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false );

		pWait->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::RUN:
		pRun->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false) ;

		pRun->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK1:
		pAttack[0]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false );

		pAttack[0]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK2:
		pAttack[1]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false );

		pAttack[1]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK3:
		pAttack[2]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false );

		pAttack[2]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	}

	atkCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	bodyCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	SSS->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());

}


DirectX::XMFLOAT2 Player::GetLeftStickVector()
{

	if ( abs( xInput[0].sLX ) < 250 && abs( xInput[0].sLY ) < 250 ) return leftStickVec;

	leftStickVec.x = static_cast<float> ( xInput[0].sLX ) /  1000;
	leftStickVec.y = static_cast<float> ( xInput[0].sLY ) / -1000;

	float len = sqrtf( leftStickVec.x * leftStickVec.x + leftStickVec.y * leftStickVec.y );

	if ( len <= 0 ) return DirectX::XMFLOAT2( 0, 0 );

	float mag = 1 / len;

	leftStickVec.x *= mag;
	leftStickVec.y *= mag;

	return leftStickVec;

}

// 右スティックの傾いてる角度を取得	
float Player::GetLeftStickAngle()
{
	float angle = 0.0f;

	angle = atan2f( GetLeftStickVector().x, GetLeftStickVector().y );

	return angle;
}

void Player::SwitchMotion( ModelState state )
{
	static ModelState ms = ModelState::T;
	if ( state == ms ) return;
	ms = state;
	switch ( ms )
	{
	case Player::ModelState::T:
		break;																					
	case Player::ModelState::WAIT:

		motionState = ModelState::WAIT;
		pWait->StartAnimation( 0, true );

		break;
	case Player::ModelState::RUN:

		motionState = ModelState::RUN;
		pRun->StartAnimation( 0, true );

		break;
	case Player::ModelState::ATTACK1:

		motionState = ModelState::ATTACK1;
		pAttack[0]->StartAnimation( 0, false );

		break;
	case Player::ModelState::ATTACK2:

		motionState = ModelState::ATTACK2;
		pAttack[1]->StartAnimation( 0, false );

		break;
	case Player::ModelState::ATTACK3:

		motionState = ModelState::ATTACK3;
		pAttack[2]->StartAnimation( 0, false );

		break;
	}
}

void Player::Move()
{
	if ( isAttack ) return;

	if ( abs( xInput[0].sLX ) > 250 || abs( xInput[0].sLY ) > 250)
	{
		if ( xInput->bL3s )
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) /** ( abs( xInput[0].sX ) / 1000.0f */ * MAX_SPEED * 2;
			moveSpeed.z = cosf(modelData.GetAngle().y) /** ( abs( xInput[0].sY ) / 1000.0f */ * MAX_SPEED * 2;
			isMove = true;
		}
		else
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) /** ( abs( xInput[0].sX ) / 1000.0f */ * MAX_SPEED;
			moveSpeed.z = cosf(modelData.GetAngle().y) /** ( abs( xInput[0].sY ) / 1000.0f */ * MAX_SPEED;
			isMove = true;
		}
	}
	else
	{
		// 待機モーションに切り替え
		SwitchMotion(ModelState::WAIT);

		moveSpeed = { 0, 0, 0 };

		isMove = false;
	}

	attackCnt = 0;
}

void Player::Attack()
{
	if (xInput[0].bXt && !isAttack)
	{
		isAttack = true;
	}

	if (isAttack)
	{
		switch (attackState)
		{
		case AttackState::ATK1ST:
			SwitchMotion(ModelState::ATTACK1);
			attackCnt = 0;
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].inputAttackButton && pAttack[attackCnt]->GetAnimationFrame() <= 20)
			{
				if (xInput[0].bXt)
				{
					enableNextAttack = true;
				}
			}
			if (pAttack[0]->GetAnimationFrame() == 20)
			{
				if (enableNextAttack)
				{
					attackState = AttackState::ATK2ND;
					enableNextAttack = false;
				}
				else
				{
					isAttack = false;
					enableNextAttack = false;
					attackState = AttackState::ATK1ST;
				}
			}
			break;
		case AttackState::ATK2ND:
				SwitchMotion(ModelState::ATTACK2);
				attackCnt = 1;
				if (pAttack[1]->GetAnimationFrame() > attackInfo[attackCnt].inputAttackButton && pAttack[attackCnt]->GetAnimationFrame() <= 20)
				{
					if (xInput[0].bXt)
					{
						enableNextAttack = true;
					}
				}
				if (pAttack[1]->GetAnimationFrame() == 20)
				{
					if (enableNextAttack)
					{
						attackState = AttackState::ATK3RD;
						enableNextAttack = false;
					}
					else
					{
						isAttack = false;
						enableNextAttack = false;
						attackState = AttackState::ATK1ST;
					}
				}
			break;
		case AttackState::ATK3RD:
			SwitchMotion(ModelState::ATTACK3);
			attackCnt = 2;
			if (pAttack[attackCnt]->GetAnimationFrame() == 20)
			{
				attackCnt = 0;
				isAttack = false;
				enableNextAttack = false;
				attackState = AttackState::ATK1ST;
			}
			break;
		}
	}
}

void Player::ImGui()
{
	ImGui::Begin(u8"Player");

	ImGui::Text("angleY : %f", modelData.GetAngle().y);
	ImGui::Text("posX   : %f", modelData.GetPos().x);
	ImGui::Text("posZ   : %f", modelData.GetPos().z);
	ImGui::Text("AnimationFrame   : %d", pAttack[1]->GetAnimationFrame());

	ImGui::DragInt("MAX_SPEED##Player", &MAX_SPEED);

	ImGui::DragFloat("HOSEI##Player", &hosei);
	ImGui::DragFloat("ATTACKPOWER1##Player", &attackInfo[0].power);
	ImGui::DragFloat("ATTACKPOWER2##Player", &attackInfo[1].power);
	ImGui::DragFloat("ATTACKPOWER3##Player", &attackInfo[2].power);

	ImGui::DragFloat3("addModelPos##Player", &addModelPos.x);

	ImGui::DragInt("VERTEXNUM##Player", &vectexPosNo);

	ImGui::RadioButton("1st##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_1ST);
	ImGui::SameLine();
	ImGui::RadioButton("2nd##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_2ND);
	ImGui::SameLine();
	ImGui::RadioButton("3rd##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_3RD);

	if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_1ST)
	{
		ImGui::Text("posX   : %f", modelData.GetPos().z);
	}
	else if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_2ND)
	{
		ImGui::Text("posY   : %f", modelData.GetPos().z);
	}
	else if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_3RD)
	{
		ImGui::Text("posZ   : %f", modelData.GetPos().z);
	}

	//cereal でjson とbinary に保存
	static std::string data_name;
	if (ImGui::Button("SAVE"))
	{
		data_name = "./Data/Document/Player.json";
		std::ofstream ofs;
		ofs.open(data_name.c_str(), std::ios::binary);
		{
			cereal::JSONOutputArchive o_archive(ofs);
			o_archive(*this);
		}
		ofs.close();
	}

	ImGui::End();
}
