/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintGlm.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:15:52 by jloro             #+#    #+#             */
/*   Updated: 2019/09/17 18:36:13 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PrintGlm.hpp"

std::ostream &operator<<(std::ostream &o, glm::vec3 & vec)
{
	o << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z;
	return o;
}
std::ostream &operator<<(std::ostream &o, glm::vec4 & vec)
{
	o << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ", w: " << vec.w;
	return o;
}
std::ostream &operator<<(std::ostream &o, glm::mat3 & mat)
{
	for (int i =0; i < 3; ++i)
	{
		o << mat[i] << std::endl;
	}
	return o;
}
std::ostream &operator<<(std::ostream &o, glm::mat4 & mat)
{
	for (int i =0; i < 4; ++i)
	{
		o << mat[i] << std::endl;
	}
	return o;
}

