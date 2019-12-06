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
		ATTACK3
	};

	struct PlayerAttackInfo
	{
		int inputAttackButton;
		float power;
	};

	int MAX_SPEED  = 10;
	int ATK_NUMBER = PlayerAtkCountImGui::ATTACK_1ST;

	ModelState motionState;

	std::unique_ptr<Model> pT;
	std::unique_ptr<Model> pWait;
	std::unique_ptr<Model> pRun;
	std::unique_ptr<Model> pAttack[3];

	OBJ3D modelData;

	// 左スティックの傾いてる方向
	DirectX::XMFLOAT2 leftStickVec;

	// 移動スピード
	DirectX::XMFLOAT3 moveSpeed;

	PlayerAttackInfo attackInfo[3];

	// 移動していたらtrue
	bool isMove;
	// 攻撃してたらtrue
	bool isAttack;
	//次の攻撃をするかどうか
	bool enableNextAttack;
	// 何段攻撃目か
	int attackCnt;
	//攻撃ステート
	AttackState attackState;

	DirectX::XMFLOAT3 addModelPos = {};
	int vectexPosNo = 0;

	//Collision
	std::unique_ptr<CollisionPrimitive> atkCollision;
	std::unique_ptr<CollisionPrimitive> bodyCollision;
	std::unique_ptr<CollisionPrimitive> SSS;
	float hosei;
private:
	//モーションの切り替え関数
	void SwitchMotion(ModelState state);
	//左スティックの傾いてる方向を取得
	DirectX::XMFLOAT2 GetLeftStickVector();
	// 左スティックの傾いてる角度を取得
	float GetLeftStickAngle();

public:
	Player() {}
	~Player() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	void Attack();
	void Move();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			cereal::make_nvp("移動スピード", MAX_SPEED),
			cereal::make_nvp("攻撃力1", attackInfo[0].power),
			cereal::make_nvp("攻撃力2", attackInfo[1].power),
			cereal::make_nvp("攻撃力3", attackInfo[2].power)
			);
	}

	OBJ3D GetModelData() { return modelData; }

	DirectX::XMFLOAT3 SphereLinear(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, float t)
	{
		DirectX::XMVECTOR s = DirectX::XMLoadFloat3(&start);
		s = DirectX::XMVector3Normalize(s);
		DirectX::XMVECTOR e = DirectX::XMLoadFloat3(&end);
		e = DirectX::XMVector3Normalize(e);

		// 2ベクトル間の角度（鋭角側）
		DirectX::XMVECTOR vecAngle = DirectX::XMVector3Dot(s, e);
		float angle = 0;
		DirectX::XMStoreFloat(&angle, vecAngle);
		// sinθ
		float SinTh = sin(angle);
		DirectX::XMVECTOR vecSinTh = DirectX::XMLoadFloat(&SinTh);
		// 補間係数
		float Ps = sin(angle * (1 - t));
		float Pe = sin(angle * t);

		DirectX::XMVECTOR vecPs = DirectX::XMLoadFloat(&Ps);
		DirectX::XMVECTOR vecPe = DirectX::XMLoadFloat(&Pe);
		vecPs = DirectX::XMVectorMultiply(s, vecPs);
		vecPe = DirectX::XMVectorMultiply(e, vecPe);

		DirectX::XMVECTOR ansAdd = DirectX::XMVectorAdd(vecPs, vecPe);
		ansAdd = DirectX::XMVectorDivide(ansAdd, vecSinTh);
		// 一応正規化して球面線形補間に
		ansAdd = DirectX::XMVector3Normalize(ansAdd);
		DirectX::XMFLOAT3 out;
		DirectX::XMStoreFloat3(&out, ansAdd);
		return out;
	}


	void ImGui();

};