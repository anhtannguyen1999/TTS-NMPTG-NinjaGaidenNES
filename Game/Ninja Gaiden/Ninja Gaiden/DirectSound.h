#pragma once
#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL
#define DirectSound_BACKGROUND1 "Sound/stage31.wav"
#define DirectSound_ATTACK_ENEMY "Sound/Attack.wav"
#define DirectSound_OBTAIN_ITEM "Sound/ItemPick.wav"
#define DirectSound_NINJA_JUMP "Sound/Jump.wav"
#define NINJA_ATTACKED "Sound/Attacked.wav"
#define DirectSound_Background2 "Sound/stage32.wav"
#define DirectSound_Background3 "Sound/boss.wav"
#define DirectSound_OBTAIN_HEALTHPOT "Sound/HealthPot.wav"
#define DirectSound_ENEMY_ATTACKED "Sound/EnemyDeath.wav"
#define DIRECTSOUND_NINJA_THROW "Sound/Throw.wav"
#define DIRECTSOUND_ENEMY_COMMANDO "Sound/Commando.wav"
#define DIRECTSOUND_ENEMY_GUNNER "Sound/GunnerShoot.wav"
#define DIRECTSOUND_SUBWEAPON_FIRE "Sound/FireShoot.wav"


#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

#include <sstream>
#include <iostream>
#include <dsound.h>
#include<vector>
#include "WaveFile.h"

//enum DirectSound_ID
//{
//	ID_DirectSound_MAP1,
//	ID_DirectSound_JUMP,
//	ID_DirectSound_COIN,
//	ID_TAIL_TALLWHIP,
//	ID_DirectSound_MUSHROOM_OBTAIN,
//	ID_DirectSound_RACOON_LEFT_OBTAIN,
//	ID_DirectSound_LIFE_UP,
//	ID_DirectSound_MARIO_SLIPING,
//	ID_DirectSound_BEAN_STALK,
//	ID_DirectSound_PIPE_MAZE,
//	ID_DirectSound_SQUISH,
//	ID_DirectSound_MARIO_ATTACK,
//	ID_DirectSound_BLOCK_BREAKING
//};
// -----------------------------------------------
// Name: class TDirectSound
// Desc: used to load/ store/ play an audio with wav extension.
// -----------------------------------------------
class DirectSound
{
public:
	DirectSound(const char* audioPath);
	~DirectSound(void);

	static HRESULT initializeDirectSoundClass(HWND windowsHandler);
	static HRESULT releaseDirectSoundClass();

	HRESULT play(bool isLoop = false, DWORD priority = 0);
	HRESULT stop();


private:
	HRESULT loadAudio(const char* audioPath);

private:
	static WAVEFORMATEX bufferFormat_;
	static DSBUFFERDESC bufferDescription_;
	static LPDIRECTSOUND8 audioHandler_;
	static HWND windowsHandler_;

	LPDIRECTSOUNDBUFFER DirectSoundBuffer_;
};
