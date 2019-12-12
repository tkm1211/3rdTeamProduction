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
	//pT         = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerT.fbx"   , false);
	//pWait      = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerWait.fbx"   , false);
	//pRun       = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerRun.fbx"    , false);
	//pAttack[0] = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack1.fbx", false);
	//pAttack[1] = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack2.fbx", false);
	//pAttack[2] = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack3.fbx", false);
	//pDamage    = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerHidame.fbx", false);
	pT         = std::make_unique<Model>("Data/Assets/Model/val/PlayerT.fbx"   , false);
	pWait      = std::make_unique<Model>("Data/Assets/Model/val/PlayerWait.fbx"   , false);
	pRun       = std::make_unique<Model>("Data/Assets/Model/val/PlayerRun.fbx"    , false);
	pAttack[0] = std::make_unique<Model>("Data/Assets/Model/val/PlayerAttack1.fbx", false);
	pAttack[1] = std::make_unique<Model>("Data/Assets/Model/val/PlayerAttack2.fbx", false);
	pAttack[2] = std::make_unique<Model>("Data/Assets/Model/val/PlayerAttack3.fbx", false);
	pDamage    = std::make_unique<Model>("Data/Assets/Model/val/PlayerHidame.fbx", false);

	modelData.Init();
	SwitchMotion(ModelState::WAIT);

	atkCollision         = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(50, 50, 50));
	atkCollision->SetColor({ 0, 1, 0, 1 });

	footRStepSound = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	footRStepSound->SetColor({ 0, 1, 0, 1 });

	footLStepSound = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	footLStepSound->SetColor({ 0, 1, 0, 1 });

	attackAfterImageEmit = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(50, 50, 50));
	attackAfterImageEmit->SetColor({ 0, 1, 0, 1 });

	bodyCollision        = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(30, 160, 30));
	bodyCollision->SetColor({ 0, 1, 0, 1 });

	hp                              = 10000;
	damage                          = 0;
	damageTimer                     = DAMAGE_TIMER;

	leftStickVec                    = {0, 0};

	moveSpeed                       = {0, 0, 0};
	oldAtkPos                       = {0, 0, 0};

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

	isMove              = false;
	isAttack            = false;
	enableNextAttack    = false;
	onAtkCollision      = false;
	isDamageCalc        = false;
	isDamage            = false;
	enableCollision     = false;
	makeRightFoot       = false;
	makeLeftFoot        = false;

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

	// Collsion
	switch (motionState)
	{
	case ModelState::WAIT:
		atkCollision->SetPos        (pWait->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		attackAfterImageEmit->SetPos(pWait->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		break;
	case ModelState::RUN:
		atkCollision->SetPos        (pRun->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		attackAfterImageEmit->SetPos(pRun->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));

		footRStepSound->SetPos(pRun->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 1738));
		footLStepSound->SetPos(pRun->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 1627));

		if (!makeRightFoot && footRStepSound->GetPos().y <= 0.4f)
		{
			makeRightFoot = true;
			//PlaySoundMem(SoundLoader::GetInstance()->playerStepSe.get());
		}
		else if (footRStepSound->GetPos().y > 0.4f)
		{
			makeRightFoot = false;
		}

		if (!makeLeftFoot && footLStepSound->GetPos().y <= 0.95f)
		{
			makeLeftFoot = true;
			//PlaySoundMem(SoundLoader::GetInstance()->playerStepSe.get());
		}
		else if (footLStepSound->GetPos().y > 0.95f)
		{
			makeLeftFoot = false;
		}

		break;
	case ModelState::ATTACK1:
		atkCollision->SetPos        (pAttack[0]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		attackAfterImageEmit->SetPos(pAttack[0]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		break;
	case ModelState::ATTACK2:
		atkCollision->SetPos        (pAttack[1]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		attackAfterImageEmit->SetPos(pAttack[1]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		break;
	case ModelState::ATTACK3:
		atkCollision->SetPos        (pAttack[2]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		attackAfterImageEmit->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		break;
	case ModelState::DAMAGE:
		atkCollision->SetPos        (pDamage->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		attackAfterImageEmit->SetPos(pDamage->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));
		break;

	}

	if (onAtkCollision)
	{
		ParticleSystem::GetInstance()->SetPlayerAttackAfterImageParticle(modelData.GetPos(), oldAtkPos, attackAfterImageEmit->GetPos());
	}
	oldAtkPos = attackAfterImageEmit->GetPos();

	bodyCollision->SetPos(pAttack[2]->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 1688));

	CameraControl::PadControlUpdate(&CameraSystem::GetInstance()->mainView);

	DamageCalc();

}


void Player::Draw()
{
	switch ( motionState )
	{
	case ModelState::WAIT:
		pWait->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pWait->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::RUN:
		pRun->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false) ;

		pRun->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK1:
		pAttack[0]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pAttack[0]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK2:
		pAttack[1]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pAttack[1]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK3:
		pAttack[2]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE ), false );

		pAttack[2]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::DAMAGE:
		pDamage->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::PHONE), false);

		pDamage->Render(modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		break;
	}

	if (enableCollision)
	{
		if (onAtkCollision) atkCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		bodyCollision->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	}
	//attackAfterImageEmit->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	if(makeLeftFoot) footLStepSound->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
	if(makeRightFoot) footRStepSound->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
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
	case Player::ModelState::DAMAGE:

		motionState = ModelState::DAMAGE;
		pDamage->StartAnimation( 0, false );

		break;
	}
}

