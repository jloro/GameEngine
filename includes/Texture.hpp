/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 16:43:54 by jloro             #+#    #+#             */
/*   Updated: 2019/06/20 16:44:16 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "glad.h"

enum class eTextureType {Diffuse, Specular, Ambient, Cubemap};

struct Texture 
{
	GLuint	id;
	eTextureType	type;
    std::string path;
};

#endif