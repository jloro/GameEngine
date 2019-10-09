/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BoxCollider.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:03:32 by jules             #+#    #+#             */
/*   Updated: 2019/09/18 16:16:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOXCOLLIDER_HPP
# define BOXCOLLIDER_HPP

# include <iostream>
# include "ACollider.hpp"

class BoxCollider : public ACollider
{

public: 
/*	constructors / destrucors	*/
    BoxCollider(GameObject *obj, glm::vec3 min, glm::vec3 max, glm::vec3 scale, glm::vec3 offset, bool showMesh); 
    //BoxCollider(const BoxCollider & src); 
    virtual ~BoxCollider(void); 

/*	public variables	*/
/*	public functions	*/
	//BoxCollider &		operator=(const BoxCollider & rhs);
    virtual bool IsCollindingWith(ACollider &other) const;

private:
/*	private variables	*/
/*	private functions	*/

};

#endif
