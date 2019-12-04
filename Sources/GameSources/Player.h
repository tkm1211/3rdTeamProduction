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
	enum PlayerAtkCount
	{
		ATTACK_1ST,
		ATTACK_2ND,
		ATTACK_3RD
	};


	int MAX_SPEED  = 10;
	int ATK_NUMBER = PlayerAtkCount::ATTACK_1ST;
	struct PlayerAttackInfo
	{
		// 攻撃中何フレーム入力を受け付けるか
		int inputAttackTime;
		float power;

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

	// 何段攻撃目か
	int attackCnt;
	PlayerAttackInfo attackInfo[3];

	// 移動していたらtrue
	bool isMove;
	// 攻撃してたらtrue
	bool isAttack;
	bool nextAttack;

	DirectX::XMFLOAT3 addModelPos = {};
	int vectexPosNo = 0;
	std::unique_ptr<CollisionPrimitive> atkCollision;

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


	void ImGui();

};