void Player::Move()
{
	if ( isAttack || isDamage ) return;

	if ( abs( xInput[0].sLX ) > 250 || abs( xInput[0].sLY ) > 250)
	{
#if 1
		if ( xInput->bL3s )
		{
			// 走りモーションに切り替え
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) * MAX_SPEED * 2;
			moveSpeed.z = cosf(modelData.GetAngle().y) * MAX_SPEED * 2;
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
	//ParticleSystem::GetInstance()->SetPlayerAttackAfterImageParticle(modelData.GetPos(), {0, 0, 0});

	if (isDamage) return;

	if (xInput[0].bXt && !isAttack)
	{
		isAttack = true;
		moveSpeed = { 0, 0, 0 };
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
					attackState = AttackState::ATK2ND;
					enableNextAttack = false;
				}
				else
				{
					isAttack = false;
					enableNextAttack = false;
					attackState = AttackState::ATK1ST;
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
						attackState = AttackState::ATK3RD;
						enableNextAttack = false;
					}
					else
					{
						isAttack = false;
						enableNextAttack = false;
						attackState = AttackState::ATK1ST;
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
				attackCnt = 0;
				isAttack = false;
				enableNextAttack = false;
				attackState = AttackState::ATK1ST;
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
	moveSpeed = { 0.0f, 0.0f, 0.0f };
	hp -= damage;
	isDamageCalc = false;
}


void Player::ImGui()
{
	ImGui::Begin(u8"Player");
	
	ImGui::Text (u8"アニメーションフレーム   : %d" , pAttack[attackCnt]->GetAnimationFrame());

	ImGui::Text (u8"パーティクル数           : %d" , ParticleSystem::GetInstance()->popParticleNum);
	ParticleSystem::GetInstance()->popParticleNum = 0;

	ImGui::Text("angleY : %f", modelData.GetAngle().y);
	ImGui::Text("posX   : %f", modelData.GetPos().x);
	ImGui::Text("posY   : %f", modelData.GetPos().y);
	ImGui::Text("posZ   : %f", modelData.GetPos().z);

	ImGui::Text("HP   : %d", hp);

	ImGui::DragInt(u8"スピード##Player"                  , &MAX_SPEED);
	ImGui::DragInt(u8"次のダメージを受けれるまで##Player", &DAMAGE_TIMER);

	//static int num[2];
	//ImGui::DragInt(u8"1##Player", &num[0]);
	//ImGui::DragInt(u8"2##Player", &num[1]);
	//footRStepSound->SetPos(pWait->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 1738));
	//footLStepSound->SetPos(pWait->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 1627));


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
