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
	pT         = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerT.fbx"   , false);
	pWait      = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerStay.fbx"   , false);
	pRun       = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerRun.fbx"    , false);
	pAttack[0] = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack1.fbx", false);
	pAttack[1] = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack2.fbx", false);
	pAttack[2] = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerAttack3.fbx", false);
	pDamage    = std::make_unique<Model>("Data/Assets/Model/Pl/PlayerOuch.fbx", false);
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


	atkCollision         = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(45, 45, 45));
	atkCollision->SetColor({ 0, 1, 0, 1 });

	footRStepSound = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	footRStepSound->SetColor({ 0, 1, 0, 1 });

	footLStepSound = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	footLStepSound->SetColor({ 0, 1, 0, 1 });

	attackAfterImageEmit = std::make_unique<CollisionPrimitive>(1, true, DirectX::XMFLOAT3(10, 10, 10));
	attackAfterImageEmit->SetColor({ 0, 1, 0, 1 });

	bodyCollision        = std::make_unique<CollisionPrimitive>(2, true, DirectX::XMFLOAT3(25, 80, 25));
	bodyCollision->SetColor({ 0, 1, 0, 1 });

	hp                              = 10000;
	damage                          = 0;
	damageTimer                     = DAMAGE_TIMER;

	leftStickVec                    = {0, 0};

	moveSpeed                       = {0, 0, 0};
	oldAtkPos                       = {0, 0, 0};

	attackMag                       = 0.0f;
	totalAttack                     = 0.0f;

	// �U���J�E���g( 0 ~ 2 )
	attackCnt                       = 0;
	// �_���[�W��
	attackInfo[0].power             = 0.0f;
	attackInfo[1].power             = 0.0f;
	attackInfo[2].power             = 0.0f;
	// ���͊J�n����
	attackInfo[0].inputStartTime    = 5;
	attackInfo[1].inputStartTime    = 5;
	attackInfo[2].inputStartTime    = 0;
	// ���͏I������
	attackInfo[0].inputEndTime      = 20;
	attackInfo[1].inputEndTime      = 20;
	attackInfo[2].inputEndTime      = 0;
	// ���̍U���ɍs������
	attackInfo[0].nextAttakTime     = 20;
	attackInfo[1].nextAttakTime     = 20;
	attackInfo[2].nextAttakTime     = 30;
	// �U�������蔻��J�n
	attackInfo[0].atkCollisionStart = 10;
	attackInfo[1].atkCollisionStart = 10;
	attackInfo[2].atkCollisionStart = 10;
	// �U�������蔻��I��
	attackInfo[0].atkCollisionEnd   = 20;
	attackInfo[1].atkCollisionEnd   = 30;
	attackInfo[2].atkCollisionEnd   = 20;
	// �U�����̈ړ��X�s�[�h
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

	// json�ǂݍ���
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

	// Collsion
	switch (motionState)
	{
	case ModelState::WAIT:
		bodyCollision->SetPos(pWait->GetVectexPos(std::string("Player"), { -2, -59, 7 }, modelData.GetWorldMatrix(), 0));
		atkCollision->SetPos (pWait->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		break;

	case ModelState::RUN:
		bodyCollision->SetPos       (pRun->GetVectexPos(std::string("Player"), { -2, -59, 7 }, modelData.GetWorldMatrix(), 0));
		atkCollision->SetPos        (pRun->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));

		footLStepSound->SetPos(pRun->GetVectexPos(std::string("Player"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 13172));
		footRStepSound->SetPos(pRun->GetVectexPos(std::string("Player"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 13348));

		if (!makeRightFoot && footRStepSound->GetPos().y <= 0.6f)
		{
			makeRightFoot = true;
			////PlaySoundMem(SoundLoader::GetInstance()->playerStepSe.get());
			////SetVolume(SoundLoader::GetInstance()->playerStepSe.get(), 0.1f);
		}
		else if (footRStepSound->GetPos().y > 1.5f)
		{
			makeRightFoot = false;
		}

		if (!makeLeftFoot && footLStepSound->GetPos().y <= 0.6f)
		{
			makeLeftFoot = true;
			//PlaySoundMem(SoundLoader::GetInstance()->playerStepSe.get());
			//SetVolume(SoundLoader::GetInstance()->playerStepSe.get(), 0.1f);
		}
		else if (footLStepSound->GetPos().y > 0.3f)
		{
			makeLeftFoot = false;
		}

		break;

	case ModelState::ATTACK1:
		bodyCollision->SetPos       (pAttack[0]->GetVectexPos(std::string("Player"), { -2, -59, 7 }, modelData.GetWorldMatrix(), 0));
		atkCollision->SetPos        (pAttack[0]->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		attackAfterImageEmit->SetPos(pAttack[0]->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		break;

	case ModelState::ATTACK2:
		bodyCollision->SetPos       (pAttack[1]->GetVectexPos(std::string("Player"), { -2, -59, 7 }, modelData.GetWorldMatrix(), 0));
		atkCollision->SetPos        (pAttack[1]->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		attackAfterImageEmit->SetPos(pAttack[1]->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		break;

	case ModelState::ATTACK3:
		bodyCollision->SetPos       (pAttack[2]->GetVectexPos(std::string("Player"), { -2, -59, 7 }, modelData.GetWorldMatrix(), 0));
		atkCollision->SetPos        (pAttack[2]->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		attackAfterImageEmit->SetPos(pAttack[2]->GetVectexPos(std::string("Sword") , {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		break;

	case ModelState::DAMAGE:
		bodyCollision->SetPos       (pDamage->GetVectexPos(std::string("Player"),  { -2, -59, 7 }, modelData.GetWorldMatrix(), 0));
		atkCollision->SetPos        (pDamage->GetVectexPos(std::string("Sword") ,  {  0,   0, 0 }, modelData.GetWorldMatrix(), 0));
		break;

	}


	CameraControl::PadControlUpdate(&CameraSystem::GetInstance()->mainView);

	//ImGui();
	DamageCalc();

	modelData.SetPosX(modelData.GetPos().x + moveSpeed.x);
	modelData.SetPosZ(modelData.GetPos().z + moveSpeed.z);

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

		pRun->Render     ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			               DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK1:
		pAttack[0]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pAttack[0]->Render( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK2:
		pAttack[1]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE), false );

		pAttack[1]->Render     ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                     DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::ATTACK3:
		pAttack[2]->Preparation( ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh( ShaderSystem::PHONE ), false );

		pAttack[2]->Render     ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                     DirectX::XMFLOAT4( 0.0f, -1.0f, 1.0f, 0.0f ), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime() );
		break;
	case ModelState::DAMAGE:
		pDamage->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::PHONE), false);

		pDamage->Render     ( modelData.GetWorldMatrix(), CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(),
			                  DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
		break;
	}
#ifdef _DEBUG
	if (enableCollision)
	{
		if (onAtkCollision) atkCollision->Render  (CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		                    bodyCollision->Render (CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		if(makeLeftFoot)    footLStepSound->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		if(makeRightFoot)   footRStepSound->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
		if(onAtkCollision)  attackAfterImageEmit->Render(CameraSystem::GetInstance()->mainView.GetViewMatrix(), CameraSystem::GetInstance()->mainView.GetProjectionMatrix(), DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), FrameWork::GetInstance().GetElapsedTime());
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

// �E�X�e�B�b�N�̌X���Ă�p�x���擾	
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
		//PlaySoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
		//SetVolume(SoundLoader::GetInstance()->playerAttackSwingSe.get(), 1.0f);
		break;
	case Player::ModelState::ATTACK2:

		motionState = ModelState::ATTACK2;
		pAttack[1]->StartAnimation( 0, false );
		//PlaySoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
		//SetVolume(SoundLoader::GetInstance()->playerAttackSwingSe.get(), 1.0f);

		break;
	case Player::ModelState::ATTACK3:

		motionState = ModelState::ATTACK3;
		pAttack[2]->StartAnimation( 0, false );
		//PlaySoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
		//SetVolume(SoundLoader::GetInstance()->playerAttackSwingSe.get(), 1.0f);

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
			// ���胂�[�V�����ɐ؂�ւ�
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) * MAX_SPEED * 2;
			moveSpeed.z = cosf(modelData.GetAngle().y) * MAX_SPEED * 2;
			isMove = true;
		}
		else
		{
			// ���胂�[�V�����ɐ؂�ւ�
			SwitchMotion(ModelState::RUN);

			modelData.SetAngle(DirectX::XMFLOAT3(0, CameraSystem::GetInstance()->mainView.GetRotateY() + DirectX::XM_PI + GetLeftStickAngle(), 0));
			moveSpeed.x = sinf(modelData.GetAngle().y) * MAX_SPEED;
			moveSpeed.z = cosf(modelData.GetAngle().y) * MAX_SPEED;
			isMove = true;
		}
#else
		if ( xInput->bL3s )
		{
			// ���胂�[�V�����ɐ؂�ւ�
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
			// ���胂�[�V�����ɐ؂�ւ�
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
		// �ҋ@���[�V�����ɐ؂�ւ�
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
		oldAtkPos = { 0.0f, 0.0f, 0.0f };
	}

	if (isAttack)
	{
		switch (attackState)
		{
		case AttackState::ATK1ST:
			

			SwitchMotion(ModelState::ATTACK1);
			attackCnt = 0;
			// ����
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].inputStartTime && pAttack[attackCnt]->GetAnimationFrame() <= attackInfo[attackCnt].inputEndTime)
			{
				atkCollision->GetPos();

				if (xInput[0].bXt)
				{
					enableNextAttack = true;
				}
			}

			if(pAttack[attackCnt]->GetAnimationFrame() > 10 ) if (oldAtkPos.x == 0 && oldAtkPos.y == 0 && oldAtkPos.z == 0) oldAtkPos = atkCollision->GetPos();


			moveSpeed.x = sinf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;
			moveSpeed.z = cosf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;

			// Collision�\��
			if (pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionStart && pAttack[attackCnt]->GetAnimationFrame() < attackInfo[attackCnt].atkCollisionEnd)
			{
				onAtkCollision = true;
			}
			else if(pAttack[attackCnt]->GetAnimationFrame() > attackInfo[attackCnt].atkCollisionEnd)
			{
				onAtkCollision = false;
				moveSpeed.x = 0.0f;
				moveSpeed.z = 0.0f;
				
				//ParticleSystem::GetInstance()->SetPlayerAttackAfterImageParticle(modelData.GetPos(), oldAtkPos, atkCollision->GetPos(), {0, 0, 0});

			}

			// 2�i�ڂɂ������ǂ���
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
				oldAtkPos = { 0.0f, 0.0f, 0.0f };
			}
			break;
		case AttackState::ATK2ND:
				SwitchMotion(ModelState::ATTACK2);
				attackCnt = 1;
				// ����
				if (pAttack[1]->GetAnimationFrame() > attackInfo[attackCnt].inputStartTime && pAttack[attackCnt]->GetAnimationFrame() <= attackInfo[attackCnt].inputEndTime)
				{
					if (xInput[0].bXt)
					{
						enableNextAttack = true;
					}
				}

				moveSpeed.x = sinf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;
				moveSpeed.z = cosf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;

				// Collision�\��
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

				// 3�i�ڂɂ������ǂ���
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
					oldAtkPos = { 0.0f, 0.0f, 0.0f };
				}
			break;
		case AttackState::ATK3RD:
			SwitchMotion(ModelState::ATTACK3);
			attackCnt = 2;

			moveSpeed.x = sinf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;
			moveSpeed.z = cosf(modelData.GetAngle().y) * attackInfo[attackCnt].speed;

			// Collision�\��
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
				oldAtkPos = { 0.0f, 0.0f, 0.0f };
			}
			break;
		}
	}
}

