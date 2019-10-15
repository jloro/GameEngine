#include "GameObject.hpp"
#include "AComponent.hpp"
#include <algorithm>
#include "Engine.hpp"

GameObject::GameObject(void) : _tag("Default")
{
    _transform = std::shared_ptr<Transform>(new Transform());
    destroyOnReset = true;
}

GameObject::GameObject(Transform trans) : _tag("Default")
{
    _transform = std::shared_ptr<Transform>(new Transform(trans));
    destroyOnReset = true;
}
GameObject::GameObject(Transform trans, std::string tag) : _tag(tag)
{
    _transform = std::shared_ptr<Transform>(new Transform(trans));
    destroyOnReset = true;
}
GameObject::GameObject(std::string tag) : _tag(tag)
{
    _transform = std::shared_ptr<Transform>(new Transform());
    destroyOnReset = true;
}
void GameObject::AddComponent(std::shared_ptr<AComponent> component)
{
    if (find(_components.begin(), _components.end(), component) == _components.end())
    {
        _components.push_back(component);
        component->SetGameObject(this);
    }
}

GameObject::~GameObject(void) { }

std::shared_ptr<Transform> GameObject::GetTransform(void) const
{
    return _transform;
}
void	GameObject::Update(void)
{
}
void	GameObject::FixedUpdate(void)
{
}

std::string	GameObject::GetTag() const { return _tag; }
void		GameObject::SetTag(std::string tag) { _tag = tag; }

bool		GameObject::CompareTags(std::string otherTag)
{
	return Engine42::Engine::GetTag(_tag) & Engine42::Engine::GetTag(otherTag);
}
