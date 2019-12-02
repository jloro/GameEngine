#include "Light.hpp"
#include <string>

Light::Light(eLightType type) : _type(type) {
    
}

Light::~Light() {
    
}

void Light::SendLightToShader(std::shared_ptr<Shader> shader) const {
    shader->setVec3("light.ambient", data.ambient);
    shader->setVec3("light.diffuse", data.diffuse);
    shader->setVec3("light.specular", data.specular);
    shader->setVec3("light.pos", data.pos);
    shader->setVec3("light.dir", -data.dir);
    shader->setFloat("light.constant", data.constant);
    shader->setFloat("light.linear", data.linear);
    shader->setFloat("light.quadratic", data.quadratic);
    shader->setFloat("light.cutOff", data.cutOff);
}

eLightType Light::GetLightType() const { return _type; }
