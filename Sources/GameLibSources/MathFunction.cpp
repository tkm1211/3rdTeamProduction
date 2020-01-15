#include "MathFunction.h"


DirectX::XMMATRIX ExtractOffset(const DirectX::XMMATRIX& mWorld)
{
	return DirectX::XMMatrixTranslation(mWorld.r[3].m128_f32[0], mWorld.r[3].m128_f32[1], mWorld.r[3].m128_f32[2]);
}
DirectX::XMMATRIX ExtractScaling(const DirectX::XMMATRIX& mWorld)
{
	return DirectX::XMMatrixScaling
	(
		DirectX::XMVector3Length(DirectX::XMVECTOR{ mWorld.r[0].m128_f32[0],mWorld.r[0].m128_f32[1],mWorld.r[0].m128_f32[2] }).m128_f32[0],
		DirectX::XMVector3Length(DirectX::XMVECTOR{ mWorld.r[1].m128_f32[0],mWorld.r[1].m128_f32[1],mWorld.r[1].m128_f32[2] }).m128_f32[0],
		DirectX::XMVector3Length(DirectX::XMVECTOR{ mWorld.r[2].m128_f32[0],mWorld.r[2].m128_f32[1],mWorld.r[2].m128_f32[2] }).m128_f32[0]
	);
}
// ���[���h�s�񂩂��]�����݂̂𒊏o����
DirectX::XMMATRIX ExtractRotation(const DirectX::XMMATRIX& mWorld)
{
	DirectX::XMMATRIX mOffset = ExtractOffset(mWorld);
	DirectX::XMMATRIX mScaling = ExtractScaling(mWorld);

	DirectX::XMVECTOR det;
	// ������Scaling�A�E����Offset�̋t�s������ꂼ�ꂩ����B
	return DirectX::XMMatrixInverse(&det, mScaling) * mWorld * XMMatrixInverse(&det, mOffset);
}


// �X�N���[�����W�����[���h���W�ɕϊ�
DirectX::XMFLOAT3* CalcScreenToWorld
(DirectX::XMFLOAT3* pout,
	int screenX,				// �X�N���[��X���W
	int screenY,				// �X�N���[��Y���W
	float fZ,					// �ˉe��Ԃł�Z�l�i0�`1�j
	int screenW,
	int screenH,
	DirectX::XMMATRIX* view,
	DirectX::XMMATRIX* prj)
{
	// �e�s��̋t�s����Z�o
	DirectX::XMMATRIX invView, invPrj, vp, invViewPort;
	DirectX::XMFLOAT4X4 vpFloat4x4;

	invView = DirectX::XMMatrixInverse(NULL, *view);
	invPrj = DirectX::XMMatrixInverse(NULL, *prj);

	vp = DirectX::XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&vpFloat4x4, vp);
	vpFloat4x4._11 = screenW / 2.0f; vpFloat4x4._22 = -screenH / 2.0f;
	vpFloat4x4._41 = screenW / 2.0f; vpFloat4x4._42 = screenH / 2.0f;
	vp = DirectX::XMLoadFloat4x4(&vpFloat4x4);
	invViewPort = DirectX::XMMatrixInverse(NULL, vp);

	// �t�ϊ�
	DirectX::XMMATRIX tmp = invViewPort * invPrj * invView;
	DirectX::XMStoreFloat3(pout, DirectX::XMVector3TransformCoord(DirectX::XMVectorSet(screenX, screenY, fZ, 1.0f), tmp));

	return pout;
}