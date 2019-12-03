#include "Material.hpp"
#include "PrintGlm.hpp"

#pragma region Constructor/Destructor
Material::Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float shininess) {
    _mat.ambient = ambient;
    _mat.diffuse = diffuse;
    _mat.specular = specular;
    _mat.shininess = shininess;
    _mat.hasAmbientMap = false;
    _mat.hasDiffuseMap = false;
    _mat.hasSpecularMap = false;
    _ambientMap.type = eTextureType::Ambient;
    _specularMap.type = eTextureType::Specular;
    _diffuseMap.type = eTextureType::Diffuse;

}

Material::Material()
{
    _mat.hasAmbientMap = false;
    _mat.hasDiffuseMap = false;
    _mat.hasSpecularMap = false;
    _ambientMap.type = eTextureType::Ambient;
    _specularMap.type = eTextureType::Specular;
    _diffuseMap.type = eTextureType::Diffuse;
    _mat.ambient = glm::vec4(0.0f);
    _mat.diffuse = glm::vec4(1.0f);
    _mat.specular = glm::vec4(0.0f);
    _mat.shininess = 1.0f;
}

Material::~Material() {
    
}
#pragma endregion

#pragma region Getters/Setters

void Material::SetAmbientMap(std::string path, GLuint id) {
    _mat.hasAmbientMap = true;
    _ambientMap.path = path;
    _ambientMap.id = id;
}

void Material::SetDiffuseMap(std::string path, GLuint id) {
    _mat.hasDiffuseMap = true;
    _diffuseMap.path = path;
    _ambientMap.id = id;
}

void Material::SetSpecularMap(std::string path, GLuint id) {
    _mat.hasSpecularMap = true;
    _specularMap.path = path;
    _ambientMap.id = id;
    
}
void Material::SetAmbientMap(Texture map) {
    _mat.hasAmbientMap = true;
    _ambientMap = map;
}

void Material::SetDiffuseMap(Texture map) {
    _mat.hasDiffuseMap = true;
    _diffuseMap = map;
}

void Material::SetSpecularMap(Texture map) {
    _mat.hasSpecularMap = true;
    _specularMap = map;
    
}

void Material::SetAmbient(glm::vec4 ambient) { _mat.ambient = ambient; }
void Material::SetDiffuse(glm::vec4 diffuse) { _mat.diffuse = diffuse; }
void Material::SetSpecular(glm::vec4 specular) { _mat.specular = specular; }
void Material::SetAmbient(aiColor3D ambient) { _mat.ambient = glm::vec4(ambient.r, ambient.g, ambient.b, 1.0f); }
void Material::SetDiffuse(aiColor3D diffuse) { _mat.diffuse = glm::vec4(diffuse.r, diffuse.g, diffuse.b, 1.0f); }
void Material::SetSpecular(aiColor3D specular) { _mat.specular = glm::vec4(specular.r, specular.g, specular.b, 1.0f); }
void Material::SetShininess(float shininess) { _mat.shininess = shininess; 
}
MaterialData Material::GetMaterialData() const { return (_mat); }
Texture Material::GetAmbientMap() const { return _ambientMap; }
Texture Material::GetDiffuseMap() const { return _diffuseMap; }
Texture Material::GetSpecularMap() const { return _specularMap; }

#pragma endregion

#pragma region Utils

void Material::SendMaterialToShader(std::shared_ptr<Shader> shader) const {
    unsigned int i = 0;
    glActiveTexture(GL_TEXTURE0 + i);
    if (_mat.hasAmbientMap)
    {
        shader->SetInt("texture_ambient", i++);
        glBindTexture(GL_TEXTURE_2D, _ambientMap.id);
    }
    if (_mat.hasDiffuseMap)
    {
        shader->SetInt("texture_diffuse", i++);
        glBindTexture(GL_TEXTURE_2D, _diffuseMap.id);
    }
    if (_mat.hasSpecularMap)
    {
        shader->SetInt("texture_specular", i++);
        glBindTexture(GL_TEXTURE_2D, _specularMap.id);
    }
    shader->SetVec4("material.diffuse", _mat.diffuse);
    shader->SetVec4("material.specular", _mat.specular);
    shader->SetVec4("material.ambient", _mat.ambient);
    shader->SetFloat("material.shininess", _mat.shininess);
    shader->SetBool("material.hasAmbientMap", _mat.hasAmbientMap);
    shader->SetBool("material.hasDiffuseMap", _mat.hasDiffuseMap);
    shader->SetBool("material.hasSpecularMap", _mat.hasSpecularMap);
}
#pragma endregion

#pragma region operator overload
bool Material::operator==(Material& other) {
    MaterialData otherData = other.GetMaterialData();
    bool ret = true;
    if (otherData.hasAmbientMap == _mat.hasAmbientMap
        && otherData.hasDiffuseMap == _mat.hasDiffuseMap
        && otherData.hasSpecularMap == _mat.hasSpecularMap)
    {
        ret = ret || (otherData.ambient == _mat.ambient && otherData.diffuse == _mat.diffuse && otherData.specular == _mat.specular);
        if (_mat.hasAmbientMap)
            ret = ret || (other.GetAmbientMap().path == _ambientMap.path);

        if (_mat.hasDiffuseMap)
            ret = ret || (other.GetDiffuseMap().path == _diffuseMap.path);

        if (_mat.hasSpecularMap)
            ret = ret || (other.GetSpecularMap().path == _specularMap.path);

        return (ret || (_mat.shininess == otherData.shininess));
    }
    else
        return false;
    
}

Material& Material::operator=(Material const & other)
{
    _mat = other.GetMaterialData();
    _ambientMap = other.GetAmbientMap();
    _diffuseMap = other.GetDiffuseMap();
    _specularMap = other.GetSpecularMap();
    return *this;
}

std::ostream & operator<<(std::ostream & o, Material const & rhs)
{
    MaterialData data = rhs.GetMaterialData();
    o << "Material data: " << std::endl;
    o << "Ambient: " << data.ambient << std::endl;
    o << "Diffuse: " << data.diffuse << std::endl;
    o << "Specular: " << data.specular << std::endl;
    o << "Shininess: " << data.shininess << std::endl;

    if (data.hasDiffuseMap)
        o << "DiffuseMap: " << rhs.GetDiffuseMap().path << std::endl;

   // o << "Material data: " << std::endl;

    return o;
}


#pragma endregion