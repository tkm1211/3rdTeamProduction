#pragma once
#include "Audio.h"

class SoundLoader
{
private:
	SoundLoader() {}

public:
	std::unique_ptr<CXAudio2> walk;

	std::unique_ptr<CXAudio2> crystalCrash;
	std::unique_ptr<CXAudio2> crystalStart;

	std::unique_ptr<CXAudio2> guardSpark;
	std::unique_ptr<CXAudio2> holdShield;
	std::unique_ptr<CXAudio2> notHoldShield;

	std::unique_ptr<CXAudio2> thunder;
	std::unique_ptr<CXAudio2> lightning;
	std::unique_ptr<CXAudio2> lightningClone;

	std::unique_ptr<CXAudio2> playerDamage;

	std::unique_ptr<CXAudio2> playerAttackHit;
	std::unique_ptr<CXAudio2> playerSwing1;
	std::unique_ptr<CXAudio2> playerSwing2;
	std::unique_ptr<CXAudio2> playerSwing3;


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
