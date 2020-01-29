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
	// 何段攻撃目か
	int attackCnt;
	// 体力
	int hp;
	// ダメージ
	int damage;
	// ダメージのクールタイム
	int damageTimer;
	// 攻撃倍率
	int attackMag;

	// 合計の攻撃力
	float totalAttack;

	float finalBlowSpeedY;

	ModelState motionState;


	OBJ3D modelData;

	// 左スティックの傾いてる方向
	DirectX::XMFLOAT2 leftStickVec;

	// 移動スピード
	DirectX::XMFLOAT3 moveSpeed;

	DirectX::XMFLOAT3 emitFinalBlowPos;

	DirectX::XMFLOAT3 emitPower;

	// 段階攻撃別情報
	PlayerAttackInfo attackInfo[3];
	// 攻撃ステート
	AttackState attackState;
	// ガードステート
	GuardState  guardState;
	// 右手のボーン
	BoneInfo rightBone;
	// 左手のボーン
	BoneInfo leftBone;
	// 体のボーン
	BoneInfo bodyBone;
	// 右足のボーン
	BoneInfo rightFootBone;
	// 左足のボーン
	BoneInfo leftFootBone;
	// 右腕のボーン
	BoneInfo rightArmBone;

	// 移動していたらtrue
	bool isMove;
	//	スキルを使用したらtrue
	bool isFinalBlow;
	//	スキル中下におろすスピード保持
	bool speedDownTrg;
	//	雷ため
	bool emitThunderStore;
	// ガードしていたらture
	bool isGuard;
	// ガード当たり判定
	bool onGuardCollision;
	// ガード当たり判定
	bool onFinalBlowCollision;
	// ガードが弾かれたらtrue
	bool isFlip;
	// 攻撃してたらtrue
	bool isAttack;
	// 攻撃終了
	bool isFinishAttack;
	// 次の攻撃をするかどうか
	bool enableNextAttack;
	// 攻撃collisionを表示するかどうか
	bool onAtkCollision;
	// ダメージ計算中
	bool isDamageCalc;
	// ダメージ中
	bool isDamage;
	// Playerの当たり判定 on / off
	bool enableCollision;
	// 右足の音を鳴らすフラグ
	bool makeRightFoot;
	// 左足の音を鳴らすフラグ
	bool makeLeftFoot;
	// 斬撃の軌跡表示フラグ
	bool isAttackLocusDisplay;
	// 死んだかどうか
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
	//モーションの切り替え関数
	void SwitchMotion(ModelState state);
	//左スティックの傾いてる方向を取得
	DirectX::XMFLOAT2 GetLeftStickVector();
	// 左スティックの傾いてる角度を取得
	float GetLeftStickAngle();
	// ダメージ計算
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

	// ダメージを受ける : _damage ダメージ量
	void SufferDamage(int _damage);
	// ガード成功
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
			cereal::make_nvp("移動スピード"        , MAX_SPEED),
			cereal::make_nvp("ダメージタイマー"    , DAMAGE_TIMER),
			cereal::make_nvp("攻撃倍率"            , ATK_MAG),

			cereal::make_nvp("攻撃力1"             , attackInfo[0].power),
			cereal::make_nvp("攻撃力2"             , attackInfo[1].power),
			cereal::make_nvp("攻撃力3"             , attackInfo[2].power),

			cereal::make_nvp("入力開始時間1"       , attackInfo[0].inputStartTime),
			cereal::make_nvp("入力開始時間2"       , attackInfo[1].inputStartTime),
			cereal::make_nvp("入力開始時間3"       , attackInfo[2].inputStartTime),

			cereal::make_nvp("入力終了時間1"      , attackInfo[0].inputEndTime),
			cereal::make_nvp("入力終了時間2"      , attackInfo[1].inputEndTime),
			cereal::make_nvp("入力終了時間3"      , attackInfo[2].inputEndTime),

			cereal::make_nvp("次の攻撃に行く時間1", attackInfo[0].nextAttakTime),
			cereal::make_nvp("次の攻撃に行く時間2", attackInfo[1].nextAttakTime),
			cereal::make_nvp("次の攻撃に行く時間3", attackInfo[2].nextAttakTime),

			cereal::make_nvp("攻撃当たり判定開始1", attackInfo[0].atkCollisionStart),
			cereal::make_nvp("攻撃当たり判定開始2", attackInfo[1].atkCollisionStart),
			cereal::make_nvp("攻撃当たり判定開始3", attackInfo[2].atkCollisionStart),

			cereal::make_nvp("攻撃当たり判定終了1", attackInfo[0].atkCollisionEnd),
			cereal::make_nvp("攻撃当たり判定終了2", attackInfo[1].atkCollisionEnd),
			cereal::make_nvp("攻撃当たり判定終了3", attackInfo[2].atkCollisionEnd),

			cereal::make_nvp("速度1"              , attackInfo[0].speed),
			cereal::make_nvp("速度2"              , attackInfo[1].speed),
			cereal::make_nvp("速度3"              , attackInfo[2].speed)
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