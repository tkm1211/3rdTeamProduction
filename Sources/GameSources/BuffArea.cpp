#include "BuffArea.h"
#include "easing.h"
#include "Camera.h"
#include "FrameWork.h"
#include "Blender.h"


void BuffArea::Init()
{
	//���f���̃��[�h
	pArea = std::make_unique<Model>("Data/Assets/Model/val/auraeffect.fbx", false);
}

void BuffArea::UnInit()
{
}

void BuffArea::Update()
{
	float s = 0;	//�X�P�[����u���p
	for (auto &ba : buffArea)
	{
		if (!ba.isExist) continue;
		switch (ba.state)
		{
		case 0: //�o��
			s = easing::OutQuint(static_cast<float>(ba.timer), 30.0f, ba.radius, 0.0f); //�C�ӂ̑傫���܂ő傫������
			ba.modelData.SetScale({s, s ,s});
			ba.timer++;
			if (ba.timer > 30) ba.state++;
			break;
		case 1:	 //�X�V
			if (ba.stopFlg) break;	//��break

			s = ba.subRadius;
			ba.modelData.SetScale({ ba.modelData.GetScale().x - s, ba.modelData.GetScale().y - s ,ba.modelData.GetScale().z - s }); //�k�ޏ���
			if (ba.modelData.GetScale().x <= 0) //�傫�����O�ȉ��Ȃ瑶�݂�����
			{
				ba.isExist = false;
				BreakBuffArea();
			}
			break;
		}

		//�펞��]������
		ba.modelData.SetAngleY(ba.modelData.GetAngle().y + ba.addRota);
		ba.modelData.SetPos(ba.pos);
	}

}

void BuffArea::Draw()
{
	pArea->Preparation(ShaderSystem::GetInstance()->GetShaderOfSkinnedMesh(ShaderSystem::DEFAULT), false);
	
	SetBlenderMode(BM_ADD);
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		pArea->Render(ba.modelData.GetWorldMatrix(), camera.GetViewMatrix(), camera.GetProjectionMatrix(),
			DirectX::XMFLOAT4(0.0f, -1.0f, 1.0f, 0.0f), ba.modelData.GetColor(), FrameWork::GetInstance().GetElapsedTime());
	}
	SetBlenderMode(BM_ALPHA);

}

void BuffArea::SetBuffArea(BuffAreaInfo &b)
{
	//���ꂩ�琶�������ȊO�͓������~�߂�
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.stopFlg = true;
	}

	//����
	for (auto& ba : buffArea)
	{
		if (ba.isExist) continue; //���݃t���O��false������Ȃ炻���𐶐�������
		ba.Init(b);
		return;
	}
	//����ȊO�Ȃ�push back���đ��₷
	buffArea.push_back(b);
}


void BuffArea::SetBuffArea(DirectX::XMFLOAT3 pos, float rad, float subRad)
{
	BuffAreaInfo ba;
	ba.Init(pos, rad, subRad);
	ba.addRota = (rand() % 12 - 6 ) * 0.01745f;
	SetBuffArea(ba);
}

void BuffArea::BreakBuffArea()
{
	for (auto& ba : buffArea)
	{
		if (!ba.isExist) continue;
		ba.isExist = false;
	}
}