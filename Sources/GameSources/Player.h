#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
#include "Billboard.h"

#undef max
#undef min

//creal
#include <cereal/cereal.hpp>

#include <cereal/types/string.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

class PlayerModelManager
{
public:
	std::unique_ptr<Model> pT;
	std::unique_ptr<Model> pWait;
	std::unique_ptr<Model> pRun;
	std::unique_ptr<Model> pDash;
	std::unique_ptr<Model> pAttack[3];
	std::unique_ptr<Model> pDamage;
	std::unique_ptr<Model> pGuard[4];
	std::unique_ptr<Model> pFinalBlow;
	std::unique_ptr<Model> pClear;
	std::unique_ptr<Model> pDead;

public:
	PlayerModelManager() {}
	~PlayerModelManager() {}

	static PlayerModelManager* GetInstance()
	{
		static PlayerModelManager instance;
		return &instance;
	}

public:
	void Init();
};

class Player
{
private:

	enum PlayerAtkCountImGui
	{
		ATTACK_1ST,
		ATTACK_2ND,
		ATTACK_3RD
	};
	enum class GuardState
	{
		GRD1ST,
		GRD2ND,
		GRD3RD,
		GRD4TH
	};
	enum class AttackState
	{
		ATK1ST,
		ATK2ND,
		ATK3RD
	};
	enum class ModelState
	{
		T,
		WAIT,
		RUN,
		DASH,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		GUARD1,
		GUARD2,
		GUARD3,
		GUARD4,
		DAMAGE,
		FINALBLOW,
		CLEAR,
		DEAD
	};

	struct PlayerAttackInfo
	{
		int   inputStartTime;
		int   inputEndTime;
		int   nextAttakTime;
		int   atkCollisionStart;
		int   atkCollisionEnd;
		float power;
		float speed;
	};

	struct BoneInfo
	{
		int meshIndex;
		int boneIndex;
	};

	int MAX_SPEED     = 7;
	int DAMAGE_TIMER  = 30;
	int ATK_NUMBER    = PlayerAtkCountImGui::ATTACK_1ST;
	float ATK_MAG     = 0.01f;
	float FINALBLOW_MAX_SPEEDY = 20.0f;
	// ���i�U���ڂ�
	int attackCnt;
	// �̗�
	int hp;
	// �_���[�W
	int damage;
	// �_���[�W�̃N�[���^�C��
	int damageTimer;
	// �U���{��
	int attackMag;

	// ���v�̍U����
	float totalAttack;

	float finalBlowSpeedY;

	ModelState motionState;


	OBJ3D modelData;

	// ���X�e�B�b�N�̌X���Ă����
	DirectX::XMFLOAT2 leftStickVec;

	// �ړ��X�s�[�h
	DirectX::XMFLOAT3 moveSpeed;

	DirectX::XMFLOAT3 emitFinalBlowPos;

	DirectX::XMFLOAT3 emitPower;

	// �i�K�U���ʏ��
	PlayerAttackInfo attackInfo[3];
	// �U���X�e�[�g
	AttackState attackState;
	// �K�[�h�X�e�[�g
	GuardState  guardState;
	// �E��̃{�[��
	BoneInfo rightBone;
	// ����̃{�[��
	BoneInfo leftBone;
	// �̂̃{�[��
	BoneInfo bodyBone;
	// �E���̃{�[��
	BoneInfo rightFootBone;
	// �����̃{�[��
	BoneInfo leftFootBone;
	// �E�r�̃{�[��
	BoneInfo rightArmBone;

	// �ړ����Ă�����true
	bool isMove;
	//	�X�L�����g�p������true
	bool isFinalBlow;
	//	�X�L�������ɂ��낷�X�s�[�h�ێ�
	bool speedDownTrg;
	//	������
	bool emitThunderStore;
	// �K�[�h���Ă�����ture
	bool isGuard;
	// �K�[�h�����蔻��
	bool onGuardCollision;
	// �K�[�h�����蔻��
	bool onFinalBlowCollision;
	// �K�[�h���e���ꂽ��true
	bool isFlip;
	// �U�����Ă���true
	bool isAttack;
	// �U���I��
	bool isFinishAttack;
	// ���̍U�������邩�ǂ���
	bool enableNextAttack;
	// �U��collision��\�����邩�ǂ���
	bool onAtkCollision;
	// �_���[�W�v�Z��
	bool isDamageCalc;
	// �_���[�W��
	bool isDamage;
	// Player�̓����蔻�� on / off
	bool enableCollision;
	// �E���̉���炷�t���O
	bool makeRightFoot;
	// �����̉���炷�t���O
	bool makeLeftFoot;
	// �a���̋O�Օ\���t���O
	bool isAttackLocusDisplay;
	// ���񂾂��ǂ���
	bool isDead;

