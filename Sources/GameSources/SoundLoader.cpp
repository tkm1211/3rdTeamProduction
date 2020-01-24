#include"SoundLoader.h"
//	CreateSoundBuffer(&TitleBGM, "Data/Sounds/title.wav");
//ボリューム DSBVOLUME_MAX ~ DSBVOLUME_MIN

//***************************************************************************************************
//
//サウンド読み込み
//
//***************************************************************************************************
void SoundLoader::load()
{
	main = std::make_unique<CXAudio2>(L"Data/Sound/BGM/GameMain.wav", 1);
	clear = std::make_unique<CXAudio2>(L"Data/Sound/BGM/GameClear.wav", 0);
	over = std::make_unique<CXAudio2>(L"Data/Sound/BGM/GameOver.wav", 0);
	title   = std::make_unique<CXAudio2>(L"Data/Sound/BGM/Title.wav", 1);

	walk = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Walk/walk.wav", 0);

	crystalCrash = std::make_unique<CXAudio2>(L"Data/Sound/SE/MagicArea/CrystalCrash.wav", 0);
	crystalStart = std::make_unique<CXAudio2>(L"Data/Sound/SE/MagicArea/start.wav", 0);

	guardSpark = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Shield/Guard.wav", 0);
	holdShield = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Shield/Hold_Shield.wav", 0);
	notHoldShield = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Shield/not_Hold_Shield.wav", 0);
	
	thunder = std::make_unique<CXAudio2>(L"Data/Sound/SE/Thunder.wav", 0);
	lightning = std::make_unique<CXAudio2>(L"Data/Sound/SE/Lightning.wav", 0);
	lightningClone = std::make_unique<CXAudio2>(L"Data/Sound/SE/Lightning_clone.wav", 0);

	playerDamage = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Damage/hit.wav", 0);

	playerAttackHit = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Attack/hit.wav", 0);
	playerSwing1 = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Attack/swing1.wav", 0);
	playerSwing2 = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Attack/swing2.wav", 0);
	playerSwing3 = std::make_unique<CXAudio2>(L"Data/Sound/SE/player/Attack/swing3.wav", 0);
}


//***************************************************************************************************
//
//更新
//
//***************************************************************************************************
void SoundLoader::Update()
{
	main->Update();
	clear->Update();
	over->Update();
	title->Update();

	walk->Update();

	crystalCrash->Update();
	crystalStart->Update();

	guardSpark->Update();
	holdShield->Update();
	notHoldShield->Update();

	thunder->Update();
	lightning->Update();
	lightningClone->Update();

	playerDamage->Update();

	playerAttackHit->Update();
	playerSwing1->Update();
	playerSwing2->Update();
	playerSwing3->Update();
}

//***************************************************************************************************
//
//サウンド解放
//
//***************************************************************************************************
void SoundLoader::Release()
{
	main->Relese();
	clear->Relese();
	title->Relese();
	over->Relese();

	walk->Relese();

	crystalCrash->Relese();
	crystalStart->Relese();

	guardSpark->Relese();
	holdShield->Relese();
	notHoldShield->Relese();

	thunder->Relese();
	lightning->Relese();
	lightningClone->Relese();

	playerDamage->Relese();

	playerAttackHit->Relese();
	playerSwing1->Relese();
	playerSwing2->Relese();
	playerSwing3->Relese();
}

void SoundLoader::ImGui()
{

}

void AllSoundStop()
{
	StopSoundMem(SoundLoader::GetInstance()->walk.get());
	StopSoundMem(SoundLoader::GetInstance()->crystalCrash.get());
	StopSoundMem(SoundLoader::GetInstance()->crystalStart.get());
	StopSoundMem(SoundLoader::GetInstance()->guardSpark.get());
	StopSoundMem(SoundLoader::GetInstance()->holdShield.get());
	StopSoundMem(SoundLoader::GetInstance()->notHoldShield.get());
	StopSoundMem(SoundLoader::GetInstance()->thunder.get());
	StopSoundMem(SoundLoader::GetInstance()->lightning.get());
	StopSoundMem(SoundLoader::GetInstance()->lightningClone.get());
	StopSoundMem(SoundLoader::GetInstance()->playerDamage.get());

	StopSoundMem(SoundLoader::GetInstance()->playerAttackHit.get());
	StopSoundMem(SoundLoader::GetInstance()->playerSwing1.get());
	StopSoundMem(SoundLoader::GetInstance()->playerSwing2.get());
	StopSoundMem(SoundLoader::GetInstance()->playerSwing3.get());
}

void AllBgmSoundStop()
{
	StopSoundMem(SoundLoader::GetInstance()->main.get());
	StopSoundMem(SoundLoader::GetInstance()->clear.get());
	StopSoundMem(SoundLoader::GetInstance()->over.get());
	StopSoundMem(SoundLoader::GetInstance()->title.get());
}


//***************************************************************************************************
//サウンド再生
//***************************************************************************************************
void PlaySoundMem(CXAudio2* sound_name)
{
	sound_name->PlayWAV();
}

//***************************************************************************************************
//サウンド停止
//***************************************************************************************************
void StopSoundMem(CXAudio2* sound_name)
{
	if (!sound_name) return;
	sound_name->StopWAV();
}

//***************************************************************************************************
//サウンド停止
//***************************************************************************************************

void SetVolume(CXAudio2* sound_name, float volume)
{
	sound_name->Volume(volume);
}



