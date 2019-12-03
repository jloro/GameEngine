#include "Light.hpp"
#include <string>

Light::Light(eLightType type) : _type(type) {
    
}

Light::~Light() {
    
}

void Light::SendLightToShader(std::shared_ptr<Shader> shader) const {
    shader->SetVec3("light.ambient", data.ambient);
    shader->SetVec3("light.diffuse", data.diffuse);
    shader->SetVec3("light.specular", data.specular);
    shader->SetVec3("light.pos", data.pos);
    shader->SetVec3("light.dir", -data.dir);
    shader->SetFloat("light.constant", data.constant);
    shader->SetFloat("light.linear", data.linear);
    shader->SetFloat("light.quadratic", data.quadratic);
    shader->SetFloat("light.cutOff", data.cutOff);
    shader->SetBool("light.isPoint", _type == eLightType::Point);
    shader->SetBool("light.isDir", _type == eLightType::Directionnal);
    shader->SetBool("light.isSpot", _type == eLightType::Spot);
}

eLightType Light::GetLightType() const { return _type; }
