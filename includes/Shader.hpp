/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:19:23 by jloro             #+#    #+#             */
/*   Updated: 2019/09/17 18:31:32 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_HPP
# define SHADER_HPP

# include <vector>
# include "glad.h"
# include <glm.hpp>
# define ENGINE_PATH "GameEngine/"

class Camera;
class SdlWindow;

class Shader
{
	public:
		Shader(std::vector<const char *> shaderSource, std::vector<GLenum> shaderType);
		virtual~Shader();

		virtual void	use(void) const;
		void	Reload(void);

		void	SetBool(const std::string &name, bool value) const;
		void SetInt(const std::string &name, int value) const;
		void SetFloat(const std::string &name, float value) const;
		void SetVec2(const std::string &name, const glm::vec2 &value) const;
		void SetVec2(const std::string &name, float x, float y) const;
		void SetVec3(const std::string &name, const glm::vec3 &value) const;
		void SetVec3(const std::string &name, float x, float y, float z) const;
		void SetVec4(const std::string &name, const glm::vec4 &value) const;
		void SetVec4(const std::string &name, float x, float y, float z, float w) const;
		void SetMat2(const std::string &name, const glm::mat2 &mat) const;
		void SetMat3(const std::string &name, const glm::mat3 &mat) const;
		void SetMat4(const std::string &name, const glm::mat4 &mat) const;
		void SetMat4v(const std::string &name, std::vector<glm::mat4> &mat) const;
		void SetUpUniforms(const Camera &cam, const SdlWindow &win, float time) const ;

		static std::shared_ptr<Shader>	standard;
		static std::shared_ptr<Shader>	skeletal;

	protected:
		std::vector<const char *> 	_shaderSource;
		std::vector<GLenum> 	 	_shaderType;
		void	_checkCompileError(GLuint shader, const std::string &filename) const;
		void	_LoadShader(void);

		GLuint				_program;
};
std::ostream &operator<<(std::ostream &o, const glm::vec2 & vec);
std::ostream &operator<<(std::ostream &o, const glm::vec3 & vec);


#endif