void Player::SufferDamage(int _damage)
{
	// �_���[�W���󂯂Ă���r���Ȃ瑦Return
	if (isDamage) return;
	isDamageCalc = true;
	isDamage     = true;
	// �󂯂�_���[�W�ʂ���
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
	// ��_�����[�V�����ɐ؂�ւ�
	SwitchMotion(ModelState::DAMAGE);
	attackCnt = 0;
	isAttack = false;
	enableNextAttack = false;
	attackState = AttackState::ATK1ST;
	moveSpeed = { 0.0f, 0.0f, 0.0f };
	oldAtkPos = { 0.0f, 0.0f, 0.0f };
	hp -= damage;
	isDamageCalc = false;
}


void Player::ImGui()
{
	ImGui::Begin(u8"Player");
	
	ImGui::Text (u8"���v�U��                 : %f" , totalAttack);
	ImGui::Text (u8"�A�j���[�V�����t���[��   : %d" , pWait->GetAnimationFrame());

	ImGui::Text (u8"�p�[�e�B�N����           : %d" , ParticleSystem::GetInstance()->popParticleNum);
	ParticleSystem::GetInstance()->popParticleNum = 0;

	ImGui::Text("angleY : %f", modelData.GetAngle().y);
	ImGui::Text("posX   : %f", modelData.GetPos().x);
	ImGui::Text("posY   : %f", modelData.GetPos().y);
	ImGui::Text("posZ   : %f", modelData.GetPos().z);

	ImGui::Text("HP   : %d", hp);

	ImGui::DragInt  (u8"�X�s�[�h##Player"                  , &MAX_SPEED);
	ImGui::DragInt  (u8"���̃_���[�W���󂯂��܂�##Player", &DAMAGE_TIMER);
	ImGui::DragFloat(u8"�U���{��##Player"                  , &ATK_MAG);

	static int num[1];
	static DirectX::XMFLOAT3 _p = {};
	ImGui::DragInt(u8"1##Player", &num[0]);
	//ImGui::DragInt(u8"2##Player", &num[1]);
	ImGui::DragFloat3(u8"3##Player", &_p.x);

	//attackAfterImageEmit->SetPos(pWait->GetVectexPos(std::string("model1"), { 0, 0, 0 }, modelData.GetWorldMatrix(), 9));

	ImGui::RadioButton("1st##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_1ST);
	ImGui::SameLine();
	ImGui::RadioButton("2nd##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_2ND);
	ImGui::SameLine();
	ImGui::RadioButton("3rd##Player", &ATK_NUMBER, PlayerAtkCountImGui::ATTACK_3RD);

	if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_1ST)
	{

		ImGui::DragFloat(u8"�U����##Player"                , &attackInfo[0].power);
		ImGui::DragInt  (u8"���͊J�n##Player"              , &attackInfo[0].inputStartTime);
		ImGui::DragInt  (u8"���͏I��##Player"              , &attackInfo[0].inputEndTime);
		ImGui::DragInt  (u8"���̍U���ւ�������##Player"    , &attackInfo[0].nextAttakTime);
		ImGui::DragInt  (u8"�����蔻��\���J�n##Player"    , &attackInfo[0].atkCollisionStart);
		ImGui::DragInt  (u8"�����蔻��\���I��##Player"    , &attackInfo[0].atkCollisionEnd);
		ImGui::DragFloat(u8"�U���̎��̃X�s�[�h##Player"    , &attackInfo[0].speed);

	}
	else if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_2ND)
	{

		ImGui::DragFloat(u8"�U����##Player"               , &attackInfo[1].power);
		ImGui::DragInt  (u8"���͊J�n##Player"             , &attackInfo[1].inputStartTime);
		ImGui::DragInt  (u8"���͏I��##Player"             , &attackInfo[1].inputEndTime);
		ImGui::DragInt  (u8"���̍U���ւ�������##Player"   , &attackInfo[1].nextAttakTime);
		ImGui::DragInt  (u8"�����蔻��\���J�n##Player"   , &attackInfo[1].atkCollisionStart);
		ImGui::DragInt  (u8"�����蔻��\���I��##Player"   , &attackInfo[1].atkCollisionEnd);
		ImGui::DragFloat(u8"�U���̎��̃X�s�[�h##Player"   , &attackInfo[1].speed);
	}
	else if (ATK_NUMBER == PlayerAtkCountImGui::ATTACK_3RD)
	{

		ImGui::DragFloat(u8"�U����##Player"               , &attackInfo[2].power);
		ImGui::DragInt  (u8"���͊J�n##Player"             , &attackInfo[2].inputStartTime);
		ImGui::DragInt  (u8"���͏I��##Player"             , &attackInfo[2].inputEndTime);
		ImGui::DragInt  (u8"���̍U���ւ�������##Player"   , &attackInfo[2].nextAttakTime);
		ImGui::DragInt  (u8"�����蔻��\���J�n##Player"   , &attackInfo[2].atkCollisionStart);
		ImGui::DragInt  (u8"�����蔻��\���I��##Player"   , &attackInfo[2].atkCollisionEnd);
		ImGui::DragFloat(u8"�U���̎��̃X�s�[�h##Player"   , &attackInfo[2].speed);
	}

	ImGui::Checkbox(u8"�v���C���[�̓����蔻�� on / off ##Player", &enableCollision);

	//cereal ��json ��binary �ɕۑ�
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
