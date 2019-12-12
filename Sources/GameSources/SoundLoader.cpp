#include"SoundLoader.h"
//	CreateSoundBuffer(&TitleBGM, "Data/Sounds/title.wav");
//�{�����[�� DSBVOLUME_MAX ~ DSBVOLUME_MIN

//***************************************************************************************************
//
//�T�E���h�ǂݍ���
//
//***************************************************************************************************
void SoundLoader::load()
{
	gameBgm             = std::make_unique<CXAudio2>(L"Data/Sound/game.wav", 1);
	titleBgm            = std::make_unique<CXAudio2>(L"Data/Sound/title.wav", 1);
	playerStepSe        = std::make_unique<CXAudio2>(L"Data/Sound/move.wav", 0);
	magicCreateSe       = std::make_unique<CXAudio2>(L"Data/Sound/SE/Magic_start.wav", 0);
	magicDestroySe      = std::make_unique<CXAudio2>(L"Data/Sound/SE/Magic_End.wav", 0);
	playerAttackSwingSe = std::make_unique<CXAudio2>(L"Data/Sound/SE/Swing.wav", 0);
	playerAttackHitSe     = std::make_unique<CXAudio2>(L"Data/Sound/SE/sword-hit.wav", 0);
	crystalBreakSe = std::make_unique<CXAudio2>(L"Data/Sound/SE/ChainLock.wav", 0);
}


//***************************************************************************************************
//
//�X�V
//
//***************************************************************************************************
void SoundLoader::Update()
{
	gameBgm->Update();
	titleBgm->Update();
	playerStepSe->Update();
	magicCreateSe->Update();
	magicDestroySe->Update();
	playerAttackSwingSe->Update();
	crystalBreakSe->Update();
	playerAttackHitSe->Update();
}

//***************************************************************************************************
//
//�T�E���h���
//
//***************************************************************************************************
void SoundLoader::Release()
{
	gameBgm->Relese();
	titleBgm->Relese();
	playerStepSe->Relese();
	magicCreateSe->Relese();
	magicDestroySe->Relese();
	crystalBreakSe->Relese();
	playerAttackSwingSe->Relese();
	playerAttackHitSe->Relese();
}

void SoundLoader::ImGui()
{

}

void AllSoundStop()
{
	StopSoundMem(SoundLoader::GetInstance()->playerStepSe.get());
	StopSoundMem(SoundLoader::GetInstance()->magicCreateSe.get());
	StopSoundMem(SoundLoader::GetInstance()->magicDestroySe.get());
	StopSoundMem(SoundLoader::GetInstance()->crystalBreakSe.get());
	StopSoundMem(SoundLoader::GetInstance()->playerAttackSwingSe.get());
	StopSoundMem(SoundLoader::GetInstance()->playerAttackHitSe.get());
}

void AllBgmSoundStop()
{
	StopSoundMem(SoundLoader::GetInstance()->titleBgm.get());
	StopSoundMem(SoundLoader::GetInstance()->gameBgm.get());
}


//***************************************************************************************************
//�T�E���h�Đ�
//***************************************************************************************************
void PlaySoundMem(CXAudio2* sound_name)
{
	sound_name->PlayWAV();
}

//***************************************************************************************************
//�T�E���h��~
//***************************************************************************************************
void StopSoundMem(CXAudio2* sound_name)
{
	if (!sound_name) return;
	sound_name->StopWAV();
}

//***************************************************************************************************
//�T�E���h��~
//***************************************************************************************************

void SetVolume(CXAudio2* sound_name, float volume)
{
	sound_name->Volume(volume);
}



