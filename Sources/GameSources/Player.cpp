#include "Player.h"
#include "Camera.h"
#include "FrameWork.h"
#include "InputDevice.h"
#include "Shader.h"
#include "CameraSystem.h"
#include "CameraControl.h"
#include "ParticleSystem.h"
#include "SoundLoader.h"
#include <fstream>
#include <string>

void Player::Init()
{
	pWait         = std::make_unique<Model>("Data/Assets/Model//Pl/PlayerStay.fbx"           , false);
	pRun          = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerRun.fbx"           , false);
	pDash        = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerFastRun.fbx"   , false);
	pAttack[0]  = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack1.fbx"     , false);
	pAttack[1]  = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack2.fbx"     , false);
	pAttack[2]  = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack3.fbx"     , false);
	pGuard[0]   = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerGurd_Do.fbx"   , false);
	pGuard[1]   = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerGurd_Stay.fbx" , false);
	pGuard[2]   = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerGurd.fbx"          , false);
	pDamage    = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerOuch.fbx"         , false);


	//pT         = std::make_unique<Model>("Data/Assets/Model/val/PlayerT.fbx"   , false);
	//pWait      = std::make_unique<Model>("Data/Assets/Model/val/PlayerWait.fbx"   , false);
	//pRun       = std::make_unique<Model>("Data/Assets/Model/val/PlayerRun.fbx"    , false);
	//pAttack[0] = std::make_unique<Model>("Data/Assets/Model/val/PlayerAttack1.fbx", false);
	//pAttack[1] = std::make_unique<Model>("Data/Assets/Model/val/PlayerAttack2.fbx", false);
	//pAttack[2] = std::make_unique<Model>("Data/Assets/Model/val/PlayerAttack3.fbx", false);
	//pDamage    = std::make_unique<Model>("Data/Assets/Model/val/PlayerHidame.fbx", false);

	modelData.Init();
	motionState = ModelState::WAIT;
	SwitchMotion(ModelState::WAIT);

	// geometry collision
	atkCollision         = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(45, 45, 45));
	atkCollision->SetColor({ 0, 1, 0, 1 });

	footRStepSound = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	footRStepSound->SetColor({ 0, 1, 0, 1 });

	footLStepSound = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	footLStepSound->SetColor({ 0, 1, 0, 1 });

	bodyCollision        = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(25, 80, 25));
	bodyCollision->SetColor({ 0, 1, 0, 1 });


	hp                                   = 10000;
	damage                          = 0;
	damageTimer                 = DAMAGE_TIMER;

	leftStickVec                    = {0, 0};

	moveSpeed                    = {0, 0, 0};

	attackMag                      = 0.0f;
	totalAttack                     = 0.0f;

	// 攻撃カウント( 0 ~ 2 )
	attackCnt                       = 0;
	// ダメージ量
	attackInfo[0].power             = 0.0f;
	attackInfo[1].power             = 0.0f;
	attackInfo[2].power             = 0.0f;
	// 入力開始時間
	attackInfo[0].inputStartTime    = 5;
	attackInfo[1].inputStartTime    = 5;
	attackInfo[2].inputStartTime    = 0;
	// 入力終了時間
	attackInfo[0].inputEndTime      = 20;
	attackInfo[1].inputEndTime      = 20;
	attackInfo[2].inputEndTime      = 0;
	// 次の攻撃に行く時間
	attackInfo[0].nextAttakTime     = 20;
	attackInfo[1].nextAttakTime     = 20;
	attackInfo[2].nextAttakTime     = 30;
	// 攻撃当たり判定開始
	attackInfo[0].atkCollisionStart = 10;
	attackInfo[1].atkCollisionStart = 10;
	attackInfo[2].atkCollisionStart = 10;
	// 攻撃当たり判定終了
	attackInfo[0].atkCollisionEnd   = 20;
	attackInfo[1].atkCollisionEnd   = 30;
	attackInfo[2].atkCollisionEnd   = 20;
	// 攻撃時の移動スピード
	attackInfo[0].speed             = 1;
	attackInfo[1].speed             = 3;
	attackInfo[2].speed             = 5;

	attackState         = AttackState::ATK1ST;
	guardState          = GuardState::GRD1ST;

	isMove                    = false;
	isAttack                   = false;
	isFinishAttack          = false;
	isGuard                   = false;
	isFlip                       = false;
	enableNextAttack     = false;
	onAtkCollision          = false;
	isDamageCalc          = false;
	isDamage                = false;
	enableCollision         = false;
	makeRightFoot         = false;
	makeLeftFoot           = false;

	// json読み込み
	std::ifstream ifs;
	ifs.open("./Data/Document/Player.json", std::ios::out);
	{
		cereal::JSONInputArchive i_archive(ifs);
		i_archive(*this);
	}
	ifs.close();

}

