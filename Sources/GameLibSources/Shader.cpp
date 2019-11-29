#include "Shader.h"
#include "FrameWork.h"
#include "ResourceManager.h"


void Shader::LoadCSO( ID3D11Device* device, const char* csoNameOfVertexShader, const char* csoNameOfPixelShader, D3D11_INPUT_ELEMENT_DESC* inputElementDesc, UINT numElements )
{
	ResourceManager::CreateVertexShaderAndInputLayout( device, csoNameOfVertexShader, vertexShader.GetAddressOf(), inputLayout.GetAddressOf(), inputElementDesc, numElements );
	ResourceManager::CreatePixelShader( device, csoNameOfPixelShader, pixelShader.GetAddressOf() );
}

void ShaderSystem::Init()
{
	Microsoft::WRL::ComPtr<ID3D11Device> device = FrameWork::GetInstance().GetDevice();

	// Load Shader Of SkinnedMesh
	{
		D3D11_INPUT_ELEMENT_DESC ieDescOfSkinnedMesh[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "WEIGHTS" , 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BONES"   , 0, DXGI_FORMAT_R32G32B32A32_UINT , 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		shaderOfSkinnedMesh[ShaderOfSkinnedMesh::DEFAULT].LoadCSO( device.Get(), "Data/Shader/SkinnedMeshVS.cso",			"Data/Shader/SkinnedMeshPS.cso",		  ieDescOfSkinnedMesh, ARRAYSIZE( ieDescOfSkinnedMesh ) );
		shaderOfSkinnedMesh[ShaderOfSkinnedMesh::PHONE].LoadCSO(   device.Get(), "Data/Shader/PhoneSkinnedMeshVS.cso",		"Data/Shader/PhoneSkinnedMeshPS.cso",	  ieDescOfSkinnedMesh, ARRAYSIZE( ieDescOfSkinnedMesh ) );
	}

	// Load ShadowMap Shader
	{
		D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT   ,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"  , 0, DXGI_FORMAT_R32G32B32_FLOAT   ,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT      ,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR"   , 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	
		shadowMapShader.LoadCSO( device.Get(), "Data/Shader/ShadowMapVS.cso", "Data/Shader/ShadowMapPS.cso", inputElementDesc, ARRAYSIZE( inputElementDesc ) );
	}
}