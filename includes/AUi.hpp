/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AUi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:08:36 by jules             #+#    #+#             */
/*   Updated: 2019/10/19 16:53:17 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUI_HPP
# define AUI_HPP

# include "glm.hpp"

class AUi
{
	public:

		AUi(void);
		~AUi(void);
		virtual void			Draw() const = 0;
		virtual	void			OnClick();
		virtual	void			OnRelease();
		virtual glm::vec4		GetMinMax() const = 0;
		virtual	void			Resize() = 0;

		bool					GetClicked() const;
	private:
		bool					_clicked;
};

#endif
