#include "SwordLocusSprite.h"
#include "ResourceManager.h"
#include "Texture.h"
#include <map>
#include <vector>

SwordLocusSprite::SwordLocusSprite(ID3D11Device* device, const wchar_t* fileName)
{
	HRESULT hr = S_OK;

	//頂点データの構造を定義
	D3D11_INPUT_ELEMENT_DESC ieDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	//頂点シェーダーオブジェクト作成 && インプットレイアウト作成****************
	ResourceManager::CreateVertexShaderAndInputLayout(device, "Data/Shader/SwordLocusVS.cso", &vertexShader, &inputLayout, ieDesc, ARRAYSIZE(ieDesc));
	//**************************************************************************

	//ピクセルシェーダーオブジェクト作成****************************************
	ResourceManager::CreatePixelShader(device, "Data/Shader/SwordLocusPS.cso", &pixelShader);
	//**************************************************************************

	Texture::LoadTextureFromFile(device, fileName, shaderResourceView.GetAddressOf(), &texture2dDesc);


	//ラスタライザーステートオブジェクト作成************************************

	//ソリッド
	D3D11_RASTERIZER_DESC rasterizer_desc = {}; //memo:「 = {}」で構造体を初期化

	rasterizer_desc.FillMode = D3D11_FILL_SOLID;
	rasterizer_desc.CullMode = D3D11_CULL_NONE;
	rasterizer_desc.FrontCounterClockwise = FALSE;
	rasterizer_desc.DepthClipEnable = TRUE;
	hr = device->CreateRasterizerState(&rasterizer_desc, solidRasterizerState.GetAddressOf());
	assert(!hr && "Errer device->CreateRasterizerState");
	//**************************************************************************

	//深度ステンシル ステート オブジェクト**************************************
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = FALSE;
	hr = device->CreateDepthStencilState(&depthStencilDesc, depthStencilState.GetAddressOf());
	assert(!hr && "Errer device->CreateDepthStencilState");
	//**************************************************************************


	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = device->CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
	assert(!hr && "CreateSamplerState	Error");


}

void SwordLocusSprite::Render
(
	ID3D11DeviceContext* deviceContext, //デバイスコンテキスト
	const DirectX::XMMATRIX& view,
	const DirectX::XMMATRIX& projection,
	const DirectX::XMFLOAT4& lightDirection,
	const DirectX::XMFLOAT4& color,
	float elapsedTime)
	{
	//定数バッファのバインド
	//定数バッファの作成
	Cbuffer cb;
	DirectX::XMStoreFloat4x4(&cb.view_projection,  view * projection);
	cb.material_color = color;
	cb.light_direction = lightDirection;


	deviceContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cb, 0, 0);
	deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

	//頂点バッファのバインド
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	//インデックスバッファのバインド
	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	//プリミティブモードの設定
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//入力レイアウトのバインド
	deviceContext->IASetInputLayout(inputLayout.Get());

	//	ラスタライザーの設定
	deviceContext->RSSetState(solidRasterizerState.Get());

	//シェーダー(2種)の設定
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

	deviceContext->PSSetShaderResources(0, 1, shaderResourceView.GetAddressOf());
	deviceContext->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	//深度テストの設定
	deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 0);

	//プリミティブの描画(index付き)
	deviceContext->DrawIndexed(numIndex, 0, 0);
}

void SwordLocusSprite::CreateBuffer(ID3D11Device* device, Vertex* vertices, unsigned int* indices, int numV, int numI)
{
	HRESULT hr = S_OK;

	//頂点バッファーオブジェクト作成(頂点データをDirect3Dのパイプラインに流し込む為のバッファー作成)
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(Vertex) * numV;//バッファーのサイズを指定(頂点数に応じて４の数を変える)
	bd.Usage = D3D11_USAGE_IMMUTABLE;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;//頂点バッファーとしてバインドする為 D3D11_BIND_VERTEX_BUFFERを指定
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices;//リソースデータのポインタを指定
	InitData.SysMemPitch = 0; //その他の項目はテクスチャデータの場合にだけ使うものなので「0」を指定
	InitData.SysMemSlicePitch = 0; //その他の項目はテクスチャデータの場合にだけ使うものなので「0」を指定

	hr = device->CreateBuffer(&bd, &InitData, vertexBuffer.GetAddressOf());
	assert(!hr && "Errer device->CreateBuffer");

	//インデックスバッファオブジェクト作成
	if (indices)
	{
		ZeroMemory(&bd, sizeof(bd));
		bd.ByteWidth = sizeof(unsigned int) * numI;
		bd.Usage = D3D11_USAGE_IMMUTABLE;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		bd.StructureByteStride = 0;

		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = indices;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		hr = device->CreateBuffer(&bd, &InitData, indexBuffer.GetAddressOf());
		assert(!hr && "Errer device->CreateBuffer");

		numIndex = numI;
	}
	//定数バッファオブジェクト作成
	ZeroMemory(&bd, sizeof(bd));

	bd.ByteWidth = sizeof(Cbuffer);
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	hr = device->CreateBuffer(&bd, nullptr, constantBuffer.GetAddressOf());
	assert(!hr && "Errer device->CreateBuffer");
}


void SwordLocusSprite::CreateMesh(ID3D11Device* device, DirectX::XMFLOAT4 tex)
{
	Vertex vertices[4 * 9 * 11 - 4] = {}; // 4頂点 * 10面
	unsigned int indices[3 * 2 * 9 * 11 - 6] = {};//　3頂点 * 2枚 * 10面 （三角形ポリゴン）

	int numV = 0, numI = 0;
	float otex = tex.x / texture2dDesc.Width;
	float ntex = tex.x / texture2dDesc.Width;
	for (int i = 1; i < 99; i++)
	{
		vertices[numV + 0].pos = meshInfo[i].dPos;
		vertices[numV + 1].pos = meshInfo[i].uPos;
		vertices[numV + 2].pos = meshInfo[i - 1].dPos;
		vertices[numV + 3].pos = meshInfo[i - 1].uPos;
		vertices[numV + 0].texcoord = {ntex, 1.0f};
		vertices[numV + 1].texcoord = {ntex, 0.0f};
		vertices[numV + 2].texcoord = {otex, 1.0f};
		vertices[numV + 3].texcoord = {otex, 0.0f};
		vertices[numV + 0].normal = vertices[numV + 1].normal =
			vertices[numV + 2].normal = vertices[numV + 3].normal = DirectX::XMFLOAT3(+0.0f, +1.0f, +0.0f);
		indices[numI + 0] = numV + 0;	indices[numI + 1] = numV + 1;	indices[numI + 2] = numV + 2;
		indices[numI + 3] = numV + 1;	indices[numI + 4] = numV + 3;	indices[numI + 5] = numV + 2;
		numV += 4;	numI += 6;
		otex += ( tex.z / texture2dDesc.Width) / (9.0f * 11.0f);
		ntex += ( tex.z / texture2dDesc.Width) / (9.0f * 11.0f);
	}

	//バッファー作成
	CreateBuffer(device, vertices, indices, numV, numI);

}