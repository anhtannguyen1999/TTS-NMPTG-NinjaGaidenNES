#include "DirectSound.h"

#if MEMORY_LEAK_DEBUG == 1
#include <vld.h>
#endif

WAVEFORMATEX DirectSound::bufferFormat_;
DSBUFFERDESC DirectSound::bufferDescription_;
LPDIRECTSOUND8 DirectSound::audioHandler_;
HWND DirectSound::windowsHandler_;

// -----------------------------------------------
// Name: T6_DirectSound::T6_DirectSound()
// Desc: Get the audio Name and Path, ready to load.
// -----------------------------------------------
DirectSound::DirectSound(const char* audioPath)
{
	loadAudio(audioPath);
}



DirectSound::~DirectSound(void)
{
	
	DirectSoundBuffer_->Stop();
}


// -----------------------------------------------
// Name: T6_DirectSound::initializeDirectSoundClass()
// Desc: Initialize the basic PROPERTIESs for loading audio
// -----------------------------------------------
HRESULT DirectSound::initializeDirectSoundClass(HWND windowsHandler)
{
	windowsHandler_ = windowsHandler;

	HRESULT result;
	result = DirectSoundCreate8(0, &audioHandler_, 0);
	result = result | audioHandler_->SetCooperativeLevel(windowsHandler_, DSSCL_PRIORITY);

	ZeroMemory(&bufferFormat_, sizeof(WAVEFORMATEX));
	ZeroMemory(&bufferDescription_, sizeof(DSBUFFERDESC));

	bufferFormat_.wFormatTag = AUDIO_FORMAT_TAG;
	bufferFormat_.nChannels = AUDIO_NUM_OF_CHANNEL;
	bufferFormat_.nSamplesPerSec = AUDIO_SAMPLE_SPEED;
	bufferFormat_.wBitsPerSample = AUDIO_BITS_PER_SAMPLE;
	bufferFormat_.nBlockAlign = AUDIO_BLOCK_ALIGN(bufferFormat_.wBitsPerSample,
		bufferFormat_.nChannels);
	bufferFormat_.nAvgBytesPerSec = AUDIO_AVERAGE_BPS(bufferFormat_.nSamplesPerSec,
		bufferFormat_.nBlockAlign);

	bufferDescription_.dwFlags = AUDIO_FLAGS;
	bufferDescription_.guid3DAlgorithm = AUDIO_GUID;
	bufferDescription_.dwSize = sizeof(DSBUFFERDESC);

	return result;
}


// -----------------------------------------------
// Name: T6_DirectSound::releaseDirectSoundClass()
// Desc: Release the basic PROPERTIES after used (close game).
// -----------------------------------------------
HRESULT DirectSound::releaseDirectSoundClass()
{
	if (audioHandler_ != 0)
		return audioHandler_->Release();

	return S_OK;
}


// -----------------------------------------------
// Name: T6_DirectSound::loadAudio()
// Desc: Load the Audio stored in audioPath.
// -----------------------------------------------
wchar_t* convert(const char* str)
{
	int n = strlen(str);
	wchar_t*s = new wchar_t[n + 1];
	for (int i = 0; i < n; i++)
		s[i] = str[i];
	s[n] = 0;
	return s;
}

HRESULT DirectSound::loadAudio(const char* audioPath_)
{
	HRESULT result;
	WaveFile audioObject;
	//size_t wn = mbsrtowcs(NULL, &audioPath_, 0, NULL);

	// error if wn == size_t(-1)

	//wchar_t * buf = new wchar_t[wn + 1]();  // value-initialize to 0 (see below)
	//const char *port = "8080";
	size_t size = strlen(audioPath_) + 1;
	wchar_t* buf = new wchar_t[size];

	size_t outSize;
	mbstowcs_s(&outSize, buf, size, audioPath_, size - 1);

	//wn = mbsrtowcs(buf, &audioPath_, wn + 1, NULL);

	// error if wn == size_t(-1)
	//wchar_t* buf = convert(audioPath_);
	 // successful conversion

						// result now in buf, return e.g. as std::wstring

	result = audioObject.Open(buf, 0, 1);

	if (!FAILED(result)) {

		bufferDescription_.dwBufferBytes = audioObject.GetSize();
		bufferDescription_.lpwfxFormat = audioObject.m_pwfx;

		result = audioHandler_->CreateSoundBuffer(&bufferDescription_, &DirectSoundBuffer_, 0);

		VOID* pointerToLockedBuffer = 0;
		DWORD lockedSize = 0;
		if (DirectSoundBuffer_ != NULL)
		{
			result = result | (DirectSoundBuffer_)->Lock(0, AUDIO_BUFFER_SIZE, &pointerToLockedBuffer,
				&lockedSize, 0, 0, DSBLOCK_ENTIREBUFFER);
		}
		if (!FAILED(result)) {
			DWORD readedData = 0;
			audioObject.ResetFile();
			result = audioObject.Read((BYTE*)pointerToLockedBuffer, lockedSize, &readedData);
			if (!FAILED(result)) {
				(DirectSoundBuffer_)->Unlock(pointerToLockedBuffer, lockedSize, 0, 0);
			}
		}
	}

	audioObject.Close();
	return result;
}


// -----------------------------------------------
// T6_DirectSound::play()
// Desc: Play loaded audio, may choose loop or no.
// -----------------------------------------------
HRESULT DirectSound::play(bool isLoop, DWORD priority)
{
	if (DirectSoundBuffer_ != NULL)
	{
		return DirectSoundBuffer_->Play(0, priority, isLoop & DSBPLAY_LOOPING);
	}
}


// -----------------------------------------------
// T6_DirectSound:stop()
// Desc: Stop the audio if it is playing.
// -----------------------------------------------
HRESULT DirectSound::stop()
{
	HRESULT result = DirectSoundBuffer_->Stop();
	DirectSoundBuffer_->SetCurrentPosition(0);
	return result;
}