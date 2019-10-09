/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:52:36 by jloro             #+#    #+#             */
/*   Updated: 2019/09/25 14:58:06 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include "glm.hpp"
# include <string>
# include <vector>
# include <assimp/scene.h>

class Node
{
	public:
		Node(aiNode* root);
		virtual~Node();

		std::string	name;
		glm::mat4	transform;
		std::vector<std::shared_ptr<Node>>	children;
		unsigned int	numChildren;
	private:
		glm::mat4	_aiMat4ToGlmMat4(aiMatrix4x4 from);
};

#endif
