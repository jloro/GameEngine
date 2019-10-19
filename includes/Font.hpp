/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Font.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:22:15 by jules             #+#    #+#             */
/*   Updated: 2019/10/19 14:22:38 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_HPP
# define FONT_HPP

# include <string>
# include "Shader.hpp"
# include <memory>
# include "glm.hpp"
# include <map>
# include "SdlWindow.hpp"

struct Character {
    glm::vec2 Size;       // Size of glyph
    glm::vec2 Bearing;    // Offset from baseline to left/top of glyph
    float     Advance;    // Offset to advance to next glyph
	glm::vec4	textureCoord; //s0, s1, t0, t1
};

class Font
{
	public:
		Font(const std::string font, int pixelSize);
		virtual ~Font();

		void	RenderText(const std::string text, float x, float y, float scale, glm::vec4 color);

		void	UpdateProj();
		int		GetPixelSize() const;
		int		GetTextWidth(std::string text, float scale);

	private:
		GLuint			_texture;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_vao;
		std::map<GLchar, Character> _characters;
		glm::mat4		_proj;
		int				_pixelSize;
};

#endif
