/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SoundListener.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:46:06 by jules             #+#    #+#             */
/*   Updated: 2019/10/08 16:56:23 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOUNDLISTENER_HPP
# define SOUNDLISTENER_HPP

# include "AComponent.hpp"
# include "SDL_mixer.h"

class SoundListener : public AComponent
{
	public:
		SoundListener(const char * path, int volume = 100);
		virtual	~SoundListener();

		void	Play();
		void	ChangeVolume(int volume);
	private:
		Mix_Chunk*	_sound;

};

#endif
