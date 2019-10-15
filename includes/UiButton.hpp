/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UiButton.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:33:58 by jules             #+#    #+#             */
/*   Updated: 2019/10/15 17:44:03 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UIBUTTON_HPP
# define UIBUTTON_HPP

# include "AComponent.hpp"
# include "Shader.hpp"
# include "IUi.hpp"
# include "UiText.hpp"

class UiButton : public AComponent, public IUi
{
	public:
		UiButton(glm::vec2 pos, glm::vec2 scale, std::string text, glm::vec4 color, void (*OnClick)());
		UiButton(void);
		virtual	~UiButton();

		glm::vec2		pos;
		glm::vec2		scale;
		glm::vec4		color;
		void			(*OnClick)();

		virtual void	Draw() const;

		glm::vec4		GetMinMax() const;
	private:
		std::vector<GLfloat>	_vertices;
		std::vector<unsigned int>	_faces;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_vao;
		GLuint			_ebo;
		glm::mat4		_proj;
		std::shared_ptr<UiText>			_text;
};

#endif
