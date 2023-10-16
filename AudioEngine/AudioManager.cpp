#include "AudioManager.h"
#include "Utilities.h"
#include <iostream>

PlayerUtils::AudioManager::AudioManager()
{
    // Declaring Initial Values for everything.
    // Ussally do nothing that required code execution.
}

PlayerUtils::AudioManager::~AudioManager()
{
    // Notifying things that this is being destroyed.
}

void PlayerUtils::AudioManager::Initialize()
{
	if (m_Initialized)
	{
		return;
	}

	FMODCheckERROR(FMOD::System_Create(&m_system));

	if (m_system->init(1, FMOD_INIT_NORMAL, nullptr) != FMOD_OK)
	{
		printf("Failed to Initialize FMOD System!\n");
		FMODCheckERROR(m_system->close());
		return;
	}
	printf("AudioManager::Initialize(): Successful!\n");

	for (int i = 0; i < 10; i++)
	{
		m_ChannelList.push_back(new Channel);
	}
	m_Initialized = true;
}

void PlayerUtils::AudioManager::Update()
{
	if (!m_Initialized)
	{
		return;
	}

	FMOD_RESULT result = m_system->update();

	if (result != FMOD_OK)
	{
		FMODCheckERROR(result);
		Destroy();
	}
}

void PlayerUtils::AudioManager::Destroy()
{
	if (!m_Initialized)
	{
		return;
	}

	for (std::pair<const char*, Audio*> pair : m_AudioMap)
	{
		FMODCheckERROR(pair.second->Audio->release());
	}

	m_AudioMap.clear();

	FMODCheckERROR(m_system->close());
	FMODCheckERROR(m_system->release());

	m_Initialized = false;
}

void PlayerUtils::AudioManager::LoadAudioStream(const char* source)
{
	if (!m_Initialized)
	{
		return;
	}

	if (m_AudioMap.find(source) != m_AudioMap.end())
	{
		printf("AudioManager:: LoadAudio() Audio Already Loaded!\n");
		return;
	}

	m_AudioMap.insert(std::pair<const char* ,Audio*>(source, new Audio()));

	FMODCheckERROR(m_system->createStream(source, FMOD_DEFAULT, 0, &m_AudioMap[source]->Audio));

	printf("AudioManager::LoadAudio(%s): Loaded successful!\n", source);
}

void PlayerUtils::AudioManager::LoadAudio(const char* file)
{
	if (!m_Initialized)
	{
		return;
	}

	if (m_AudioMap.find(file) != m_AudioMap.end())
	{
		printf("AudioManager :: Load Audio() Already Loaded!\n");
		return;
	}

	m_AudioMap.insert(std::pair<const char*, Audio*>(file, new Audio()));

	FMODCheckERROR(m_system->createSound(file, FMOD_DEFAULT, 0, &m_AudioMap[file]->Audio));

	printf("AudioManager :: Load Audio (%s): Loaded Successfully\n", file);
}

int PlayerUtils::AudioManager::PlayAudio(const char* AudioName, bool& isPlaying)
{
	if (!m_Initialized)
	{
		printf("Not Initialized!\n");
		return m_NextChannelID;
	}

	std::map<const char*, Audio*>::iterator it = m_AudioMap.find(AudioName);

	if (it == m_AudioMap.end())
	{
		printf("Audio Not Found!\n");
		return m_NextChannelID;
	}

	printf("Audio Found\n");

	int ChannelID = m_NextChannelID;
	m_NextChannelID = (m_NextChannelID + 1) % 10;
	Channel* channel = m_ChannelList[ChannelID];

	if (isPlaying)
	{
		StopAudio(ChannelID, isPlaying);
	}

	FMODCheckERROR(m_system->playSound(it->second->Audio, 0, isPlaying, &channel->fmodChannel));
	isPlaying = !isPlaying;

	return ChannelID;
}

int PlayerUtils::AudioManager::MediaStatus(const int ChannelID, bool& isPlaying)
{
	
	if (isPlaying == true)
	{
		bool playing = GetPlaybackStatus(ChannelID, isPlaying);
		m_ChannelList[ChannelID]->fmodChannel->setPaused(!isPlaying);
	}
	else
	{
		bool playing = GetPlaybackStatus(ChannelID, isPlaying);
		m_ChannelList[ChannelID]->fmodChannel->setPaused(!isPlaying);
	}
	printf("Player Media Status : %s\n", !isPlaying ? "Pause" : "Resume");
	return 0;
}

int PlayerUtils::AudioManager::StopAudio(const int ChannelID, bool& isPlaying)
{
	m_ChannelList[ChannelID]->fmodChannel->stop();
	isPlaying = !isPlaying;
	printf("Player Media Status : Stopped\n");
	return 0;
}

void PlayerUtils::AudioManager::SetChannelVolume(const int ChannelID, float& VolumeValue)
{
	FMODCheckERROR(m_ChannelList[ChannelID]->fmodChannel->setVolume(VolumeValue));
}


void PlayerUtils::AudioManager::SetChannelPitch(const int ChannelID, float& PitchValue)
{
	FMODCheckERROR(m_ChannelList[ChannelID]->fmodChannel->setPitch(PitchValue));
}


void PlayerUtils::AudioManager::SetChannelPan(const int ChannelID, float& PanValue)
{
	FMODCheckERROR(m_ChannelList[ChannelID]->fmodChannel->setPan(PanValue));
}

bool PlayerUtils::AudioManager::GetChannelPlaying(int ChannelID)
{
	bool isPlaying;
	m_ChannelList[ChannelID]->fmodChannel->isPlaying(&isPlaying);
	return isPlaying;
}

bool PlayerUtils::AudioManager::GetPlaybackStatus(const int ChannelID, bool& isPlaying)
{
	bool Playing = m_ChannelList[ChannelID]->fmodChannel->getPaused(&isPlaying);
	return Playing;
}

void PlayerUtils::AudioManager::GetPlaybackPosition(int ChannelID, unsigned int& value)
{
	FMODCheckERROR(m_ChannelList[ChannelID]->fmodChannel->getPosition(&value, FMOD_TIMEUNIT_MS));
}

void PlayerUtils::AudioManager::printinfo() const
{
	size_t size = m_ChannelList.size();

	for (size_t i = 0; i < m_ChannelList.size(); i++)
	{
		// You can fill this in.
	}
}


