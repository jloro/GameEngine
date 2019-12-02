#include "BoxColliderRenderer.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"

BoxColliderRenderer::BoxColliderRenderer(GameObject* obj, BoxCollider* collider) : ARenderer(obj), _collider(collider)
{
	glm::vec3 min = _collider->center - _collider->size / 2.0f;;
	glm::vec3 max = _collider->center + _collider->size / 2.0f;;
	std::vector<float>	vertices = {
		min.x, min.y, max.z,
		max.x, min.y, max.z,
		min.x, max.y, max.z,
		max.x, max.y, max.z,
		min.x, max.y, min.z,
		max.x, max.y, min.z,
		min.x, min.y, min.z,
		max.x, min.y, min.z
	};
	std::vector<unsigned int> faces {
		0, 1, 2,
		2, 1, 3,
		2, 3, 4,
		4, 3, 5,
		4, 5, 6,
		6, 5, 7,
		6, 7, 0,
		0, 7, 1,
		1, 7, 3,
		3, 7, 5,
		6, 0, 4,
		4, 0, 2
	};
	std::vector<const char *>	shadersPath{ "shaders/Vertex.vs.glsl", "shaders/Assimp.fs.glsl"};
	std::vector<GLenum>			type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	_shader = std::make_shared<Shader>(shadersPath, type);
	std::vector<Vertex> finalVertices;
	for (int i = 0; i < 8; i++)
	{
		Vertex v;
		v.position = glm::vec3(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
		finalVertices.push_back(v);
	}
	Material mat;
	mat.SetDiffuse(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	mat.SetAmbient(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
	_mesh = std::make_shared<Mesh>(finalVertices, faces, mat);
	_mesh->SendToOpenGL();
}

BoxColliderRenderer::~BoxColliderRenderer() {}

void	BoxColliderRenderer::Draw() const
{
	if (_gameObj->GetComponent<MeshRenderer>()->IsRender())
	{
		_shader->use();
		_shader->setMat4("view", Camera::Instance()->GetMatView());
		_shader->setMat4("projection", Camera::Instance()->GetMatProj());
		_shader->setMat4("model", glm::scale(_transform->GetMatrix(), _collider->scale));
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		_mesh->Draw(_shader);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}
