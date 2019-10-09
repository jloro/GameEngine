#ifndef ACOMPONENT_HPP
# define ACOMPONENT_HPP

# include <iostream>
# include "GameObject.hpp"
# include <memory>

class AComponent 
{
public: 
/*	constructors / destrucors	*/
    AComponent();
    AComponent(GameObject *obj);
    AComponent(std::shared_ptr<GameObject> obj);
    virtual ~AComponent();
    void SetGameObject(GameObject *obj);

/*	public functions	*/
    virtual std::shared_ptr<Transform>  GetTransform() const;
    virtual GameObject  *GetGameObj() const;

protected:
/*
    if component have a shared_ptr of gameObject and 
    GameObject have shared_ptr of Component that
    create a circular dependency
*/
    GameObject *_gameObj;
    std::shared_ptr<Transform> _transform;
};
#endif