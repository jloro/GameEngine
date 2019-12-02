/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:46:40 by jules             #+#    #+#             */
/*   Updated: 2019/11/27 17:56:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_HPP
# define MATERIAL_HPP

# include <glm.hpp>
# include <string>
# include "Shader.hpp"
# include "Texture.hpp"
# include <assimp/scene.h>
# include <iostream>

struct MaterialData
{
	bool		hasAmbientMap;
	bool		hasDiffuseMap;
	bool		hasSpecularMap;
	glm::vec4	ambient;
	glm::vec4	diffuse;
	glm::vec4	specular;
	float		shininess;
};

class Material
{
	public:
		Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess);
		Material();
		virtual	~Material();

		void	SetAmbientMap(std::string path, GLuint id);
		void	SetDiffuseMap(std::string path, GLuint id);
		void	SetSpecularMap(std::string path, GLuint id);
		void	SetAmbientMap(Texture map);
		void	SetDiffuseMap(Texture map);
		void	SetSpecularMap(Texture map);
		void	SetAmbient(glm::vec4 ambient);
		void	SetDiffuse(glm::vec4 diffuse);
		void	SetSpecular(glm::vec4 specular);
		void	SetAmbient(aiColor3D ambient);
		void	SetDiffuse(aiColor3D diffuse);
		void	SetSpecular(aiColor3D specular);
		void	SetShininess(float shininess);



		Texture		GetDiffuseMap() const;
		Texture		GetSpecularMap() const;
		Texture		GetAmbientMap() const;
		MaterialData 	GetMaterialData(void) const;

		void	SendMaterialToShader(std::shared_ptr<Shader> shader) const;
		bool 	operator==(Material & other);
		Material& operator=(Material const & other);
	private:
		MaterialData	_mat;
		Texture			_diffuseMap;
		Texture			_ambientMap;
		Texture			_specularMap;
};
std::ostream & operator<<(std::ostream & o, Material const & rhs);
#endif
