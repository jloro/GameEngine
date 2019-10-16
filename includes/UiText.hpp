/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UiText.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:35:19 by jules             #+#    #+#             */
/*   Updated: 2019/10/16 16:16:38 by jules            ###   ########.fr       */
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

		glm::vec4		GetMinMax() const;

		std::string		text;
		glm::vec2		pos;
		float			scale;
		glm::vec4		color;
	private:

};

#endif
