#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>


class OBJ3D
{
protected:
	DirectX::XMFLOAT3 pos;    // ���S���W
	DirectX::XMFLOAT3 speed;  // ���x
	DirectX::XMFLOAT3 scale;  // ���S���W����̔��a
	DirectX::XMFLOAT3 angle;  // �I�C���[�p
	DirectX::XMFLOAT4 color;  // �F
	DirectX::XMFLOAT3 adjust; // �`��ʒu�␳
	bool exists;			  // ���݃t���O

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

public: // Get�֐�
	DirectX::XMFLOAT3 GetPos()    { return pos;		}
	DirectX::XMFLOAT3 GetSpeed()  { return speed;	}
	DirectX::XMFLOAT3 GetScale()  { return scale;	}
	DirectX::XMFLOAT3 GetAngle()  { return angle;	}
	DirectX::XMFLOAT4 GetColor()  { return color;	}
	DirectX::XMFLOAT3 GetAdjust() { return adjust;	}
	bool GetExists()			  { return exists;	}

	// ���[���h�ϊ��s��̎擾�֐�
	DirectX::XMMATRIX GetWorldMatrix();

public: // Set�֐�
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