/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UiText.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:35:19 by jules             #+#    #+#             */
/*   Updated: 2019/10/19 16:55:31 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UITEXT_HPP
# define UITEXT_HPP

# include "glm.hpp"
# include "AComponent.hpp"
# include <string>
# include "AUi.hpp"

class UiText : public AComponent, public AUi
{
	public:
		UiText(std::string text, glm::vec2 pos, float scale, glm::vec4 color);
		UiText(void);
		virtual	~UiText();

		virtual void	Draw() const;
		virtual	void	OnClick();
		virtual	void	OnRelease();
		virtual	void	Resize();
		glm::vec4		GetMinMax() const;

		glm::vec2		pos;
		glm::vec4		color;

		std::string		GetText() const;
		int				GetWidthText() const;
		float			GetScale() const;
		void			SetText(std::string text);
		void			SetScale(float scale);

	private:
		std::string		_text;
		float			_scale;
		float			_width;

};

#endif