void Player::UnInit()
{
	pT              = nullptr;
	pWait         = nullptr;
	pRun          = nullptr;
	pAttack[0] = nullptr;
	pAttack[1] = nullptr;
	pAttack[2] = nullptr;
	pGuard[0]  = nullptr;
	pGuard[1]  = nullptr;
	pGuard[2]  = nullptr;
	pDamage   = nullptr;

	modelData.UnInit();
}

void Player::Update()
{

	Move();

	Attack();

	Guard();

	// Collsion
	CollisionInformation();


	CameraControl::PadControlUpdate(&CameraSystem::GetInstance()->mainView);

	ImGui();
	DamageCalc();
	DirectX::XMFLOAT3 z = modelData.GetPos();
	z.y += 50;
	if (xInput[0].bYs)
	{
		ParticleSystem::GetInstance()->SetUltimateThunder(z);
	}
	modelData.SetPosX(modelData.GetPos().x + moveSpeed.x);
	modelData.SetPosZ(modelData.GetPos().z + moveSpeed.z);

	if (GetKeyState('S') < 0)
	{
		ParticleSystem::GetInstance()->SetSpark({0, 300, 0});
	}

}

void Player::Draw()
{
	switch ( motionState )
	{
	case ModelState::WAIT:
		pWait->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pWait->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		                                  DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::RUN:
		pRun->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false) ;

		pRun->Render        ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                               DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::DASH:
		pDash->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false) ;

		pDash->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                               DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK1:
		pAttack[0]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pAttack[0]->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                                       DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK2:
		pAttack[1]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pAttack[1]->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                                       DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK3:
		pAttack[2]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE ), false );

		pAttack[2]->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                                       DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::GUARD1:
		pGuard[0]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pGuard[0]->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
		                                          DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::GUARD2:
		pGuard[1]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pGuard[1]->Render       ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                                      DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::GUARD3:
		pGuard[2]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE ), false );

		pGuard[2]->Render     ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                     DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::DAMAGE:
		pDamage->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::PHONE), false);

		pDamage->Render        ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                                      DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		break;
	}
