/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameManager.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 11:46:50 by jloro             #+#    #+#             */
/*   Updated: 2019/10/08 16:57:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

# include "Model.hpp"
# include <list>
# include "MeshRenderer.hpp"
# include "Player.hpp"
# include "Obstacle.hpp"
# include "RoomManager.hpp"
# include "SDL_mixer.h"
# include "SoundListener.hpp"

class GameManager : public GameObject
{
	public:
		GameManager(std::shared_ptr<Player> player);
		virtual~GameManager();

		virtual void	Update();
		virtual void	FixedUpdate();

		const static unsigned int	speedWorld;
		
		std::shared_ptr<Player>	player;

		static std::shared_ptr<GameManager>	instance;
		void					Reset();
		void					Die();
		int						GetScore(void) const;
		void					IncreaseScore(int amount);
		void 					PlayGameOver(void);
	private:
		int						_score;
		std::shared_ptr<Model>	_modelPillar;
		std::shared_ptr<RoomManager>	_rooms;
		std::shared_ptr<SoundListener>	_coinSound; 
		std::shared_ptr<SoundListener>	_gameOverSound; 
		float _timeScore;
};

#endif
