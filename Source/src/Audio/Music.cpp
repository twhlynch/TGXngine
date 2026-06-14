#include "Music.h"
#include "Logs.h"

namespace TGX
{
Music::Music(Song song)
{
	String name = GetPathForSong(song);

	if (name.empty())
	{
		return;
	}

	if (!music.openFromFile("audio/" + name + ".ogg"))
	{
		Log::Warning("Failed to read music audio");
	}
}

Music::~Music() = default;

String Music::GetPathForSong(Song song)
{
	switch (song)
	{
		case Song::Intro:
			return "intro";
	}

	return "";
}

void Music::Play()
{
	music.play();
}

void Music::Stop()
{
	music.stop();
}
} // namespace TGX