#ifdef _DEBUG
	if (enableCollision)
	{
		if (onAtkCollision)  atkCollision->Render       (CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		                            bodyCollision->Render     (CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		if(makeLeftFoot)    footLStepSound->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		if(makeRightFoot)  footRStepSound->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	}
#endif // _DEBUG
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
		pWait->GetBoneTransformIndex(std::string("R_hand"), rightBone.meshIndex, rightBone.boneIndex);
		pWait->GetBoneTransformIndex(std::string("spine1") , bodyBone.meshIndex, bodyBone.boneIndex);
		pWait->GetBoneTransformIndex(std::string("R_Foot"), rightFootBone.meshIndex, rightFootBone.boneIndex);
		pWait->GetBoneTransformIndex(std::string("L_Foot"), leftFootBone.meshIndex, leftFootBone.boneIndex);

		break;
	case Player::ModelState::RUN:

		motionState = ModelState::RUN;
		pRun->StartAnimation( 0, true );
		pRun->GetBoneTransformIndex(std::string("R_hand"), rightBone.meshIndex, rightBone.boneIndex);
		pRun->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);
		pRun->GetBoneTransformIndex(std::string("R_Foot"), rightFootBone.meshIndex, rightFootBone.boneIndex);
		pRun->GetBoneTransformIndex(std::string("L_Foot"), leftFootBone.meshIndex, leftFootBone.boneIndex);

		break;
	case Player::ModelState::DASH:

		motionState = ModelState::DASH;
		pDash->StartAnimation( 0, true );
		pDash->GetBoneTransformIndex(std::string("R_hand"), rightBone.meshIndex, rightBone.boneIndex);
		pDash->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);
		pDash->GetBoneTransformIndex(std::string("R_Foot"), rightFootBone.meshIndex, rightFootBone.boneIndex);
		pDash->GetBoneTransformIndex(std::string("L_Foot"), leftFootBone.meshIndex, leftFootBone.boneIndex);

		break;
	case Player::ModelState::ATTACK1:

		motionState = ModelState::ATTACK1;
		pAttack[0]->StartAnimation( 0, false );
		pAttack[0]->GetBoneTransformIndex(std::string("R_hand"), rightBone.meshIndex, rightBone.boneIndex);
		pAttack[0]->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);
		pAttack[0]->GetBoneTransformIndex(std::string("R_Foot"), rightFootBone.meshIndex, rightFootBone.boneIndex);
		pAttack[0]->GetBoneTransformIndex(std::string("L_Foot"), leftFootBone.meshIndex, leftFootBone.boneIndex);

		ParticleSystem::GetInstance()->GetPlayerAttackEffect()->SetEffectInfo(atkCollision->GetPos(), 0);

		//PlaySoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
		//SetVolume(SoundLoader::GetInstance()->playerAttackSwingSe.get(), 1.0f);
		break;
	case Player::ModelState::ATTACK2:

		motionState = ModelState::ATTACK2;
		pAttack[1]->StartAnimation( 0, false );
		pAttack[1]->GetBoneTransformIndex(std::string("R_hand"), rightBone.meshIndex, rightBone.boneIndex);
		pAttack[1]->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);
		pAttack[1]->GetBoneTransformIndex(std::string("R_Foot"), rightFootBone.meshIndex, rightFootBone.boneIndex);
		pAttack[1]->GetBoneTransformIndex(std::string("L_Foot"), leftFootBone.meshIndex, leftFootBone.boneIndex);

		ParticleSystem::GetInstance()->GetPlayerAttackEffect()->SetEffectInfo(atkCollision->GetPos(), 1);

		//PlaySoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
		//SetVolume(SoundLoader::GetInstance()->playerAttackSwingSe.get(), 1.0f);

		break;
	case Player::ModelState::ATTACK3:

		motionState = ModelState::ATTACK3;
		pAttack[2]->StartAnimation( 0, false );
		pAttack[2]->GetBoneTransformIndex(std::string("R_hand"), rightBone.meshIndex, rightBone.boneIndex);
		pAttack[2]->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);
		pAttack[2]->GetBoneTransformIndex(std::string("R_Foot"), rightFootBone.meshIndex, rightFootBone.boneIndex);
		pAttack[2]->GetBoneTransformIndex(std::string("L_Foot"), leftFootBone.meshIndex, leftFootBone.boneIndex);

		ParticleSystem::GetInstance()->GetPlayerAttackEffect()->SetEffectInfo(atkCollision->GetPos(), 2);

		//PlaySoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
		//SetVolume(SoundLoader::GetInstance()->playerAttackSwingSe.get(), 1.0f);

		break;
	case Player::ModelState::GUARD1:

		motionState = ModelState::GUARD1;
		pGuard[0]->StartAnimation( 0, false );
		pGuard[0]->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);

		break;
	case Player::ModelState::GUARD2:

		motionState = ModelState::GUARD2;
		pGuard[1]->StartAnimation( 0, true );
		pGuard[1]->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);

		break;
	case Player::ModelState::GUARD3:

		motionState = ModelState::GUARD3;
		pGuard[2]->StartAnimation( 0, false );
		pGuard[2]->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);

		break;
	case Player::ModelState::DAMAGE:

		motionState = ModelState::DAMAGE;
		pDamage->StartAnimation( 0, false );
		pDamage->GetBoneTransformIndex(std::string("spine1"), bodyBone.meshIndex, bodyBone.boneIndex);

		break;
	}
}

