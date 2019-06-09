#include "Sound.h"
#include"DirectSound.h"


Sound* Sound::instance_ = nullptr;


Sound::Sound()
{
}


Sound::~Sound()
{

	loadedSound_.clear();
}


void Sound::initialize(HWND windowsHandler)
{
	DirectSound::initializeDirectSoundClass(windowsHandler);
	instance_ = new Sound();
}


void Sound::play(string soundLink, bool repeat /*= false*/, bool playFromStart /*= true*/)
{
	try
	{
		/*if (playFromStart)
		loadedSound_.at(soundLink)->stop();*/
		//	stop(soundLink);

		loadedSound_.at(soundLink)->play(repeat);
	}
	catch (exception)
	{
		loadedSound_.insert(SoundPair(soundLink, new DirectSound(soundLink.c_str())));
		loadedSound_.at(soundLink)->play(repeat);
	}
}



Sound* Sound::getInstance()
{
	return instance_;
}




void Sound::stop(string soundLink)
{
	try
	{
		loadedSound_.at(soundLink)->stop();
	}
	catch (exception)
	{

	}
}

void Sound::Stop(int id)
{
}

void Sound::deleteSound(string soundLink)
{
	try
	{
		loadedSound_.at(soundLink)->deleteSound();
		loadedSound_.erase(soundLink);
	}
	catch (exception)
	{

	}
}