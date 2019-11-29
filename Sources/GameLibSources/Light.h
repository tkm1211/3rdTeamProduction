#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>


class Light
{
public:
	static const int POINTMAX = 32;
	static const int SPOTMAX = 32;

	struct POINTLIGHT
	{
		float index;
		float range;
		float type;
		float dumy;
		DirectX::XMFLOAT4 pos;
		DirectX::XMFLOAT4 color;
	};
	struct SPOTLIGHT {
		float index;
		float range;//���̓͂��͈�
		float type; //�L����������
		float inner_corn;
		float outer_corn;
		float dumy0;
		float dumy1;
		float dumy2;
		DirectX::XMFLOAT4 pos;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT4 dir;
	};

	struct CBufferLight
	{
		DirectX::XMFLOAT4 lightColor;	//���C�g�̐F
		DirectX::XMFLOAT4 lightDir;		//���C�g�̕���
		DirectX::XMFLOAT4 ambientColor; //����
		DirectX::XMFLOAT4 eyePos;		//�J�������W
		POINTLIGHT pointLight[POINTMAX];
		SPOTLIGHT spotLight[SPOTMAX];
	};

public:
	 Light() {}
	~Light() {}

	static Light* GetInstance()
	{
		static Light instance;
		return &instance;
	}

public:
	Microsoft::WRL::ComPtr <ID3D11Buffer>	constantBufferLight;

	float lightAngle = 4.16f;
	float posY = -0.36f;

	DirectX::XMFLOAT4 lightDir = DirectX::XMFLOAT4(1, 1, 1, 1);
	DirectX::XMFLOAT4 lightColor = DirectX::XMFLOAT4(1, 1, 1, 1);
	DirectX::XMFLOAT4 ambient = DirectX::XMFLOAT4(1, 1, 1, 1);
	POINTLIGHT pointLight[POINTMAX];
	SPOTLIGHT spotLight[SPOTMAX];

	void Init();
	void Update();
	void ImGui();

	void SetDirLight(DirectX::XMFLOAT4 dir, DirectX::XMFLOAT3 color);
	void SetAmbient(DirectX::XMFLOAT3 amb);
	void SetPointLight(int index, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, float range);
	void SetSpotLight(int index, DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 color, DirectX::XMFLOAT3 dir, float range, float near, float far);
};