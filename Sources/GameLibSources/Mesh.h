#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>
#include <string>
#include "Shader.h"


class Mesh
{
protected:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>			vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>			pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>			inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				constantBuffer;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		wireframeRasterizerState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>		solidRasterizerState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>		depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11SamplerState>			samplerState;

	// TRUE : right handed , FALSE : left handed
	BOOL handedCoordinateSystem = FALSE;

public:
	Mesh() {}
	virtual ~Mesh() {}

public:
	virtual void Preparation(ID3D11DeviceContext* immediateContext, Shader shader, bool wireframe = false) {}
	//virtual void Render
	//(
	//	ID3D11DeviceContext *immediateContext,
	//	const DirectX::XMFLOAT4X4 &wvp,
	//	const DirectX::XMFLOAT4X4 &world,
	//	const DirectX::XMFLOAT4 &lightDirection,
	//	const DirectX::XMFLOAT4 &materialColor,
	//	float elapsedTime,
	//	bool wireframe = false
	//) {}
	virtual void Render
	(
		ID3D11DeviceContext* immediateContext,
		const DirectX::XMFLOAT4X4& wvp,
		const DirectX::XMFLOAT4X4& world,
		const DirectX::XMFLOAT4& lightDirection,
		const DirectX::XMFLOAT4& materialColor,
		float elapsedTime,
		bool inCamera
	) {}

	//virtual void Release() {}

	virtual void StartAnimation( u_int _animationNumber, bool _isloopAnimation ) {}
	// virtual void StopAnimation() {}
	virtual void ReStartAnimation() {}
	virtual void PauseAnimation() {}
	virtual int GetAnimationFrame() { return 0; }
	virtual DirectX::XMFLOAT4X4 GetBoneTransform( std::string name, DirectX::XMFLOAT3& pos, int vectexPosNo ) { return DirectX::XMFLOAT4X4(); }
	virtual int RayPick
	(
		const DirectX::XMFLOAT3& startPosition,
		const DirectX::XMFLOAT3& endPosition,
		DirectX::XMFLOAT3* outPosition,
		DirectX::XMFLOAT3* outNormal,
		float* outLength
	) { return 0; }

	template <class T>
	void serialize( T &archive )
	{
		return;
	}

protected:
	void Init( ID3D11Device *device, BOOL handedCoordinateSystem );
};