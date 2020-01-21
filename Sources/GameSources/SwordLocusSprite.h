#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

#include <windows.h>
#include <tchar.h>
#include <sstream>
#include <memory>

#include <cassert>

#include <d3d11.h>
#include <wrl.h>

#include "misc.h"
#include "HighResolutionTimer.h"


class SwordLocusSprite
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texcoord;
	};

	struct Cbuffer
	{
		DirectX::XMFLOAT4X4 view_projection; 
		DirectX::XMFLOAT4 material_color; //材質色
		DirectX::XMFLOAT4 light_direction; //ライト進行方向
	};

	struct MeshInfo
	{
		DirectX::XMFLOAT3 dPos;
		DirectX::XMFLOAT3 uPos;
	};

public:
	Microsoft::WRL::ComPtr <ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr <ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr <ID3D11InputLayout> inputLayout;
	Microsoft::WRL::ComPtr <ID3D11Buffer> vertexBuffer; //（頂点バッファ）
	Microsoft::WRL::ComPtr <ID3D11Buffer> indexBuffer; //（インデックスバッファ）
	Microsoft::WRL::ComPtr <ID3D11Buffer> constantBuffer; //（定数バッファ）
	Microsoft::WRL::ComPtr <ID3D11RasterizerState> solidRasterizerState; //（塗りつぶし描画）
	Microsoft::WRL::ComPtr <ID3D11DepthStencilState> depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11SamplerState>		samplerState;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;

	D3D11_TEXTURE2D_DESC texture2dDesc;

	int numIndex;

	MeshInfo meshInfo[9 * 11 + 1];

public:
	SwordLocusSprite(ID3D11Device* device, const wchar_t* fileName);
	~SwordLocusSprite() {}

	void Render(
		ID3D11DeviceContext*, //デバイスコンテキスト
		const DirectX::XMMATRIX& view,
		const DirectX::XMMATRIX& projection,
		const DirectX::XMFLOAT4& lightDirection,
		const DirectX::XMFLOAT4& color,
		float elapsedTime
	);

	void CreateMesh(ID3D11Device* device, DirectX::XMFLOAT4 tex);

private:
	void CreateBuffer(ID3D11Device* device, Vertex* v, unsigned int* i, int numV, int numI);
};