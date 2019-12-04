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
		// �U�������t���[�����͂��󂯕t���邩
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

	// ���X�e�B�b�N�̌X���Ă����
	DirectX::XMFLOAT2 leftStickVec;

	// �ړ��X�s�[�h
	DirectX::XMFLOAT3 moveSpeed;

	// ���i�U���ڂ�
	int attackCnt;
	PlayerAttackInfo attackInfo[3];

	// �ړ����Ă�����true
	bool isMove;
	// �U�����Ă���true
	bool isAttack;
	bool nextAttack;

	DirectX::XMFLOAT3 addModelPos = {};
	int vectexPosNo = 0;
	std::unique_ptr<CollisionPrimitive> atkCollision;

private:

	//���[�V�����̐؂�ւ��֐�
	void SwitchMotion(ModelState state);
	//���X�e�B�b�N�̌X���Ă�������擾
	DirectX::XMFLOAT2 GetLeftStickVector();
	// ���X�e�B�b�N�̌X���Ă�p�x���擾
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
			cereal::make_nvp("�ړ��X�s�[�h", MAX_SPEED),
			cereal::make_nvp("�U����1", attackInfo[0].power),
			cereal::make_nvp("�U����2", attackInfo[1].power),
			cereal::make_nvp("�U����3", attackInfo[2].power)
			);
	}

	OBJ3D GetModelData() { return modelData; }


	void ImGui();

};