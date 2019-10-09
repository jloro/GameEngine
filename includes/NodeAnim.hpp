/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NodeAnim.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:20:55 by jloro             #+#    #+#             */
/*   Updated: 2019/09/25 14:36:22 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODEANIM_HPP
# define NODEANIM_HPP

# include <string>
# include "glm.hpp"
# include <vector>
# include <assimp/scene.h>
# include <gtx/quaternion.hpp>

struct	vectorKey
{
	glm::vec3	value;
	double		time;
};

struct	quatKey
{
	glm::quat	value;
	double		time;
};

class NodeAnim
{
	public:
		NodeAnim(aiNodeAnim* infos);
		virtual~NodeAnim();

		std::string	nodeName;

		unsigned int	numPositionKeys;
		unsigned int	numRotationKeys;
		unsigned int	numScalingKeys;

		std::vector<vectorKey>	positionKeys;
		std::vector<vectorKey>	scalingKeys;
		std::vector<quatKey>	rotationKeys;
	private:
		glm::mat3				_aiMat3ToGlmMat3(aiMatrix3x3 from);
};

#endif
