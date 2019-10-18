/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Text.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 13:31:18 by jules             #+#    #+#             */
/*   Updated: 2019/10/18 14:12:04 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_HPP
# define TEXT_HPP

# include <string>
# include "Shader.hpp"
# include <memory>
# include "glm.hpp"
# include <map>
# include "SdlWindow.hpp"
# include <nlohmann/json.hpp>

struct Character {
    glm::vec2 Size;       // Size of glyph
    glm::vec2 Bearing;    // Offset from baseline to left/top of glyph
    float     Advance;    // Offset to advance to next glyph
	glm::vec4	textureCoord; //s0, s1, t0, t1
};

class Text
{
	public:
		Text(const std::string font, int pixelSize);
		virtual ~Text();

		void	RenderText(const std::string text, float x, float y, float scale, glm::vec4 color);

		void	UpdateProj();
		int		GetPixelSize() const;
		int		GetTextWidth(std::string text, float scale);

		float up;
		float down;
	private:
		GLuint			_texture;
		nlohmann::json	_json;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_vao;
		std::map<GLchar, Character> _characters;
		glm::mat4		_proj;
		int				_pixelSize;
};

#endif