void Player::Move()
{
	if ( isAttack || isDamage || isGuard) return;

	if ( abs( xInput[0].sLX ) > 250 || abs( xInput[0].sLY ) > 250)
	{
#if 1
		if ( xInput->bL3s )
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::DASH);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) * MAX_SPEED * 1.5f;
			moveSpeed.z = cosf(modelData.GetAngle().y) * MAX_SPEED * 1.5f;
			isMove = true;
		}
		else
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) * MAX_SPEED;
			moveSpeed.z = cosf(modelData.GetAngle().y) * MAX_SPEED;
			isMove = true;
		}
#else
		if ( xInput->bL3s )
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY(), 0));
			float x = xInput->sLX * 0.01f * MAX_SPEED;
			float y = xInput->sLY * 0.01f * MAX_SPEED;
			moveSpeed.x = sinf(modelData.GetAngle().y) * x * 2;
			moveSpeed.z = cosf(modelData.GetAngle().y) * y * 2;
			isMove = true;
		}
		else
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY(), 0));
			float x = xInput->sLX * 0.01f * MAX_SPEED;
			float y = xInput->sLY * 0.01f * MAX_SPEED;
			moveSpeed.x = sinf(modelData.GetAngle().y) * x;
			moveSpeed.z = cosf(modelData.GetAngle().y) * y;
			isMove = true;
		}
#endif // 0
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

	if (isDamage || isGuard) return;

	if (xInput[0].bXt && !isAttack)
	{
		isAttack = true;
		moveSpeed = { 0, 0, 0 };
		guardState = GuardState::GRD1ST;
	}

	if (isAttack)
	{
		switch (attackState)
		{
		case AttackState::ATK1ST:
			SwitchMotion(ModelState::ATTACK1);

			attackCnt = 0;

			// 入力
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].inputStartTime && pAttack[attackCnt]->GetAnimationFrame() <= attackInfo[attackCnt].inputEndTime)
			{

				if (xInput[0].bXt)
				{
					enableNextAttack = true;
				}
			}


			moveSpeed.x = sinf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;
			moveSpeed.z = cosf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;

			// Collision表示
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionStart && pAttack[attackCnt]->GetAnimationFrame() < attackInfo[attackCnt].atkCollisionEnd)
			{
				onAtkCollision = true;
			}
			else if(pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionEnd)
			{
				onAtkCollision = false;
				moveSpeed.x = 0.0f;
				moveSpeed.z = 0.0f;
			}

			// 2段目にいくかどうか
			if (pAttack[0]->GetAnimationFrame() >= attackInfo[attackCnt].nextAttakTime)
			{
				if (enableNextAttack)
				{
					attackState          = AttackState::ATK2ND;
					enableNextAttack = false;
					isFinishAttack       = false;
				}
				else
				{
					isFinishAttack = true;
				}
				onAtkCollision = false;

			}

			break;
		case AttackState::ATK2ND:
				SwitchMotion(ModelState::ATTACK2);
				attackCnt = 1;

				// 入力
				if (pAttack[1]->GetAnimationFrame() > attackInfo[attackCnt].inputStartTime && pAttack[attackCnt]->GetAnimationFrame() <= attackInfo[attackCnt].inputEndTime)
				{
					if (xInput[0].bXt)
					{
						enableNextAttack = true;
					}
				}

				moveSpeed.x = sinf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;
				moveSpeed.z = cosf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;

				// Collision表示
				if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionStart&& pAttack[attackCnt]->GetAnimationFrame() < attackInfo[attackCnt].atkCollisionEnd)
				{
					onAtkCollision = true;
				}
				else if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionEnd)
				{
					onAtkCollision = false;
					moveSpeed.x = 0.0f;
					moveSpeed.z = 0.0f;
				}

				// 3段目にいくかどうか
				if (pAttack[1]->GetAnimationFrame() >= attackInfo[attackCnt].nextAttakTime)
				{
					if (enableNextAttack)
					{
						attackState          = AttackState::ATK3RD;
						enableNextAttack = false;
						isFinishAttack       = false;
					}
					else
					{
						isFinishAttack = true;
					}
					onAtkCollision = false;

				}


			break;
		case AttackState::ATK3RD:
			SwitchMotion(ModelState::ATTACK3);
			attackCnt = 2;

			moveSpeed.x = sinf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;
			moveSpeed.z = cosf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;

			// Collision表示
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionStart&& pAttack[attackCnt]->GetAnimationFrame() < attackInfo[attackCnt].atkCollisionEnd)
			{
				onAtkCollision = true;
			}
			else if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionEnd)
			{
				onAtkCollision = false;
				moveSpeed.x = 0.0f;
				moveSpeed.z = 0.0f;
			}

			if (pAttack[attackCnt]->GetAnimationFrame() >= attackInfo[attackCnt].nextAttakTime)
			{
				isFinishAttack = true;
			}
			break;
		}
	}

	if (isFinishAttack)
	{
		switch (attackState)
		{
		case Player::AttackState::ATK1ST:
			// 入力
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].inputStartTime&& pAttack[attackCnt]->GetAnimationFrame() <= attackInfo[attackCnt].inputEndTime)
			{
				if (xInput[0].bXt)
				{
					attackState          = AttackState::ATK2ND;
					enableNextAttack = false;
					isFinishAttack       = false;
				}
			}
			if (pAttack[attackCnt]->GetAnimationFrame() > 30)
			{
				isAttack               = false;
				isFinishAttack       = false;
				enableNextAttack = false;
				attackState          = AttackState::ATK1ST;
			}
			break;
		case Player::AttackState::ATK2ND:
			// 入力
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].inputStartTime&& pAttack[attackCnt]->GetAnimationFrame() <= attackInfo[attackCnt].inputEndTime)
			{
				if (xInput[0].bXt)
				{
					attackState          = AttackState::ATK3RD;
					enableNextAttack = false;
					isFinishAttack       = false;
				}
			}
			if (pAttack[attackCnt]->GetAnimationFrame() > 25)
			{
				isAttack               = false;
				isFinishAttack       = false;
				enableNextAttack = false;
				attackState          = AttackState::ATK1ST;
			}
			break;
		case Player::AttackState::ATK3RD:
			// 入力
			if (pAttack[attackCnt]->GetAnimationFrame() > 24)
			{
				attackCnt            = 0;
				isFinishAttack      = false;
				isAttack               = false;
				enableNextAttack = false;
				attackState          = AttackState::ATK1ST;
			}
			break;
		}
	}

}

