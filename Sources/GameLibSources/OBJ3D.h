#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>


class OBJ3D
{
protected:
	DirectX::XMFLOAT3 pos;    // 中心座標
	DirectX::XMFLOAT3 speed;  // 速度
	DirectX::XMFLOAT3 scale;  // 中心座標からの半径
	DirectX::XMFLOAT3 angle;  // オイラー角
	DirectX::XMFLOAT4 color;  // 色
	DirectX::XMFLOAT3 adjust; // 描画位置補正
	bool exists;			  // 存在フラグ

public:
	OBJ3D() :
		pos( 0.0f, 0.0f, 0.0f ),
		speed( 0.0f, 0.0f, 0.0f ),
		scale( 1.0f, 1.0f, 1.0f ),
		angle( 0.0f, 0.0f, 0.0f ),
		color( 1.0f, 1.0f, 1.0f, 1.0f ),
		adjust( 0.0f, 0.0f, 0.0f ),
		exists( false )
	{}
	~OBJ3D() {}

public:
	void Init()
	{
		pos    = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
		speed  = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
		scale  = DirectX::XMFLOAT3( 1.0f, 1.0f, 1.0f );
		angle  = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
		adjust = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
		color  = DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
		exists = false;
	}
	void UnInit()
	{
		pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		speed = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
		angle = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		adjust = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		exists = false;
	}

public: // Get関数
	DirectX::XMFLOAT3 GetPos()    { return pos;		}
	DirectX::XMFLOAT3 GetSpeed()  { return speed;	}
	DirectX::XMFLOAT3 GetScale()  { return scale;	}
	DirectX::XMFLOAT3 GetAngle()  { return angle;	}
	DirectX::XMFLOAT4 GetColor()  { return color;	}
	DirectX::XMFLOAT3 GetAdjust() { return adjust;	}
	bool GetExists()			  { return exists;	}

	// ワールド変換行列の取得関数
	DirectX::XMMATRIX GetWorldMatrix();

public: // Set関数
	void SetPos( DirectX::XMFLOAT3 _pos )		{ pos = _pos;		 }
	void SetPosX( float _posX )					{ pos.x = _posX;	 }
	void SetPosY( float _posY )					{ pos.y = _posY;	 }
	void SetPosZ( float _posZ )					{ pos.z = _posZ;	 }
	void SetSpeed( DirectX::XMFLOAT3 _speed )	{ speed = _speed;	 }
	void SetScale( DirectX::XMFLOAT3 _scale )	{ scale = _scale;	 }
	void SetAngle( DirectX::XMFLOAT3 _angle )	{ angle = _angle;	 }
	void SetAngleY( float _angleY )				{ angle.y = _angleY; }
	void SetColor( DirectX::XMFLOAT4 _color )	{ color = _color;	 }
	void SetAdjust( DirectX::XMFLOAT3 _adjust ) { adjust = _adjust;  }
	void SetExists( bool _exists )				{ exists = _exists;  }
	void SetAllData
	(
		DirectX::XMFLOAT3 _pos,
		DirectX::XMFLOAT3 _speed,
		DirectX::XMFLOAT3 _scale,
		DirectX::XMFLOAT3 _angle,
		DirectX::XMFLOAT4 _color,
		DirectX::XMFLOAT3 _adjust,
		bool _exists
	)
	{
		pos = _pos;
		speed = _speed;
		scale = _scale;
		angle = _angle;
		color = _color;
		adjust = _adjust;
		exists = _exists;
	}
};