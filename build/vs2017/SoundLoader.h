#pragma once
#include <audio/audio_manager.h>
#include <map>
class SoundLoader
{
public:
	SoundLoader(gef::AudioManager& audio_manager,gef::Platform& platform);
	~SoundLoader();
	Int32 loadSound(const char* file_name, float volume);
	inline gef::AudioManager& get_audio_manager() { return audio_manager_; };
private:
	std::map<const char*, Int32> sound_id_map_;
	gef::AudioManager& audio_manager_;
	gef::Platform& platform_;
};

