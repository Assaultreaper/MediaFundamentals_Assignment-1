#include <fmod.hpp>
#include "Utilities.h"

#include <map>
#include <vector>
#include <conio.h>


namespace PlayerUtils
{
	struct Audio
	{
		const char* name;
		FMOD::Sound* Audio;
	};

	struct Channel
	{
		const char* name;
		FMOD::Channel* fmodChannel;
		float volume;
		float pitch;
		float pan;
		bool playing;
	};

	class AudioManager
	{
		public:
			AudioManager();
			~AudioManager();

			void Initialize();
			void Update();
			void Destroy();

			void LoadAudioStream(const char* source);
			void LoadAudio(const char* file);

			int PlayAudio(const char* AudioName, bool& isPlaying);
			int MediaStatus(const int ChannelID, bool& isPlaying);
			int StopAudio(const int ChannelID, bool& isPlaying);

			void SetChannelVolume(const int ChannelID, float& VolumeValue);
			void SetChannelPitch(const int ChannelID, float& PitchValue);
			void SetChannelPan(const int ChannelID, float& PanValue);

			bool GetChannelPlaying(int ChannelID);
			bool GetPlaybackStatus(const int ChannelID, bool& isPlaying);
			void GetPlaybackPosition(int ChannelID, unsigned int& value);

			void printinfo() const;

	private:
		bool m_Initialized = false;
		bool paused = false;

		std::map<const char*, Audio*> m_AudioMap;

		std::vector<Channel*> m_ChannelList;
		int m_NextChannelID = 0;

		FMOD::System* m_system = nullptr;
	};
}

