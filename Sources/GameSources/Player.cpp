#include "Player.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Shader.h"
#include "InputDevice.h"

void Player::Init()
{
	pT = std::make_unique<Model>("Data/Assets/Model/val/Player_Tpose.fbx", false);
	pWait = std::make_unique<Model>("Data/Assets/Model/val/Player_taiki.fbx", false);
	pRun = std::make_unique<Model>("Data/Assets/Model/val/Player_idou.fbx", false);
	pAttack[0] = std::make_unique<Model>("Data/Assets/Model/val/Player_attack01.fbx", false);
	pAttack[1] = std::make_unique<Model>("Data/Assets/Model/val/Player_attack02.fbx", false);
	pAttack[2] = std::make_unique<Model>("Data/Assets/Model/val/Player_attack03.fbx", false);

	modelData.Init();
	SwitchMotion(ModelState::WAIT);
	RightStickVec = {0, 0};
	MoveSpeed = {0, 0, 0};
}

void Player::UnInit()
{
	pT = nullptr;
	pWait = nullptr;
	pRun = nullptr;
	pAttack[0] = nullptr;
	pAttack[1] = nullptr;
	pAttack[2] = nullptr;

	modelData.UnInit();
}

void Player::Update()
{
	if ( abs( xInput[0].sX ) > 250 || abs( xInput[0].sY ) > 250 )
	{
		modelData.SetAngle(DirectX::XMFLOAT3(0, camera.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
		SwitchMotion(ModelState::RUN);
		MoveSpeed.x = sinf( modelData.GetAngle().y ) * ( abs( xInput[0].sX ) / 1000.0f * MAX_SPEED );
		MoveSpeed.z = cosf( modelData.GetAngle().y ) * ( abs( xInput[0].sY ) / 1000.0f * MAX_SPEED );
	}
	else
	{
		//modelData.SetAngle(DirectX::XMFLOAT3(0, camera.GetRotateY() + DirectX::XM_PI, 0));
		SwitchMotion(ModelState::WAIT);

		MoveSpeed = { 0, 0, 0 };
	}


	modelData.SetPosX( modelData.GetPos().x + MoveSpeed.x );
	modelData.SetPosZ( modelData.GetPos().z + MoveSpeed.z );

	ImGui::Begin( u8"Plyer" );

	ImGui::Text( "angleY : %f", modelData.GetAngle().y );
	ImGui::Text( "posX   : %f", modelData.GetPos().x   );
	ImGui::Text( "posZ   : %f", modelData.GetPos().z   );

	ImGui::End();
}

void Player::Draw()
{
	switch ( motionState )
	{
	case Player::ModelState::WAIT:
		pWait->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false );

		pWait->Render( modelData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case Player::ModelState::RUN:
		pRun->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::DEFAULT ), false) ;

		pRun->Render( modelData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case Player::ModelState::ATTACK1:
		break;
	case Player::ModelState::ATTACK2:
		break;
	case Player::ModelState::ATTACK3:
		break;
	}
}


DirectX::XMFLOAT2 Player::GetLeftStickVector()
{

	if ( abs( xInput[0].sX ) < 250 && abs( xInput[0].sY ) < 250 ) return RightStickVec;

	RightStickVec.x = static_cast<float> ( xInput[0].sX ) /  1000;
	RightStickVec.y = static_cast<float> ( xInput[0].sY ) / -1000;

	float len = sqrtf( RightStickVec.x * RightStickVec.x + RightStickVec.y * RightStickVec.y );

	if ( len <= 0 ) return DirectX::XMFLOAT2( 0, 0 );

	float mag = 1 / len;

	RightStickVec.x *= mag;
	RightStickVec.y *= mag;

	return RightStickVec;

}

//右スティックの傾いてる角度を取得	
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
