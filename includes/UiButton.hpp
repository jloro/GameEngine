/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UiButton.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:33:58 by jules             #+#    #+#             */
/*   Updated: 2019/10/19 19:41:11 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UIBUTTON_HPP
# define UIBUTTON_HPP

# include "AComponent.hpp"
# include "Shader.hpp"
# include "AUi.hpp"
# include "UiText.hpp"

class UiButton : public AComponent, public AUi
{
	public:
		UiButton(glm::vec2 pos, glm::vec2 scale, std::string text, glm::vec4 color, void (*OnClickEvent)());
		UiButton(void);
		virtual	~UiButton();

		glm::vec2		pos;
		glm::vec2		scale;
		glm::vec4		color;
		void			(*OnClickEvent)();
		void			(*OnReleaseEvent)();

		virtual void	Draw() const;
		virtual void	OnClick();
		virtual void	OnRelease();

		glm::vec4		GetMinMax() const;
		virtual	void	Resize();

		std::shared_ptr<UiText>			text;
	private:
		std::vector<GLfloat>	_vertices;
		std::vector<unsigned int>	_faces;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_vao;
		GLuint			_ebo;
		glm::mat4		_proj;

};

#endif
