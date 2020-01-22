#include "Operation.h"
#include "Blender.h"

void Operation::Init()
{
	operationSpr = std::make_unique<SpriteBatch>(L"Data/Assets/Texture/text.png", 4);

}

void Operation::Update()
{

}

void Operation::Draw()
{
	SetBlenderMode(BM_ALPHA);
	operationSpr->Begin();
	operationSpr->Draw({ (1920 / 2) + (800 * 0.0f), 1080 - 75 }, { 735.0f * 0.5f, 110.0f * 0.5f }, { 0.0f, 110.0f * 4.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	operationSpr->Draw({ (1920 / 2) + (210 * 1.0f), 1080 - 75 }, { 735.0f * 0.5f, 110.0f * 0.5f }, { 0.0f, 110.0f * 6.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	operationSpr->Draw({ (1920 / 2) + (220 * 2.0f), 1080 - 75 }, { 735.0f * 0.5f, 110.0f * 0.5f }, { 0.0f, 110.0f * 5.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	operationSpr->Draw({ (1920 / 2) + (220 * 3.0f), 1080 - 75 }, { 735.0f * 0.5f, 110.0f * 0.5f }, { 0.0f, 110.0f * 7.0f }, { 735.0f, 110.0f }, 0, { 1, 1, 1, 1 });
	operationSpr->End();
	SetBlenderMode(BM_NONE);
}
