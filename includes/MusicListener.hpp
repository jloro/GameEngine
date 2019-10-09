/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MusicListener.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:49:41 by jules             #+#    #+#             */
/*   Updated: 2019/10/08 16:22:02 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUSICLISTENER_HPP
# define MUSICLISTENER_HPP

# include "AComponent.hpp"
# include "SDL_mixer.h"

class MusicListener : public AComponent
{
	public:
		MusicListener(const char* path, int volume = 100);
		virtual	~MusicListener();

		void	Play(bool fadeIn = false, int ms = 0);
		void	Resume();
		void	Pause();
		void	Stop(bool fadeOut = false, int ms = 0);
		void	ChangeVolume(int volume);
	private:
		Mix_Music	*_music; 
};

#endif
