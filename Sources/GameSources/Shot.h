#pragma once
#include "OBJ3D.h"
#define SPPED_ARROW 5

class Shot
{
public:
	Shot(DirectX::XMFLOAT3 pPos, DirectX::XMFLOAT3 ePos);
	~Shot() {};

	void Update();
	void Draw();

	OBJ3DInstance& GetModelData() { return modelData; };
private:

	OBJ3DInstance modelData;
	DirectX::XMFLOAT3 pVec;

};