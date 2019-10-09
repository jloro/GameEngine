#include "MeshRenderer.hpp"
#include "PrintGlm.hpp"
#include "gtc/matrix_transform.hpp"
#include <iostream>
#include "stb_image.h"
#include <cstdlib>
#include <time.h>
#include "glm.hpp"
#include <gtc/random.hpp>
#include "Engine.hpp"
#include <sstream>


MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, 
std::shared_ptr<Shader>  shader, std::shared_ptr<GameObject> obj, bool render) : ARenderer(shader, obj), _model(model), _render(render)
{
}

std::string printvec(glm::vec4 & vec)
{
	std::stringstream ss("");
	 ss << "x: " << vec.x << ", y: " << vec.y << ", z: " << vec.z << ", w: " << vec.w;
	 return ss.str();
}
std::string printMat(glm::mat4 mat)
{
	std::stringstream ss("");

	for (int i =0; i < 4; ++i)
	{
		ss << printvec(mat[i]) << std::endl;
	}
	return ss.str();
}
void        MeshRenderer::Draw(void) const
{
	if (_render)
	{
		if (_shader == nullptr)
		{
			std::cout << "MeshRenderer : Cannot Draw with whitout shader" << std::endl;
			return;
		}
		_transform->UpdateMatrix();
		_shader->use();
		_shader->setMat4("view", Camera::instance->GetMatView());
		_shader->setMat4("projection", Camera::instance->GetMatProj());
		_shader->setMat4("model", _transform->GetMatrix());
		_model->Draw(_shader);
	}
}

MeshRenderer::MeshRenderer(MeshRenderer const & src) : ARenderer(src._shader, src._gameObj)
{
	_model = src._model;
}

MeshRenderer::~MeshRenderer(void) {}

MeshRenderer &	MeshRenderer::operator=(MeshRenderer const & rhs)
{
    this->_model = rhs._model;
    this->_shader = rhs._shader;
	this->SetGameObject(rhs._gameObj);
    return *this;
}

void MeshRenderer::Destroy(void)
{
	Engine42::Engine::Destroy(this);
}

bool				MeshRenderer::IsRender() const { return _render; }
void				MeshRenderer::SetRender(bool render) { _render = render; }
