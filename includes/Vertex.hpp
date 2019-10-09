/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vertex.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:41:44 by jloro             #+#    #+#             */
/*   Updated: 2019/09/10 12:53:40 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_HPP
# define VERTEX_HPP

# include <glm.hpp>
# define NUM_BONES_PER_VERTEX 4

struct Vertex {
	glm::vec3		position;
	glm::vec3		normal;
	glm::vec2		texCoord;
	unsigned int	ids[NUM_BONES_PER_VERTEX];
	float			weights[NUM_BONES_PER_VERTEX];
};

struct BoneInfo {
	glm::mat4		offsetMat;
	glm::mat4		finalTransMat;
};

#endif
