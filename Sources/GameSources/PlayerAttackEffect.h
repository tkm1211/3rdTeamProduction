#pragma once

#include "Model.h"
#include "OBJ3D.h"
#include "Collision.h"
#include "Billboard.h"
#include <vector>

class PlayerAttackEffect
{
private:
	struct EffectsInfo
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 angle;
		DirectX::XMFLOAT2 scale;
		DirectX::XMFLOAT2 texcoord;
		int animationTime;
		int elapsedTime;
		bool startFlag;
	};
	std::vector<EffectsInfo> effects;

	std::unique_ptr<Billboard> texture;

public:
	PlayerAttackEffect() {}
	~PlayerAttackEffect() {}

	void Init();
	void Update();
	void Draw();
	void UnInit();

	// _pos : ç¿ïW,	attackNum : âΩíiçUåÇñ⁄Ç©
	void SetEffectInfo(DirectX::XMFLOAT3 _pos, int attackNum);
};