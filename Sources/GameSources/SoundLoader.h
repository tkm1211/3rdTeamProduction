#pragma once
#include "Audio.h"

class SoundLoader
{
private:
	SoundLoader() {}

public:
	std::unique_ptr<CXAudio2> gameBgm;
	std::unique_ptr<CXAudio2> titleBgm;
	std::unique_ptr<CXAudio2> playerStepSe;

	std::unique_ptr<CXAudio2> magicCreateSe;
	std::unique_ptr<CXAudio2> magicDestroySe;


public://関数
	void Update();
	void load();
	void Release();
	
	void ImGui();

	static SoundLoader* GetInstance()
	{
		static SoundLoader instance;
		return &instance;
	}

};

void AllSoundStop();
void AllBgmSoundStop();
//***************************************************************************************************
//サウンド再生
//***************************************************************************************************
void PlaySoundMem(CXAudio2* sound_name);
//***************************************************************************************************
//サウンド停止
//***************************************************************************************************
void StopSoundMem(CXAudio2* sound_name);
//***************************************************************************************************
//サウンド停止
//***************************************************************************************************
void SetVolume(CXAudio2* sound_name, float volume);