	std::unique_ptr<CollisionPrimitive> footRStepSound;
	std::unique_ptr<CollisionPrimitive> footLStepSound;
public:

	std::unique_ptr<CollisionPrimitive> atkCollision;
	std::unique_ptr<CollisionPrimitive> grdCollision;
	std::unique_ptr<CollisionPrimitive> bodyCollision;
	std::unique_ptr<CollisionPrimitive> blowCollision;

	bool clearFlg;
	bool finish;
	bool guardCrash;
private:
	//���[�V�����̐؂�ւ��֐�
	void SwitchMotion(ModelState state);
	//���X�e�B�b�N�̌X���Ă�������擾
	DirectX::XMFLOAT2 GetLeftStickVector();
	// ���X�e�B�b�N�̌X���Ă�p�x���擾
	float GetLeftStickAngle();
	// �_���[�W�v�Z
	void DamageCalc();

	void Move();
	void Attack();
	void Guard();
public:
	Player() {}
	~Player() {}

	void Init();
	void Update();
	void CollisionInformation();
	void Draw();
	void UnInit();

	// �_���[�W���󂯂� : _damage �_���[�W��
	void SufferDamage(int _damage);
	// �K�[�h����
	void SuccessGuard();
	bool GetonGrdCollision() { return onGuardCollision; }
	bool GetOnAtkCollision() { return onAtkCollision; }
	bool GetOnBlowCollision() { return onFinalBlowCollision; }
	bool GetFinalBlow() { return isFinalBlow; }
	bool GetisDamage() { return isDamage; }
	bool GetEmitLocus() { return speedDownTrg; }
	bool GetEmitThunderStore() { return emitThunderStore; }
	bool GetisAttackLocusDisplay() { return isAttackLocusDisplay; }
	bool GetisDead() { return isDead; }
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			cereal::make_nvp("�ړ��X�s�[�h"        , MAX_SPEED),
			cereal::make_nvp("�_���[�W�^�C�}�["    , DAMAGE_TIMER),
			cereal::make_nvp("�U���{��"            , ATK_MAG),

			cereal::make_nvp("�U����1"             , attackInfo[0].power),
			cereal::make_nvp("�U����2"             , attackInfo[1].power),
			cereal::make_nvp("�U����3"             , attackInfo[2].power),

			cereal::make_nvp("���͊J�n����1"       , attackInfo[0].inputStartTime),
			cereal::make_nvp("���͊J�n����2"       , attackInfo[1].inputStartTime),
			cereal::make_nvp("���͊J�n����3"       , attackInfo[2].inputStartTime),

			cereal::make_nvp("���͏I������1"      , attackInfo[0].inputEndTime),
			cereal::make_nvp("���͏I������2"      , attackInfo[1].inputEndTime),
			cereal::make_nvp("���͏I������3"      , attackInfo[2].inputEndTime),

			cereal::make_nvp("���̍U���ɍs������1", attackInfo[0].nextAttakTime),
			cereal::make_nvp("���̍U���ɍs������2", attackInfo[1].nextAttakTime),
			cereal::make_nvp("���̍U���ɍs������3", attackInfo[2].nextAttakTime),

			cereal::make_nvp("�U�������蔻��J�n1", attackInfo[0].atkCollisionStart),
			cereal::make_nvp("�U�������蔻��J�n2", attackInfo[1].atkCollisionStart),
			cereal::make_nvp("�U�������蔻��J�n3", attackInfo[2].atkCollisionStart),

			cereal::make_nvp("�U�������蔻��I��1", attackInfo[0].atkCollisionEnd),
			cereal::make_nvp("�U�������蔻��I��2", attackInfo[1].atkCollisionEnd),
			cereal::make_nvp("�U�������蔻��I��3", attackInfo[2].atkCollisionEnd),

			cereal::make_nvp("���x1"              , attackInfo[0].speed),
			cereal::make_nvp("���x2"              , attackInfo[1].speed),
			cereal::make_nvp("���x3"              , attackInfo[2].speed)
			);
	}

	OBJ3D GetModelData() { return modelData; }
	void SetModelPosition(DirectX::XMFLOAT3 _pos) { modelData.SetPos(_pos); }
	void SetMoveSpeed(DirectX::XMFLOAT3 _speed) { moveSpeed = _speed; }
	int GetHp() { return hp; }
	void SetAttackMag(int mag) { attackMag = mag; }
	float GetAttackDamage() 
	{
		totalAttack = attackInfo[attackCnt].power * (1.0f + 0.10f * attackMag);
		return totalAttack; 
	}
	void ImGui();


};