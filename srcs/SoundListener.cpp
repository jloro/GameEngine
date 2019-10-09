#include "SoundListener.hpp"

SoundListener::SoundListener(const char * path, int volume)
{
	_sound = Mix_LoadWAV(path);
	if (_sound == NULL)
		throw std::runtime_error(std::string("error : \n") + std::string(Mix_GetError()));
	else
		Mix_VolumeChunk(_sound, volume);
}

SoundListener::~SoundListener()
{
	Mix_FreeChunk(_sound);
	_sound = NULL;
}

void	SoundListener::Play()
{
	Mix_PlayChannel(-1, _sound, 0);
}

void	SoundListener::ChangeVolume(int volume)
{
	Mix_VolumeChunk(_sound, volume);
}
