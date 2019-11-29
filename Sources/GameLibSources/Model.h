#pragma once

#include <memory>
#include <vector>
#include "Mesh.h"


class Model
{
private:
	std::unique_ptr<Mesh> pMesh;

public: // �R���X�g���N�^�E�f�X�g���N�^
	Model() {}

	// �i const char* fileName : ���f���t�@�C���p�X, bool leftHandedCoordinate : true = ������W�n false = �E����W�n �j
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

public: // �A�j���[�V�����֐�
	// ���߂���A�j���[�V�������n�߂�֐�
	void StartAnimation( u_int _animationNumber, bool _isloopAnimation )
	{
		pMesh->StartAnimation( _animationNumber, _isloopAnimation );
	}

	// PauseAnimation()�Ă΂ꂽ���̃A�j���[�V�����t���[������A�j���[�V�������n�߂�֐�
	void ReStartAnimation()
	{
		pMesh->ReStartAnimation();
	}

	// (���H�����̂��ߎg�p���Ȃ��ł��������B)�A�j���[�V�������ꎞ��~����֐�
	void PauseAnimation()
	{
		pMesh->PauseAnimation();
	}

	// ���݂̃A�j���[�V�����t���[�����擾����֐�
	int GetAnimationFrame()
	{
		return pMesh->GetAnimationFrame();
	}

	DirectX::XMFLOAT4X4 GetBoneTransform( std::string name, DirectX::XMFLOAT3& pos )
	{
		return pMesh->GetBoneTransform( name, pos );
	}
};