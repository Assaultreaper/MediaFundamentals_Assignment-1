#pragma once
 
#include "AudioManager.h"

class MediaPlayer
{
public:

	MediaPlayer() = default;
	~MediaPlayer();

	void InitializePlaylist();
	void Shutdown();
	void Play();

private:
	void Terminate();

	inline void PrintInfo() const;

	PlayerUtils::AudioManager* m_AudioManager;
	
	int m_CurrentChannel;
	bool isPlaying = false;
	bool m_running = false;

	float m_Volume = 0.5f;
	void increaseVolume();
	void decreaseVolume();

	float m_Pitch = 1.0f;
	void increasePitch();
	void decreasePitch();

	float m_Pan = 0.0f;
	void PanRight();
	void PanLeft();
};

