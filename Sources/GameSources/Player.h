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

	// ���X�e�B�b�N�̌X���Ă����
	DirectX::XMFLOAT2 leftStickVec;

	// �ړ��X�s�[�h
	DirectX::XMFLOAT3 moveSpeed;

	PlayerAttackInfo attackInfo[3];

	// �ړ����Ă�����true
	bool isMove;
	// �U�����Ă���true
	bool isAttack;
	//���̍U�������邩�ǂ���
	bool enableNextAttack;
	// ���i�U���ڂ�
	int attackCnt;
	//�U���X�e�[�g
	AttackState attackState;

	DirectX::XMFLOAT3 addModelPos = {};
	int vectexPosNo = 0;

	//Collision
	std::unique_ptr<CollisionPrimitive> atkCollision;
	std::unique_ptr<CollisionPrimitive> bodyCollision;
	std::unique_ptr<CollisionPrimitive> SSS;
	float hosei;
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

	DirectX::XMFLOAT3 SphereLinear(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, float t)
	{
		DirectX::XMVECTOR s = DirectX::XMLoadFloat3(&start);
		s = DirectX::XMVector3Normalize(s);
		DirectX::XMVECTOR e = DirectX::XMLoadFloat3(&end);
		e = DirectX::XMVector3Normalize(e);

		// 2�x�N�g���Ԃ̊p�x�i�s�p���j
		DirectX::XMVECTOR vecAngle = DirectX::XMVector3Dot(s, e);
		float angle = 0;
		DirectX::XMStoreFloat(&angle, vecAngle);
		// sin��
		float SinTh = sin(angle);
		DirectX::XMVECTOR vecSinTh = DirectX::XMLoadFloat(&SinTh);
		// ��ԌW��
		float Ps = sin(angle * (1 - t));
		float Pe = sin(angle * t);

		DirectX::XMVECTOR vecPs = DirectX::XMLoadFloat(&Ps);
		DirectX::XMVECTOR vecPe = DirectX::XMLoadFloat(&Pe);
		vecPs = DirectX::XMVectorMultiply(s, vecPs);
		vecPe = DirectX::XMVectorMultiply(e, vecPe);

		DirectX::XMVECTOR ansAdd = DirectX::XMVectorAdd(vecPs, vecPe);
		ansAdd = DirectX::XMVectorDivide(ansAdd, vecSinTh);
		// �ꉞ���K�����ċ��ʐ��`��Ԃ�
		ansAdd = DirectX::XMVector3Normalize(ansAdd);
		DirectX::XMFLOAT3 out;
		DirectX::XMStoreFloat3(&out, ansAdd);
		return out;
	}


	void ImGui();

};