void Player::Guard()
{
	if (isDamage) return;
	if (isAttack && !isFinishAttack) return;

	if (xInput[0].bLBs && !isGuard)
	{
		attackCnt              = 0;
		isAttack                 = false;
		isFinishAttack        = false;
		enableNextAttack  = false;
		attackState           = AttackState::ATK1ST;
		moveSpeed           = { 0.0f, 0.0f, 0.0f };
		SwitchMotion(ModelState::GUARD1);
		isGuard       = true;
		isFlip           =  false;
		guardState = GuardState::GRD1ST;
	}
	else if (!xInput[0].bLBs && isGuard && !isFlip)
	{
		guardState = GuardState::GRD1ST;
		isGuard       = false;
		SwitchMotion(ModelState::WAIT);
	}

	if (isGuard)
	{
		switch (guardState)
		{
		case GuardState::GRD1ST:
			if (pGuard[0]->GetAnimationFrame() >= 8)
			{
				SwitchMotion(ModelState::GUARD2);
				guardState = GuardState::GRD2ND;
			}
			break;
		case GuardState::GRD2ND:
			if (xInput[0].bRBt)
			{
				SwitchMotion(ModelState::GUARD3);
				guardState = GuardState::GRD3RD;
				isFlip = true;
			}
			break;
		case GuardState::GRD3RD:
			if (pGuard[2]->GetAnimationFrame() >= 18)
			{
				SwitchMotion(ModelState::GUARD2);
				guardState = GuardState::GRD2ND;
				isFlip = false;
			}
			break;
		}
	}

}

