#pragma once

#include "DirectSound.h"
#include<Windows.h>
#include <map>

using namespace std;

typedef map<string, DirectSound*> SoundMap;
typedef pair<string, DirectSound*> SoundPair;



class Sound
{
public:
	static void initialize(HWND windowsHandler);


	void play(string soundLink, bool repeat = false, bool playFromStart = true);

	void Stop(int id);

	void stop(string soundLink);

	static Sound* getInstance();

private:
	Sound();
	~Sound();

	//Sound _gameOver;
private:
	static Sound* instance_;
	SoundMap loadedSound_;
};
