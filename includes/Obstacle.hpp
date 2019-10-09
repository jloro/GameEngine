/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:16:08 by jules             #+#    #+#             */
/*   Updated: 2019/09/27 13:57:31 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBSTACLE_HPP
# define OBSTACLE_HPP

# include "GameObject.hpp"
# include "Model.hpp"
# include "Shader.hpp"

class Obstacle : public GameObject
{
	public:
		Obstacle(void);
		virtual	~Obstacle();

		virtual void	Update(void);
		virtual void	FixedUpdate(void);
		std::list<std::shared_ptr<GameObject>>  obstacles;

		void	Reset();
		void					AddObstacle(bool pillar, std::shared_ptr<Transform> parent);
	private:
		std::list<std::shared_ptr<GameObject>>  _pillar;
		std::list<std::shared_ptr<GameObject>>  _jumpOver;
		std::list<std::shared_ptr<GameObject>>  _coins;

		int			_GetRandomRow(bool left, bool middle, bool right);
};

#endif
