#include "Particle.h"
#include "SceneTitle.h"


void Particle::Init(int _maxSize, int _maxCnt, DirectX::XMFLOAT3 _originPos, bool _loop)
{
	emitting = true;
	loop = _loop;
	cnt = 0;

	maxSize = _maxSize;
	maxCnt = _maxCnt;
	originPos = _originPos;

	if (pos.size() == 0) pos.resize(maxSize);
	if (speed.size() == 0) speed.resize(maxSize);
	if (originSpeed.size() == 0) originSpeed.resize(maxSize);
	if (accel.size() == 0) accel.resize(maxSize);
	if (color.size() == 0) color.resize(maxSize);
	if (exists.size() == 0) exists.resize(maxSize);
	if (cnts.size() == 0) cnts.resize(maxSize);

	for ( DirectX::XMFLOAT3& it : pos )
	{
		it = originPos;
	}
	for ( DirectX::XMFLOAT3& it : speed )
	{
		it = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
	}
	for ( DirectX::XMFLOAT3& it : originSpeed )
	{
		it = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
	}
	for ( DirectX::XMFLOAT3& it : accel )
	{
		it = DirectX::XMFLOAT3( 0.0f, 0.0f, 0.0f );
	}
	for ( DirectX::XMFLOAT4& it : color)
	{
		it = DirectX::XMFLOAT4( 1.0f, 1.0f, 1.0f, 1.0f );
	}
	for ( auto& it : exists )
	{
		if ( loop ) it = false;
		else it = true;
	}
	if ( loop )
	{
		for ( auto& it : cnts )
		{
			it = 0;
		}
	}
}
//
//void Particle::Emit()
//{
//	if (loop)
//	{
//		for (int i = 0; i < maxSize; i++)
//		{
//			if (!exists[i])
//			{
//				exists[i] = true;
//				originSpeed[i] = speed[i];
//				break;
//			}
//		}
//		for (int i = 0; i < maxSize; i++)
//		{
//			if (!exists[i]) continue;
//			if (maxCnt < cnts[i])
//			{
//				cnts[i] = 0;
//				exists[i] = false;
//				pos[i] = originPos;
//				float randSpeedX = static_cast<float>(rand() % flashImGuiData.speed[0]) / 100.0f - (flashImGuiData.speed[0] / 2.0f / 100.0f);
//				float randSpeedY = static_cast<float>(rand() % flashImGuiData.speed[1]) / 100.0f;
//				float randSpeedZ = static_cast<float>(rand() % flashImGuiData.speed[2]) / 100.0f - (flashImGuiData.speed[2] / 2.0f / 100.0f);
//				float randAccelX = static_cast<float>(rand() % flashImGuiData.accel[0]) / 1000.0f - (flashImGuiData.accel[0] / 2.0f / 1000.0f);
//				float randAccelY = static_cast<float>(rand() % flashImGuiData.accel[1]) / 1000.0f - (flashImGuiData.accel[1] / 2.0f / 1000.0f);
//				float randAccelZ = static_cast<float>(rand() % flashImGuiData.accel[2]) / 1000.0f - (flashImGuiData.accel[2] / 2.0f / 1000.0f); 
//				speed[i] = DirectX::XMFLOAT3(randSpeedX, randSpeedY, randSpeedZ);
//				accel[i] = DirectX::XMFLOAT3(randAccelX, -randAccelY, randAccelZ);
//				color[i].w = 1.0f;
//				continue;
//			}
//
//			speed[i].x += accel[i].x;
//			speed[i].y += accel[i].y;
//			speed[i].z += accel[i].z;
//			pos[i].x += speed[i].x;
//			pos[i].y += speed[i].y;
//			pos[i].z += speed[i].z;
//
//			color[i].w = 1.0f - (static_cast<float>(cnts[i]) / static_cast<float>(maxCnt));
//
//			cnts[i]++;
//		}
//	}
//	else if (emitting)
//	{
//		for (int i = 0; i < maxSize; i++)
//		{
//			if (!exists[i])
//			{
//				continue;
//			}
//			if (maxCnt < cnt)
//			{
//				exists[i] = false;
//				continue;
//			}
//
//			speed[i].x += accel[i].x;
//			speed[i].y += accel[i].y;
//			speed[i].z += accel[i].z;
//			pos[i].x += speed[i].x;
//			pos[i].y += speed[i].y;
//			pos[i].z += speed[i].z;
//
//			color[i].w = 1.0f - (static_cast<float>(cnt) / static_cast<float>(maxCnt));
//		}
//
//		if (maxCnt < cnt)
//		{
//			emitting = false;
//			cnt = -1;
//		}
//
//		cnt++;
//	}
//}
