/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 11:31:23 by jloro             #+#    #+#             */
/*   Updated: 2019/10/14 12:16:19 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"
#include <iostream>

Mesh::Mesh(void)
{
    _vao = _vbo = _ebo = 0;
}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> faces, std::vector<Texture> textures) : 
vertices(vertices), faces(faces), textures(textures), _hasTexture(true)
{
	diffuse = glm::vec3(-1.0f);
	ambient = glm::vec3(-1.0f);
	specular = glm::vec3(-1.0f);
}
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> faces, glm::vec3 diffuse, glm::vec3 ambient, glm::vec3 specular) : 
vertices(vertices), faces(faces), _hasTexture(false)
{
	this->diffuse = diffuse;
	this->ambient = ambient;
	this->specular = specular;
}
Mesh::Mesh(Mesh const & src) 
{
    _ebo = 0;
    _vbo = 0;
    _vao = 0;
    *this = src;
}
Mesh::~Mesh() 
{
    glDeleteBuffers(1, &_ebo);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_vao);
}
Mesh &	Mesh::operator=(Mesh const & rhs)
{
    this->vertices = rhs.vertices;
    this->faces = rhs.faces;
    this->textures = rhs.textures;
	this->diffuse = rhs.diffuse;
	this->specular = rhs.specular;
	this->ambient = rhs.ambient;
	this->_hasTexture = rhs.HasTexture();
    glDeleteBuffers(1, &_ebo);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_vao);
    return *this;
}
void	Mesh::SendToOpenGL()
{
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glGenVertexArrays(1, &_vao);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faces.size(), &faces[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, ids));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));

	glBindVertexArray(0);
}

void	Mesh::Draw(const std::shared_ptr<Shader>  shader) const
{
	unsigned int	diffuseNb = 0;
	unsigned int	specularNb = 0;
	unsigned int	cubeMapNb = 0;
	std::string		name;

	shader->setInt("uHasTexture", static_cast<int>(_hasTexture));
	if (!_hasTexture)
	{
		shader->setVec3("uDiffuse", diffuse);
		shader->setVec3("uAmbient", ambient);
		shader->setVec3("uSpecular", specular);
	}
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		if (textures[i].type == eTextureType::Diffuse)
		{
			name = "texture_diffuse" + std::to_string(diffuseNb++);
		}
		else if (textures[i].type == eTextureType::Specular)
		{
			name = "texture_specular" + std::to_string(specularNb++);
		}
		else if (textures[i].type == eTextureType::Cubemap)
		{
			name = "cubeMap" + std::to_string(cubeMapNb++);
		}
		shader->setInt(name.c_str(), i);
		if (textures[i].type != eTextureType::Cubemap)
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		else 
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures[i].id);
	}

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

bool	Mesh::HasTexture() const { return _hasTexture; }
void	Mesh::SetHasTexture(bool hasTexture) { _hasTexture = hasTexture; }
