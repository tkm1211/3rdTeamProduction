

#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <imgui_internal.h>

#include "Collision.h"

class Editer
{
public:

	Editer();
	~Editer() {};

	void Update();
	void Imgui();

	const bool GetNowEditer() const { return nowEditer; };

	void SetNowEditer(bool hNowEditer) { nowEditer = hNowEditer; };

	static Editer* GetInstance()
	{
		static Editer instance;
		return &instance;
	}

private:
	bool nowTarget;
	bool nowCatch;
	bool isClone;
	bool nowEditer;
	int cWavenum;
	int catchIndex;
	float distance;
	float objectLar;
	DirectX::XMFLOAT2 oldCursor;
	DirectX::XMFLOAT2 newCursor;
	DirectX::XMFLOAT3 screenWorld;
	DirectX::XMFLOAT3 screenWorld2;
	DirectX::XMFLOAT3 target;
	DirectX::XMFLOAT4 tmpEpos;
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	D3D11_VIEWPORT viewport;
};

