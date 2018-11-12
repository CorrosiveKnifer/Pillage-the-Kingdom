#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

//Made by Jack Boyd 14860648


#include <fmod.hpp>
#include <array>
#include <map>
#include <string>

using namespace std;

class Sound;

class SoundManager
{

public:
	SoundManager();
	~SoundManager();

	bool Initialise();
	void CreateSounds();
	void CreateChannels();
	void PlaySound(string string, bool loop);
	void ReleaseSounds();
	void ReleaseChannels();

	void AddSoundToChannel(string sound, string channel);
	void ClearChannel(string channel);
	void SetChannelPause(string channel, bool isPaused);
	//Pause/Play
	//Clear
	//Update
protected:
private:

public:
protected:
private:
	map<string, FMOD::Sound*> m_pSounds;
	map<string, FMOD::Channel*> m_pChannels;

	FMOD::System* m_pSystem;
	FMOD::ChannelGroup* m_pChannelGroupBGM;
	FMOD::ChannelGroup* m_pChannelGroupEffects;
	FMOD::Channel* m_pChannelBGM;
	FMOD::Channel* m_pChannelEffects;
	FMOD_RESULT m_result;
};

#endif // __SOUNDMANAGER_H__