void Player::SufferDamage(int _damage)
{
	// ダメージを受けている途中なら即Return
	if (isDamage) return;
	isDamageCalc = true;
	isDamage     = true;
	// 受けるダメージ量を代入
	damage       = _damage;
}

void Player::DamageCalc()
{
	if (isDamage)
	{
		damageTimer--;
		if (damageTimer <= 0)
		{
			isDamage = false;
			damageTimer = DAMAGE_TIMER;
		}
	}

	if (!isDamageCalc) return;
	// 被ダメモーションに切り替え
	SwitchMotion(ModelState::DAMAGE);
	attackCnt = 0;
	isAttack = false;
	enableNextAttack = false;
	attackState = AttackState::ATK1ST;
	moveSpeed = { 0.0f, 0.0f, 0.0f };
	guardState = GuardState::GRD1ST;
	hp -= damage;
	isDamageCalc = false;
}

void Player::CollisionInformation()
{
	DirectX::XMFLOAT4X4 boneTransform = {};
	DirectX::XMFLOAT4X4 boneTransformWithWorld = {};
	switch (motionState)
	{
	case ModelState::WAIT:
		// body
		boneTransform = pWait->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// attack
		boneTransform = pWait->GetBoneTransform(rightBone.meshIndex, rightBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		atkCollision->SetPos({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * 21.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -28.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -40.0f });

		ParticleSystem::GetInstance()->GetSwordLocus()->SetEffectPoint({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * -86.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -107.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -95.0f },
			{ boneTransformWithWorld._41, boneTransformWithWorld._42 , boneTransformWithWorld._43 });

		// R_Foot
		boneTransform = pWait->GetBoneTransform(rightFootBone.meshIndex, rightFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footRStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// L_Foot
		boneTransform = pWait->GetBoneTransform(leftFootBone.meshIndex, leftFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footLStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		break;

	case ModelState::RUN:
		// body
		boneTransform = pRun->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// bone information
		boneTransform = pRun->GetBoneTransform(rightBone.meshIndex, rightBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		atkCollision->SetPos({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * 21.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -28.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -40.0f });

		ParticleSystem::GetInstance()->GetSwordLocus()->SetEffectPoint({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * -86.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -107.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -95.0f },
			{ boneTransformWithWorld._41, boneTransformWithWorld._42 , boneTransformWithWorld._43 });

		// R_Foot
		boneTransform = pRun->GetBoneTransform(rightFootBone.meshIndex, rightFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footRStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// L_Foot
		boneTransform = pRun->GetBoneTransform(leftFootBone.meshIndex, leftFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footLStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		if (!makeRightFoot && footRStepSound->GetPos().y <= 0.08f)
		{
			makeRightFoot = true;
			////PlaySoundMem(SoundLoader::GetInstance()->playerStepSe.get());
			////SetVolume(SoundLoader::GetInstance()->playerStepSe.get(), 0.1f);
		}
		else if (footRStepSound->GetPos().y > 0.08f)
		{
			makeRightFoot = false;
		}

		if (!makeLeftFoot && footLStepSound->GetPos().y <= 0.08f)
		{
			makeLeftFoot = true;
			//PlaySoundMem(SoundLoader::GetInstance()->playerStepSe.get());
			//SetVolume(SoundLoader::GetInstance()->playerStepSe.get(), 0.1f);
		}
		else if (footLStepSound->GetPos().y > 0.08f)
		{
			makeLeftFoot = false;
		}

		break;

	case ModelState::ATTACK1:
		// body
		boneTransform = pAttack[0]->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// bone information
		boneTransform = pAttack[0]->GetBoneTransform(rightBone.meshIndex, rightBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		atkCollision->SetPos({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * 21.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -28.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -40.0f });

		ParticleSystem::GetInstance()->GetSwordLocus()->SetEffectPoint({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * -86.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -107.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -95.0f },
			{ boneTransformWithWorld._41, boneTransformWithWorld._42 , boneTransformWithWorld._43 });

		// R_Foot
		boneTransform = pAttack[0]->GetBoneTransform(rightFootBone.meshIndex, rightFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footRStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// L_Foot
		boneTransform = pAttack[0]->GetBoneTransform(leftFootBone.meshIndex, leftFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footLStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		break;

	case ModelState::ATTACK2:
		// body
		boneTransform = pAttack[1]->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// bone information
		boneTransform = pAttack[1]->GetBoneTransform(rightBone.meshIndex, rightBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		atkCollision->SetPos({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * 21.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -28.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -40.0f });

		ParticleSystem::GetInstance()->GetSwordLocus()->SetEffectPoint({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * -86.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -107.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -95.0f },
			{ boneTransformWithWorld._41, boneTransformWithWorld._42 , boneTransformWithWorld._43 });

		// R_Foot
		boneTransform = pAttack[1]->GetBoneTransform(rightFootBone.meshIndex, rightFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footRStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// L_Foot
		boneTransform = pAttack[1]->GetBoneTransform(leftFootBone.meshIndex, leftFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footLStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		break;
	case ModelState::ATTACK3:
		// body
		boneTransform = pAttack[2]->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// bone information
		boneTransform = pAttack[2]->GetBoneTransform(rightBone.meshIndex, rightBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		atkCollision->SetPos({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * 21.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -28.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -40.0f });

		ParticleSystem::GetInstance()->GetSwordLocus()->SetEffectPoint({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * -86.0f, boneTransformWithWorld._42 + boneTransformWithWorld._32 * -107.0f , boneTransformWithWorld._43 + boneTransformWithWorld._33 * -95.0f },
			{ boneTransformWithWorld._41, boneTransformWithWorld._42 , boneTransformWithWorld._43 });

		// R_Foot
		boneTransform = pAttack[2]->GetBoneTransform(rightFootBone.meshIndex, rightFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footRStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		// L_Foot
		boneTransform = pAttack[2]->GetBoneTransform(leftFootBone.meshIndex, leftFootBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		footLStepSound->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });

		break;
	case ModelState::GUARD1:
		// body
		boneTransform = pDamage->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });
		break;
	case ModelState::GUARD2:
		// body
		boneTransform = pDamage->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });
		break;
	case ModelState::GUARD3:
		// body
		boneTransform = pDamage->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });
		break;

	case ModelState::DAMAGE:
		// body
		boneTransform = pDamage->GetBoneTransform(bodyBone.meshIndex, bodyBone.boneIndex);
		// ボーン行列をワールド空間に変換
		DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
		bodyCollision->SetPos({ boneTransformWithWorld._41, boneTransformWithWorld._42, boneTransformWithWorld._43 });
		break;

	}
}

void Player::ImGui()
{
	ImGui::Begin(u8"Player");
	
	ImGui::Text (u8"合計攻撃                 : %f" , totalAttack);
	ImGui::Text (u8"アニメーションフレーム   : %d" , pGuard[2]->GetAnimationFrame());

	ImGui::Text (u8"パーティクル数           : %d" , ParticleSystem::GetInstance()->popParticleNum);
	ParticleSystem::GetInstance()->popParticleNum = 0;

	ImGui::Text("angleY : %f", modelData.GetAngle().y);
	ImGui::Text("posX   : %f", modelData.GetPos().x);
	ImGui::Text("posY   : %f", modelData.GetPos().y);
	ImGui::Text("posZ   : %f", modelData.GetPos().z);

	ImGui::Text("HP   : %d", hp);

	ImGui::DragInt  (u8"スピード##Player"                  , &MAX_SPEED);
	ImGui::DragInt  (u8"次のダメージを受けれるまで##Player", &DAMAGE_TIMER);
	ImGui::DragFloat(u8"攻撃倍率##Player"                  , &ATK_MAG);

	static int num[1];
	static DirectX::XMFLOAT3 _p = {};
	//ImGui::DragInt(u8"1##Player", &num[0]);
	//ImGui::DragInt(u8"2##Player", &num[1]);
	ImGui::DragFloat3(u8"3##Player", &_p.x);

	//attackAfterImageEmit->SetPos(pWait->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));

	//// bone information
	//DirectX::XMFLOAT4X4 boneTransform = pWait->GetBoneTransform(rightBone.meshIndex, rightBone.boneIndex);
	//// ボーン行列をワールド空間に変換
	//DirectX::XMFLOAT4X4 boneTransformWithWorld;
	//DirectX::XMStoreFloat4x4(&boneTransformWithWorld, DirectX::XMLoadFloat4x4(&boneTransform) * modelData.GetWorldMatrix());
	//atkCollision->SetPos({ boneTransformWithWorld._41 + boneTransformWithWorld._31 * _p.x, boneTransformWithWorld._42 + boneTransformWithWorld._32 * _p.y , boneTransformWithWorld._43 + boneTransformWithWorld._33 * _p.z });


	ImGui::RadioButton("1st##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_1ST);
	ImGui::SameLine();
	ImGui::RadioButton("2nd##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_2ND);
	ImGui::SameLine();
	ImGui::RadioButton("3rd##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_3RD);

	if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_1ST)
	{

		ImGui::DragFloat(u8"攻撃力##Player"                , &attackInfo[0].power);
		ImGui::DragInt  (u8"入力開始##Player"              , &attackInfo[0].inputStartTime);
		ImGui::DragInt  (u8"入力終了##Player"              , &attackInfo[0].inputEndTime);
		ImGui::DragInt  (u8"次の攻撃へいく時間##Player"    , &attackInfo[0].nextAttakTime);
		ImGui::DragInt  (u8"当たり判定表示開始##Player"    , &attackInfo[0].atkCollisionStart);
		ImGui::DragInt  (u8"当たり判定表示終了##Player"    , &attackInfo[0].atkCollisionEnd);
		ImGui::DragFloat(u8"攻撃の時のスピード##Player"    , &attackInfo[0].speed);

	}
	else if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_2ND)
	{

		ImGui::DragFloat(u8"攻撃力##Player"               , &attackInfo[1].power);
		ImGui::DragInt  (u8"入力開始##Player"             , &attackInfo[1].inputStartTime);
		ImGui::DragInt  (u8"入力終了##Player"             , &attackInfo[1].inputEndTime);
		ImGui::DragInt  (u8"次の攻撃へいく時間##Player"   , &attackInfo[1].nextAttakTime);
		ImGui::DragInt  (u8"当たり判定表示開始##Player"   , &attackInfo[1].atkCollisionStart);
		ImGui::DragInt  (u8"当たり判定表示終了##Player"   , &attackInfo[1].atkCollisionEnd);
		ImGui::DragFloat(u8"攻撃の時のスピード##Player"   , &attackInfo[1].speed);
	}
	else if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_3RD)
	{

		ImGui::DragFloat(u8"攻撃力##Player"               , &attackInfo[2].power);
		ImGui::DragInt  (u8"入力開始##Player"             , &attackInfo[2].inputStartTime);
		ImGui::DragInt  (u8"入力終了##Player"             , &attackInfo[2].inputEndTime);
		ImGui::DragInt  (u8"次の攻撃へいく時間##Player"   , &attackInfo[2].nextAttakTime);
		ImGui::DragInt  (u8"当たり判定表示開始##Player"   , &attackInfo[2].atkCollisionStart);
		ImGui::DragInt  (u8"当たり判定表示終了##Player"   , &attackInfo[2].atkCollisionEnd);
		ImGui::DragFloat(u8"攻撃の時のスピード##Player"   , &attackInfo[2].speed);
	}

	ImGui::Checkbox(u8"プレイヤーの当たり判定 on / off ##Player", &enableCollision);

	//cereal でjson とbinary に保存
	static std::string data_name;
	if (ImGui::Button("SAVE"))
	{
		data_name = "./Data/Document/Player.json";
		std::ofstream ofs;
		ofs.open(data_name.c_str(), std::ios::out);
		{
			cereal::JSONOutputArchive o_archive(ofs);
			o_archive(*this);
		}
		ofs.close();
	}


	ImGui::End();
	ImGui::ShowDemoWindow();
}
