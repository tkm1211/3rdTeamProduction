#pragma once
#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
//creal
#include <cereal/cereal.hpp>

#include <cereal/types/string.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>




class Player
{
private:
	enum PlayerAtkCountImGui
	{
		ATTACK_1ST,
		ATTACK_2ND,
		ATTACK_3RD
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
		ATTACK1,
		ATTACK2,
		ATTACK3,
		DAMAGE
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

	int MAX_SPEED     = 10;
	int DAMAGE_TIMER  = 60;
	int ATK_NUMBER    = PlayerAtkCountImGui::ATTACK_1ST;

	// 何段攻撃目か
	int attackCnt;
	// 体力
	int hp;
	// ダメージ
	int damage;
	// ダメージのクールタイム
	int damageTimer;

	ModelState motionState;

	std::unique_ptr<Model> pT;
	std::unique_ptr<Model> pWait;
	std::unique_ptr<Model> pRun;
	std::unique_ptr<Model> pAttack[3];
	std::unique_ptr<Model> pDamage;

	OBJ3D modelData;

	// 左スティックの傾いてる方向
	DirectX::XMFLOAT2 leftStickVec;

	// 移動スピード
	DirectX::XMFLOAT3 moveSpeed;

	// 段階攻撃別情報
	PlayerAttackInfo attackInfo[3];

	// 攻撃ステート
	AttackState attackState;

	// 移動していたらtrue
	bool isMove;
	// 攻撃してたらtrue
	bool isAttack;
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
public:
	std::unique_ptr<CollisionPrimitive> atkCollision;
	std::unique_ptr<CollisionPrimitive> bodyCollision;

private:
	//モーションの切り替え関数
	void SwitchMotion(ModelState state);
	//左スティックの傾いてる方向を取得
	DirectX::XMFLOAT2 GetLeftStickVector();
	// 左スティックの傾いてる角度を取得
	float GetLeftStickAngle();
	// ダメージ計算
	void DamageCalc();
public:
	Player() {}
	~Player() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void Attack();
	void Move();

	// ダメージを受ける : _damage ダメージ量
	void SufferDamage(int _damage);
	bool GetOnAtkCollision() { return onAtkCollision; }
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			cereal::make_nvp("移動スピード"        , MAX_SPEED),
			cereal::make_nvp("ダメージタイマー"    , DAMAGE_TIMER),

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


	void ImGui();

	DirectX::XMFLOAT3 SphereLinear // 戻り値 : 補間座標
	(
		DirectX::XMFLOAT3 _start, // ベクトル
		DirectX::XMFLOAT3 _end,   // ベクトル
		float t					  // 補間値（0.0f ～ 1.0f）
	)
	{
		DirectX::XMVECTOR start, end;
		start = DirectX::XMVector3Normalize(DirectX::XMVectorSet(_start.x, _start.y, _start.z, 1.0f));
		end = DirectX::XMVector3Normalize(DirectX::XMVectorSet(_end.x, _end.y, _end.z, 1.0f));

		float angle = acosf(DirectX::XMVectorGetX(DirectX::XMVector3Dot(start, end)));

		float sinSita = sinf(angle);

		float startPoint = sinf(angle * (1 - t));
		float endPoint = sinf(angle * t);

		DirectX::XMFLOAT3 startFloat3, endFloat3;
		DirectX::XMStoreFloat3(&startFloat3, start);
		DirectX::XMStoreFloat3(&endFloat3, end);

		float len = sqrtf(_start.x * _start.x + _start.y * _start.y + _start.z * _start.z);

		DirectX::XMFLOAT3 out;
		out.x = ((startPoint * startFloat3.x + endPoint * endFloat3.x) / sinSita) * len;
		out.y = ((startPoint * startFloat3.y + endPoint * endFloat3.y) / sinSita) * len;
		out.z = ((startPoint * startFloat3.z + endPoint * endFloat3.z) / sinSita) * len;

		return out;
	}

};