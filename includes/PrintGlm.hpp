/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintGlm.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 19:17:06 by jloro             #+#    #+#             */
/*   Updated: 2019/09/17 18:31:19 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTGLM_HPP
# define PRINTGLM_HPP

# include <iostream>
# include "glm.hpp"
//# include "gtc/matrix_transform.hpp"
# include "gtc/type_ptr.hpp"

std::ostream &operator<<(std::ostream &o, glm::vec3 & vec);
std::ostream &operator<<(std::ostream &o, glm::vec4 & vec);
std::ostream &operator<<(std::ostream &o, glm::mat3 & mat);
std::ostream &operator<<(std::ostream &o, glm::mat4 & mat);
#endif
