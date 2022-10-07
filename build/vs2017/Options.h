#pragma once

#include <fstream>
#include <string>
#include <audio/audio_manager.h>
enum class Difficulty
{
	easy,
	medium,
	hard
};
class Options
{
public:
	static Options& instance();
	int volume_ = 1;

	Difficulty difficulty_ = Difficulty::easy;
	~Options();

private:
	Options();
};

