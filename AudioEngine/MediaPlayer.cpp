#include "MediaPlayer.h"

MediaPlayer::~MediaPlayer()
{
}

void MediaPlayer::InitializePlaylist()
{
	m_AudioManager = new PlayerUtils::AudioManager;

	m_AudioManager->Initialize();

	printf("Press 1 to Load From Disk.\n");
	printf("Press 2 to Load From Memory.\n");
}

void MediaPlayer::Shutdown()
{
	printf("Media Player Status : Shutting Down\n ");
	m_AudioManager->Destroy();
	delete m_AudioManager;
	printf("Session Terminated\n");
}

void MediaPlayer::Play()
{
	m_running = true;
	int channel = 0;
	unsigned int position = 0;

	while (m_running)
	{
		m_AudioManager->Update();

		switch (int key = _getch())
		{
		case '1':
			m_AudioManager->LoadAudio("audio/awesomeness.wav");
			printf("Media Player Status : Audio Files Loaded From Disk\n");

			m_CurrentChannel = m_AudioManager->PlayAudio("audio/awesomeness.wav", isPlaying);
			break;
		case '2':
			m_AudioManager->LoadAudioStream("audio/awesomeness.wav");
			printf("Media Player Status : Audio File Loaded Memory\n");

			m_CurrentChannel = m_AudioManager->PlayAudio("audio/awesomeness.wav", isPlaying);
			break;
		case 32:
			m_AudioManager->MediaStatus(m_CurrentChannel, isPlaying);
			break;
		case 'x':
			m_AudioManager->StopAudio(m_CurrentChannel, isPlaying);
			break;
		case 72:
			increaseVolume();
			break;
		case 80:
			decreaseVolume();
			break;
		case 77:
			PanRight();
			break;
		case 75:
			PanLeft();
			break;
		case 73:
			increasePitch();
			break;
		case 81:
			decreasePitch();
			break;
		case 27:
			Terminate();
			break;
		}

	}
}

void MediaPlayer::Terminate()
{
	m_running = false;
}

inline void MediaPlayer::PrintInfo() const
{
	m_AudioManager->printinfo();
}

void MediaPlayer::increaseVolume()
{
	m_Volume += 0.1f;
	if (m_Volume > 1.0f)
	{
		m_Volume = 1.0f;
		printf("Audio Source Volume : Maximum Volume\n");
	}
	else
	{
		m_AudioManager->SetChannelVolume(m_CurrentChannel, m_Volume);
		printf("Audio Volume : %f\n", m_Volume);
	}
}

void MediaPlayer::decreaseVolume()
{
	m_Volume -= 0.1f;
	if (m_Volume <  0.0f)
	{
		m_Volume = 0.0f;
		printf("Audio Source Volume : Minimum Volume\n");
	}
	else
	{
		m_AudioManager->SetChannelVolume(m_CurrentChannel, m_Volume);
		printf("Audio Volume : %f\n", m_Volume);
	}
}

void MediaPlayer::increasePitch()
{
	m_Pitch += 0.1f;
	if (m_Pitch > 2.0f)
	{
		m_Pitch = 2.0f;
		printf("Audio Source Pitch : Maximum Pitch\n");
	}
	else
	{
		m_AudioManager->SetChannelPitch(m_CurrentChannel, m_Pitch);
		printf("Audio Pitch : %f\n", m_Pitch);
	}
}

void MediaPlayer::decreasePitch()
{
	m_Pitch -= 0.1f;
	if (m_Pitch < 0.1f)
	{
		m_Pitch = 0.0f;
		printf("Audio Source Pitch : Minimum Pitch\n");
		
	}
	else
	{
		m_AudioManager->SetChannelPitch(m_CurrentChannel, m_Pitch);
		printf("Audio Pitch : %f\n", m_Pitch);
	}
}

void MediaPlayer::PanRight()
{
	m_Pan += 0.1f;
	if (m_Pan > 1.0f)
	{
		m_Pan = 1.0f;
		printf("Audio Source Position : Max Pan Right\n");
	}
	else
	{
		m_AudioManager->SetChannelPan(m_CurrentChannel, m_Pan);
		printf("Audio Source Position : %f\n", m_Pan);
	}
}

void MediaPlayer::PanLeft()
{
	m_Pan -= 0.1f;
	if (m_Pan < -1.0f)
	{
		m_Pan = -1.0f;
		printf("Audio Source Position : Max Pan Left\n");
	}
	else
	{
		m_AudioManager->SetChannelPan(m_CurrentChannel, m_Pan);
		printf("Audio Source Position : %f\n", m_Pan);
	}
}
