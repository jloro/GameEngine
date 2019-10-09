#include "Transform.hpp"
#include <sstream>
#include "PrintGlm.hpp"
Transform::Transform()
{
    _Initialize(glm::vec3(0, 0, 0), glm::vec3(0,0,0), glm::vec3(1,1,1));
}

Transform::Transform(Transform const & src) 
{
    *this = src;
    return;
}

Transform::~Transform(void) {}

Transform &	Transform::operator=(Transform const & rhs)
{
    _Initialize(rhs.position, rhs.rotation, rhs.scale, rhs.parent);
    return *this;
}
Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent)
{
    _Initialize(pos, rot, scale, parent);
}
Transform::Transform(glm::vec3 pos, glm::vec3 scale, std::shared_ptr<Transform> parent)
{
    _Initialize(pos, glm::vec3(0,0,0), scale, parent);
}
Transform::Transform(glm::vec3 pos, std::shared_ptr<Transform> parent)
{
    _Initialize(pos, glm::vec3(0,0,0), glm::vec3(1,1,1), parent);
}
void    Transform::_Initialize(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, std::shared_ptr<Transform> parent)
{
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;
    this->parent = parent;
    UpdateMatrix();
}
void    Transform::UpdateMatrix()
{
    _localMatrix = glm::mat4(1.0f);
    _localMatrix = glm::translate(_localMatrix, position);
    _localMatrix = glm::rotate(_localMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    _localMatrix = glm::rotate(_localMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    _localMatrix = glm::rotate(_localMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    _localMatrix = glm::scale(_localMatrix, scale);
}
glm::mat4       Transform::GetLocalMatrix(void) const
{
    return _localMatrix;
}

glm::vec3		Transform::GetWorldPos(void) const
{
	return GetMatrix()[3];
}

glm::vec3		Transform::GetWorldScale(void) const
{
    if (parent != nullptr)
        return parent->GetWorldScale() * scale;
    return scale;
}
glm::mat4       Transform::GetMatrix(void) const
{
    if (parent != nullptr)
        return parent->GetMatrix() * _localMatrix;
    return _localMatrix ;
}
void            Transform::SetLocalMatrix(glm::mat4 matrix)
{
    _localMatrix = matrix;
}
std::string vecToStr(glm::vec3 const &vec)
{
    return std::string(std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z));
}
std::string Transform::toString(void) const
{
    std::string str;
    
    str =  "pos { " + vecToStr(position) + " } rot { " + vecToStr(rotation) + " } scale { " + vecToStr(scale) + " }";
    return str;
}

std::ostream &	operator<< (std::ostream & o, Transform const & rhs)
{
    o << rhs.toString();
    return o;
}
