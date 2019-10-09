#include "AComponent.hpp"

AComponent::AComponent() : _gameObj(nullptr), _transform(nullptr)
{
}
AComponent::AComponent(GameObject *obj) : _gameObj(obj)
{
    if (_gameObj != nullptr)
    {
        _transform = _gameObj->GetTransform();
    }
}
AComponent::AComponent(std::shared_ptr<GameObject> obj) : _gameObj(obj.get())
{
    if (_gameObj != nullptr)
    {
        _transform = _gameObj->GetTransform();
    }
}
    
AComponent::~AComponent() {}

void    AComponent::SetGameObject(GameObject *obj)
{
    _gameObj = obj;
    if (_gameObj != nullptr)
    {
        _transform = _gameObj->GetTransform();
    }
    else
    {
        _transform = nullptr;
    }
    
}

GameObject  *AComponent::GetGameObj() const {return _gameObj;};
std::shared_ptr<Transform>  AComponent::GetTransform() const {return _transform;};