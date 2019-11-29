#include "Model.h"
#include "FrameWork.h"
#include "StaticMesh.h"
#include "SkinnedMesh.h"


Model::Model
 (  const char* fileName,
	bool leftHandedCoordinate )
{

	Microsoft::WRL::ComPtr<ID3D11Device> device = FrameWork::GetInstance().GetDevice();

	char ext[32];
	_splitpath_s( fileName, NULL, NULL, NULL, NULL, NULL, NULL, ext, sizeof( ext ) );

	if ( strcmp( ext, ".obj" ) == 0 || strcmp( ext, ".OBJ" ) == 0 )
	{
		pMesh = std::make_unique<StaticMesh>( device.Get(), fileName, leftHandedCoordinate );
	}
	else if ( strcmp( ext, ".fbx" ) == 0 || strcmp( ext, ".FBX" ) == 0 )
	{
		pMesh = std::make_unique<SkinnedMesh>( device.Get(), fileName, leftHandedCoordinate );
	}

}

void Model::Preparation( Shader shader, bool wireframe )
{

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = FrameWork::GetInstance().GetContext();

	if ( pMesh )
	{
		pMesh->Preparation( immediateContext.Get(), shader, wireframe );
	}

}

void Model::Render
 (  const DirectX::XMMATRIX& world,
	const DirectX::XMMATRIX& view,
	const DirectX::XMMATRIX& projection,
	const DirectX::XMFLOAT4& lightDirection,
	const DirectX::XMFLOAT4& color,
	float elapsedTime )
{

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext = FrameWork::GetInstance().GetContext();

	//	ƒ[ƒ‹ƒh•ÏŠ·s—ñŽæ“¾
	DirectX::XMMATRIX worldM = world;

	//	Matrix -> Float4x4 •ÏŠ·
	DirectX::XMFLOAT4X4 wvp;
	DirectX::XMFLOAT4X4 _world;

	DirectX::XMStoreFloat4x4( &wvp, worldM * view * projection );
	DirectX::XMStoreFloat4x4( &_world, worldM );

	//	•`‰æ
	if ( pMesh )
	{
		pMesh->Render( immediateContext.Get(), wvp, _world, lightDirection, color, elapsedTime );
	}

}