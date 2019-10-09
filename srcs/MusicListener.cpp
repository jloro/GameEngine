#include "MusicListener.hpp"

MusicListener::MusicListener(const char * path, int volume)
{
	_music = Mix_LoadMUS(path);
	if (_music == NULL)
		throw std::runtime_error(std::string("error : \n") + std::string(Mix_GetError()));
	else
		Mix_VolumeMusic(volume);
}

MusicListener::~MusicListener()
{
	Mix_FreeMusic(_music);
	_music = NULL;
}

void	MusicListener::ChangeVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

void	MusicListener::Play(bool fadeIn, int ms)
{
	if (fadeIn)
		Mix_FadeInMusic(_music, -1, ms);
	else
		Mix_PlayMusic(_music, -1);
}

void	MusicListener::Pause()
{
	Mix_PauseMusic();
}

void	MusicListener::Stop(bool fadeOut, int ms)
{
	if (fadeOut)
		Mix_FadeOutMusic(ms);
	else
		Mix_HaltMusic();
}

void	MusicListener::Resume()
{
	Mix_ResumeMusic();
}
