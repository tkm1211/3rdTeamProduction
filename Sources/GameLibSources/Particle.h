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
	DirectX::XMFLOAT3 originPos;				// ���o���̍��W
	std::vector<DirectX::XMFLOAT3> pos;			// ���q���Ƃ̍��W�i pos.resize( maxSize )���邱�� �j
	std::vector<DirectX::XMFLOAT3> speed;		// ���x�i speed.resize( maxSize )���邱�� �j
	std::vector<DirectX::XMFLOAT3> originSpeed;	// �������x�i originSpeed.resize( maxSize )���邱�� �j
	std::vector<DirectX::XMFLOAT3> accel;		// �����x�i accel.resize( maxSize )���邱�� �j
	std::vector<DirectX::XMFLOAT4> color;		// �F�i color.resize( maxSize )���邱�� �j
	std::vector<bool> exists;					// ���q���Ƃ̑��݃t���O�i exists.resize( maxSize )���邱�� �j
	std::vector<int> cnts;						// ���q���Ƃ�(���[�v�p)�J�E���g�i cnts.resize( maxSize )���邱�� �j
	float scale;								// ���S���W����̔��a

	bool emitting;
	bool loop;

private:
	int maxSize; // �p�[�e�B�N���̍ő吔
	int	cnt;	 // �p�[�e�B�N���X�V�J�E���g
	int maxCnt;  // �p�[�e�B�N���X�V�ő�J�E���g

public:
	Particle() {}
	~Particle() {}

	void Init( int _maxSize, int _maxCnt, DirectX::XMFLOAT3 _originPos, bool _loop = false );
//	void Emit();

public: // Get�֐�
	DirectX::XMFLOAT3 GetOriginPos()		{ return originPos;		}
	DirectX::XMFLOAT3 GetPos( int _num )	{ return pos[_num];		}
	DirectX::XMFLOAT3 GetSpeed( int _num )	{ return speed[_num];	}
	DirectX::XMFLOAT3 GetAccel( int _num )	{ return accel[_num];	}
	DirectX::XMFLOAT4 GetColor( int _num )	{ return color[_num];	}
	bool GetExists( int _num )				{ return exists[_num];	}
	float GetScale()						{ return scale;			}
	int GetMaxSize()						{ return maxSize;		}
	int GetMaxCnt()							{ return maxCnt;		}

public: // Set�֐�
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
