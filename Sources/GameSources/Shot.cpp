#include "Shot.h"

Shot::Shot(DirectX::XMFLOAT3 pPos, DirectX::XMFLOAT3 ePos)
{
	DirectX::XMStoreFloat3(&pVec,
		DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&pPos),
			DirectX::XMLoadFloat3(&ePos)));

	DirectX::XMFLOAT3 temp;
	float speed = SPPED_ARROW;
	DirectX::XMStoreFloat3(&temp,
		DirectX::XMVectorSubtract(
			DirectX::XMLoadFloat3(&pVec),
			DirectX::XMLoadFloat(&speed)));

	modelData.SetSpeed(temp);
}

void Shot::Update()
{
	DirectX::XMFLOAT3 temp;
	DirectX::XMStoreFloat3(&temp,
		DirectX::XMVectorAdd(
			DirectX::XMLoadFloat3(&modelData.GetPos()),
			DirectX::XMLoadFloat3(&modelData.GetSpeed())));
	modelData.SetPos(temp);

}

void Shot::Draw()
{


}
