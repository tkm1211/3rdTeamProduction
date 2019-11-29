#pragma once

#include <memory>
#include <vector>

#include "Billboard.h"

struct ParticleImGuiData
{
	int speed[3];
	int accel[3];
	int accelStart[3];
	int accelStage[3];


};

class Particle
{
private:
	DirectX::XMFLOAT3 originPos;				// 放出源の座標
	std::vector<DirectX::XMFLOAT3> pos;			// 粒子ごとの座標（ pos.resize( maxSize )すること ）
	std::vector<DirectX::XMFLOAT3> speed;		// 速度（ speed.resize( maxSize )すること ）
	std::vector<DirectX::XMFLOAT3> originSpeed;	// 初期速度（ originSpeed.resize( maxSize )すること ）
	std::vector<DirectX::XMFLOAT3> accel;		// 加速度（ accel.resize( maxSize )すること ）
	std::vector<DirectX::XMFLOAT4> color;		// 色（ color.resize( maxSize )すること ）
	std::vector<bool> exists;					// 粒子ごとの存在フラグ（ exists.resize( maxSize )すること ）
	std::vector<int> cnts;						// 粒子ごとの(ループ用)カウント（ cnts.resize( maxSize )すること ）
	float scale;								// 中心座標からの半径

	bool emitting;
	bool loop;

private:
	int maxSize; // パーティクルの最大数
	int	cnt;	 // パーティクル更新カウント
	int maxCnt;  // パーティクル更新最大カウント

public:
	Particle() {}
	~Particle() {}

	void Init( int _maxSize, int _maxCnt, DirectX::XMFLOAT3 _originPos, bool _loop = false );
//	void Emit();

public: // Get関数
	DirectX::XMFLOAT3 GetOriginPos()		{ return originPos;		}
	DirectX::XMFLOAT3 GetPos( int _num )	{ return pos[_num];		}
	DirectX::XMFLOAT3 GetSpeed( int _num )	{ return speed[_num];	}
	DirectX::XMFLOAT3 GetAccel( int _num )	{ return accel[_num];	}
	DirectX::XMFLOAT4 GetColor( int _num )	{ return color[_num];	}
	bool GetExists( int _num )				{ return exists[_num];	}
	float GetScale()						{ return scale;			}
	int GetMaxSize()						{ return maxSize;		}
	int GetMaxCnt()							{ return maxCnt;		}

public: // Set関数
	void SetPos( int _num, DirectX::XMFLOAT3 _pos )		{ pos[_num] = _pos;			}
	void SetPosX( int _num, float _posX )				{ pos[_num].x = _posX;		}
	void SetPosY( int _num, float _posY )				{ pos[_num].y = _posY;		}
	void SetPosZ( int _num, float _posZ )				{ pos[_num].z = _posZ;		}
	void SetSpeed(int _num, DirectX::XMFLOAT3 _speed)	{ speed[_num] = _speed;		}
	void SetAccel( int _num, DirectX::XMFLOAT3 _accel )	{ accel[_num] = _accel;		}
	void SetColor( int _num, DirectX::XMFLOAT4 _color )	{ color[_num] = _color;		}
	void SetExists( int _num, bool _exists )			{ exists[_num] = _exists;	}
	void SetScale( float _scale)						{ scale = _scale;			}

};

class FlashParticle : public Particle
{
private:
	ParticleImGuiData imguiData;

public:
	void Set();
	void Emit();
};
