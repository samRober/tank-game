#include "SoundLoader.h"

SoundLoader::SoundLoader(gef::AudioManager& audio_manager, gef::Platform& platform) :
	audio_manager_(audio_manager),
	platform_(platform)
{
}

SoundLoader::~SoundLoader()
{
	for (auto i = sound_id_map_.begin();i != sound_id_map_.end();)//free resources
	{
		audio_manager_.UnloadSample(i->second);
		i = sound_id_map_.erase(i);
	}
}

Int32 SoundLoader::loadSound(const char* file_name, float volume)
{
	auto map_sound = sound_id_map_.find(file_name);
	Int32 soundId;
	if (map_sound != sound_id_map_.end()) {
		soundId = map_sound->second;
	}
	else {
		soundId = audio_manager_.LoadSample(file_name, platform_);
		sound_id_map_.insert({ file_name, soundId });

	}
	gef::VolumeInfo vi;
	vi.volume = volume;
	audio_manager_.SetSampleVoiceVolumeInfo(soundId, vi);
	return soundId;
}
