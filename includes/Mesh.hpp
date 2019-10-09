/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 11:23:36 by jloro             #+#    #+#             */
/*   Updated: 2019/09/27 11:36:54 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_HPP
# define MESH_HPP

# include <glm.hpp>
# include <string>
# include <vector>
# include "glad.h"
# include "Shader.hpp"
# include "Vertex.hpp"
# include "Texture.hpp"

class Mesh
{
	public:
/*  constructors / destructors  */
		Mesh(void); 
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> faces, std::vector<Texture> textures);
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> faces, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular);
		Mesh(Mesh const & src); 
		virtual~Mesh();
/*  public variables  */
		std::vector<Vertex>			vertices;
		std::vector<unsigned int>	faces;
		std::vector<Texture>		textures;

		glm::vec3					diffuse;
		glm::vec3					ambient;
		glm::vec3					specular;
/*  public functions  */
		Mesh &		operator=(Mesh const & rhs);
		void		Draw(const std::shared_ptr<Shader>  shader) const;
		void		SendToOpenGL(void);

		bool		HasTexture() const;
	private:
/*  private variables  */
		GLuint						_vao;
		GLuint						_vbo;
		GLuint						_ebo;
		bool						_hasTexture;
/*  private functions */
};

#endif
