#pragma once

#include <SFML/Audio.hpp>
#include "Core.h"

namespace TGX
{
class Music
{
public:
	enum class Song : std::uint8_t
	{
		Intro,
	};

	Music(Song song);
	~Music();

	void Play();
	void Stop();

private:
	static String GetPathForSong(Song song);

	sf::Music music;
};
} // namespace TGX
