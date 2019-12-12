#pragma once
#include "Sprite.h"

#include <memory>


class WaveTex
{
private:
	static const int MAX_IN_TIMER = 30;
	static const int MAX_STOP_TIMER = 60;
	static const int MAX_OUT_TIMER = 30;

	enum State
	{
		MOVE_IN,
		STOP,
		MOVE_OUT,
		END
	};
	State status;
	bool move;
	int timer;

	std::unique_ptr<Sprite> wave;
	std::unique_ptr<Sprite> num;
	DirectX::XMFLOAT2 wavePos;
	DirectX::XMFLOAT2 waveNumPos;
	int no[2];

public:
	void Init();
	void Update();
	void Draw();
	void Start(int waveNum);
};