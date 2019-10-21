/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UiButton.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 14:33:58 by jules             #+#    #+#             */
/*   Updated: 2019/10/21 11:06:40 by jules            ###   ########.fr       */
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
		UiButton(glm::vec2 pos, float width, float height, std::string text, glm::vec4 color, void (*OnClickEvent)());
		UiButton(glm::vec2 pos, float width, float height, std::string text, const std::string path, void (*OnClickEvent)());
		UiButton(void);
		virtual	~UiButton();

		glm::vec2		pos;
		glm::vec4		color;
		void			(*OnClickEvent)();
		void			(*OnReleaseEvent)() = nullptr;

		virtual void	Draw() const;
		virtual void	OnClick();
		virtual void	OnRelease();
		virtual	void	Resize();

		glm::vec4		GetMinMax() const;
		float			GetWidth() const;
		float			GetHeight() const;

		std::shared_ptr<UiText>			text;
		bool							displayText;
	private:
		std::vector<GLfloat>	_vertices;
		std::vector<unsigned int>	_faces;
		std::shared_ptr<Shader>	_shader;
		GLuint			_vbo;
		GLuint			_vao;
		GLuint			_ebo;
		glm::mat4		_proj;
		GLuint			_textureId;
		bool			_hasImage;
		float			_width;
		float			_height;

		void			_Init(std::string text, const std::string path = "");

};

#endif
