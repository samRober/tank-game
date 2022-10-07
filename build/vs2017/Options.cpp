#include "Options.h"
#include <sstream>
Options& Options::instance()
{
	static Options instance;
	return instance;
}



Options::Options()
{
	//load options from file
	std::ifstream file;
	file.open("options.txt");
	for (std::string s; std::getline(file, s);) {
		std::string tmp;
		std::stringstream s_stream(s);
		std::getline(s_stream, tmp, ' ');
		if(tmp == "volume"){
			s_stream >> volume_;
			continue;
		}
		if (tmp == "difficulty") {
			std::getline(s_stream, tmp, ' ');
			if (tmp == "easy") {
				difficulty_ = Difficulty::easy;
			}
			if (tmp == "medium") {
				difficulty_ = Difficulty::medium;

			}
			if (tmp == "hard") {
				difficulty_ = Difficulty::hard;

			}
			continue;
		}
	}
}

Options::~Options()
{
	//save options to file
	std::ofstream file;
	file.open("options.txt");
	file << "volume " << volume_ << std::endl;
	file << "difficulty ";
	switch (difficulty_)
	{
	case Difficulty::easy:
		file << "easy";
		break;
	case Difficulty::medium:
		file << "medium";
		break;
	case Difficulty::hard:
		file << "hard";
		break;
	default:
		break;
	}
	file << std::endl;
}
