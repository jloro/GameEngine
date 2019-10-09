#include "ARenderer.hpp"

ARenderer::ARenderer() : AComponent(), _shader(nullptr) {}
ARenderer::ARenderer(std::shared_ptr<GameObject> obj) : AComponent(obj.get()), _shader(nullptr) {}
ARenderer::ARenderer(std::shared_ptr<Shader>  shader, std::shared_ptr<GameObject> obj) : AComponent(obj.get()), _shader(shader) { }
ARenderer::ARenderer(std::shared_ptr<Shader>  shader, GameObject *obj) : AComponent(obj), _shader(shader) {  }
ARenderer::~ARenderer() {}

std::shared_ptr<Shader> ARenderer::GetShader(void) const { return _shader;}
void                    ARenderer::SetShader(std::shared_ptr<Shader>  shader) {_shader = shader;}

