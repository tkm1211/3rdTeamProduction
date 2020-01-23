#include <FrameWork.h>

#include "ScenePause.h"
#include "SceneManager.h"
#include "Blender.h"
#include "InputDevice.h"


void ScenePause::Init()
{
	bg = std::make_unique<Sprite>(L"Data/Assets/Texture/scene_bg.png");
	ui = std::make_unique<Sprite>(L"Data/Assets/Texture/text.png");

	returnGame.pos    = DirectX::XMFLOAT2(1920.0f / 2.0f, 272.0f);
	returnGame.texPos = DirectX::XMFLOAT2(0.0f, 110.0f);
	returnGame.size   = DirectX::XMFLOAT2(735.0f, 110.0f);

	restart.pos    = DirectX::XMFLOAT2(1920.0f / 2.0f, returnGame.pos.y + 220.0f);
	restart.texPos = DirectX::XMFLOAT2(0.0f, 220.0f);
	restart.size   = DirectX::XMFLOAT2(735.0f, 110.0f);

	returnTitle.pos    = DirectX::XMFLOAT2(1920.0f / 2.0f, restart.pos.y + 220.0f);
	returnTitle.texPos = DirectX::XMFLOAT2(0.0f, 330.0f);
	returnTitle.size   = DirectX::XMFLOAT2(735.0f, 110.0f);

	state = ScenePause::RETURN_GAME;
	cnt = 0;

	size[0] = 0.0f;
	size[1] = 0.0f;
	size[2] = 0.0f;

	keyCnt[0] = 0;
	keyCnt[1] = 0;
}

void ScenePause::Update()
{
	// �|�[�Y����
	{
		// �����
		if (xInput[0].bUPt)
		{
			if (state != ScenePause::RETURN_GAME)
			{
				cnt = 0;
				state--;
			}
		}
		else if (xInput[0].sLY < 0 || GetKeyState(VK_UP) < 0)
		{
			if (keyCnt[0] == 0)
			{
				if (state != ScenePause::RETURN_GAME)
				{
					cnt = 0;
					state--;
				}
			}
			keyCnt[0]++;
		}
		else
		{
			keyCnt[0] = 0;
		}

		// ������
		if (xInput[0].bDOWNt)
		{
			if (state != ScenePause::RETURN_TITLE)
			{
				cnt = 0;
				state++;
			}
		}
		else if (0 < xInput[0].sLY || GetKeyState(VK_DOWN) < 0)
		{
			if (keyCnt[1] == 0)
			{
				if (state != ScenePause::RETURN_TITLE)
				{
					cnt = 0;
					state++;
				}
			}
			keyCnt[1]++;
		}
		else
		{
			keyCnt[1] = 0;
		}

		// ABXY�{�^��
		if (xInput[0].bAt || xInput[0].bBt || xInput[0].bXt || xInput[0].bYt || GetKeyState(VK_RETURN) < 0)
		{
			switch (state)
			{
			case ScenePause::RETURN_GAME:
				SceneManager::GetInstance()->ReSetStackScene();
				break;

			case ScenePause::RESTART:
				Fade::GetInstance()->onFadeFlg = true;
				Fade::GetInstance()->SetNextScene(new SceneGame());
				break;

			case ScenePause::RETURN_TITLE:
				Fade::GetInstance()->onFadeFlg = true;
				Fade::GetInstance()->SetNextScene(new SceneTitle());
				break;

			default: break;
			}
		}

		// �T�C�Y�g�k
		switch (state)
		{
		case ScenePause::RETURN_GAME:
			size[0] = (sinf(cnt / 15.0f)) / 4.0f + 1.0f;
			size[1] = 1.0f;
			size[2] = 1.0f;
			break;

		case ScenePause::RESTART:
			size[0] = 1.0f;
			size[1] = (sinf(cnt / 15.0f)) / 4.0f + 1.0f;
			size[2] = 1.0f;
			break;

		case ScenePause::RETURN_TITLE:
			size[0] = 1.0f;
			size[1] = 1.0f;
			size[2] = (sinf(cnt / 15.0f)) / 4.0f + 1.0f;
			break;

		default: break;
		}

		cnt++;
	}
}

void ScenePause::Render()
{
	SetBlenderMode(BM_ALPHA);

	bg->Draw(DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1920.0f, 1080.0f), DirectX::XMFLOAT2(0.0f, 0.0f), DirectX::XMFLOAT2(1920.0f, 1080.0f), 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 0.925f));

	ui->Draw2(returnGame.pos ,  DirectX::XMFLOAT2(returnGame.size.x  * size[0], returnGame.size.y  * size[0]), returnGame.texPos , returnGame.size , 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	ui->Draw2(restart.pos    ,  DirectX::XMFLOAT2(restart.size.x     * size[1], restart.size.y     * size[1]), restart.texPos    , restart.size    , 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	ui->Draw2(returnTitle.pos,  DirectX::XMFLOAT2(returnTitle.size.x * size[2], returnTitle.size.y * size[2]), returnTitle.texPos, returnTitle.size, 0.0f, DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	SetBlenderMode(BM_NONE);
}

void ScenePause::ImGui()
{
	ImGui::Begin("Pause");

	if (ImGui::Button("Return Game"))
	{
		SceneManager::GetInstance()->ReSetStackScene();
	}
	if (ImGui::Button("ReStart"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneGame());
	}
	if (ImGui::Button("Title"))
	{
		Fade::GetInstance()->onFadeFlg = true;
		Fade::GetInstance()->SetNextScene(new SceneTitle());
	}

	ImGui::End();


	/*ImGui::Begin("Par");

	ImGui::DragFloat("pos", &size, 0.1f);

	ImGui::End();*/
}

void ScenePause::UnInit() {}