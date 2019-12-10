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

	// ���i�U���ڂ�
	int attackCnt;
	// �̗�
	int hp;
	// �_���[�W
	int damage;
	// �_���[�W�̃N�[���^�C��
	int damageTimer;

	ModelState motionState;

	std::unique_ptr<Model> pT;
	std::unique_ptr<Model> pWait;
	std::unique_ptr<Model> pRun;
	std::unique_ptr<Model> pAttack[3];
	std::unique_ptr<Model> pDamage;

	OBJ3D modelData;

	// ���X�e�B�b�N�̌X���Ă����
	DirectX::XMFLOAT2 leftStickVec;

	// �ړ��X�s�[�h
	DirectX::XMFLOAT3 moveSpeed;

	// �i�K�U���ʏ��
	PlayerAttackInfo attackInfo[3];

	// �U���X�e�[�g
	AttackState attackState;

	// �ړ����Ă�����true
	bool isMove;
	// �U�����Ă���true
	bool isAttack;
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
public:
	std::unique_ptr<CollisionPrimitive> atkCollision;
	std::unique_ptr<CollisionPrimitive> bodyCollision;

private:
	//���[�V�����̐؂�ւ��֐�
	void SwitchMotion(ModelState state);
	//���X�e�B�b�N�̌X���Ă�������擾
	DirectX::XMFLOAT2 GetLeftStickVector();
	// ���X�e�B�b�N�̌X���Ă�p�x���擾
	float GetLeftStickAngle();
	// �_���[�W�v�Z
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

	// �_���[�W���󂯂� : _damage �_���[�W��
	void SufferDamage(int _damage);
	bool GetOnAtkCollision() { return onAtkCollision; }
	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			cereal::make_nvp("�ړ��X�s�[�h"        , MAX_SPEED),
			cereal::make_nvp("�_���[�W�^�C�}�["    , DAMAGE_TIMER),

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


	void ImGui();

	DirectX::XMFLOAT3 SphereLinear // �߂�l : ��ԍ��W
	(
		DirectX::XMFLOAT3 _start, // �x�N�g��
		DirectX::XMFLOAT3 _end,   // �x�N�g��
		float t					  // ��Ԓl�i0.0f �` 1.0f�j
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