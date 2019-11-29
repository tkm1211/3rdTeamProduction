#pragma once

#include <memory>
#include <vector>
#include "Mesh.h"


class Model
{
private:
	std::unique_ptr<Mesh> pMesh;

public: // コンストラクタ・デストラクタ
	Model() {}

	// （ const char* fileName : モデルファイルパス, bool leftHandedCoordinate : true = 左手座標系 false = 右手座標系 ）
	Model
	(
		const char* fileName,
		bool leftHandedCoordinate = true
	);

	~Model() {}

public:
	/*void Init();
	void Release();*/

	void Preparation( Shader shader, bool wireframe = false );
	void Render
	(
		const DirectX::XMMATRIX& world, 
		const DirectX::XMMATRIX& view,
		const DirectX::XMMATRIX& projection,
		const DirectX::XMFLOAT4& lightDirection,
		const DirectX::XMFLOAT4& color,
		float elapsedTime
	);

public: // アニメーション関数
	// 初めからアニメーションを始める関数
	void StartAnimation( u_int _animationNumber, bool _isloopAnimation )
	{
		pMesh->StartAnimation( _animationNumber, _isloopAnimation );
	}

	// PauseAnimation()呼ばれた時のアニメーションフレームからアニメーションを始める関数
	void ReStartAnimation()
	{
		pMesh->ReStartAnimation();
	}

	// (※工事中のため使用しないでください。)アニメーションを一時停止する関数
	void PauseAnimation()
	{
		pMesh->PauseAnimation();
	}

	// 現在のアニメーションフレームを取得する関数
	int GetAnimationFrame()
	{
		return pMesh->GetAnimationFrame();
	}

	DirectX::XMFLOAT4X4 GetBoneTransform( std::string name, DirectX::XMFLOAT3& pos )
	{
		return pMesh->GetBoneTransform( name, pos );
	}
};