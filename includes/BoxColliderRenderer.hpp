/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoxColliderRenderer.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:21:46 by jules             #+#    #+#             */
/*   Updated: 2019/09/18 16:21:47 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOXCOLLIDERRENDERER_HPP
# define BOXCOLLIDERRENDERER_HPP

# include "ARenderer.hpp"
# include "BoxCollider.hpp"
# include "GameObject.hpp"

class BoxColliderRenderer : public ARenderer
{
	public:
		BoxColliderRenderer(GameObject* obj, BoxCollider* collider);
		virtual	~BoxColliderRenderer();

		virtual void        Draw() const;
	private:
		std::shared_ptr<Mesh>		_mesh;
		std::shared_ptr<Shader>		_shader;
		GameObject*					_go;
		BoxCollider*					_collider;
};

#endif
