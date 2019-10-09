#include "BoxCollider.hpp"
#include "ARenderer.hpp"
#include "Engine.hpp"
#include "BoxColliderRenderer.hpp"
#include "gtx/rotate_vector.hpp"
#include <climits>
BoxCollider::BoxCollider(GameObject *obj, glm::vec3 min, glm::vec3 max, glm::vec3 scale, glm::vec3 offset, bool showMesh) : ACollider(obj)
{
	this->scale = scale;
	size = max - min; 
	center = (min + size / 2.0f) + offset;
	if (showMesh)
	{
		std::shared_ptr<ARenderer> renderer(new BoxColliderRenderer(obj, this));
		obj->AddComponent(renderer);
		Engine42::Engine::AddRenderer(renderer);
	}
}

BoxCollider::~BoxCollider(void)
{
}

glm::vec3	rotate(glm::vec3 vec, glm::vec3 angle)
{
	vec = glm::rotateX(vec, glm::radians(angle.x));
	vec = glm::rotateY(vec, glm::radians(angle.y));
	vec = glm::rotateZ(vec, glm::radians(angle.z));
	return vec;
}

bool		CheckOverlap(float min, float max, float value)
{
	return (value >= min && value <= max);
}

void		SatTest(std::vector<glm::vec3> vertices, float & min, float & max, glm::vec3 axis, glm::vec3 center)
{
	glm::vec3 a = center + axis;
	glm::vec3 b = center - axis;
	for (auto p = vertices.begin(); p != vertices.end(); p++)
	{
		glm::vec3 ap = *p - a;
		glm::vec3 ab = b - a;
		float t = glm::dot(a + (glm::dot(ap, ab) / glm::dot(ab, ab) * ab), axis);
		if (t < min)
			min = t;
		if (t > max)
			max = t;
	}
}

bool	Intersect(glm::vec3 rot, std::vector<glm::vec3> vertices, std::vector<glm::vec3> otherVertices, glm::vec3 center)
{
	std::vector<glm::vec3>	normals = {
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
	};
	for (auto it = normals.begin(); it != normals.end(); it++)
	{
		float projMin = std::numeric_limits<int>::max();
		float projMax = std::numeric_limits<int>::min();
		float otherProjMin = std::numeric_limits<int>::max();
		float otherProjMax = std::numeric_limits<int>::min();
		(*it) = rotate((*it), rot);
		SatTest(vertices, projMin, projMax, *it, center);
		SatTest(otherVertices, otherProjMin, otherProjMax, *it, center);
		if (!(CheckOverlap(projMin, projMax, otherProjMin) || CheckOverlap(otherProjMin, otherProjMax, projMin)))
			return false;
	}
	return true;
}

bool BoxCollider::IsCollindingWith(ACollider &other) const
{
	glm::vec3 min = glm::vec3(center - size / 2.0f);
	glm::vec3 max = glm::vec3(center + size / 2.0f);

	glm::vec3 otherMin = glm::vec3(other.center - other.size / 2.0f);
	glm::vec3 otherMax = glm::vec3(other.center + other.size / 2.0f);

	glm::vec3 centerWorldPos = center * _transform->GetWorldScale() * this->scale + _transform->GetWorldPos();
	glm::vec3 otherCenterWorldPos = other.center * other.GetTransform()->GetWorldScale() * other.scale + other.GetTransform()->GetWorldPos();
	
	std::vector<glm::vec3>	vertices = {
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(min.x, max.y, max.z),
		glm::vec3(max.x, max.y, max.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(max.x, max.y, min.z),
		glm::vec3(min.x, min.y, min.z),
		glm::vec3(max.x, min.y, min.z)
	};
	std::vector<glm::vec3>	otherVertices = {
		glm::vec3(otherMin.x, otherMin.y, otherMax.z),
		glm::vec3(otherMax.x, otherMin.y, otherMax.z),
		glm::vec3(otherMin.x, otherMax.y, otherMax.z),
		glm::vec3(otherMax.x, otherMax.y, otherMax.z),
		glm::vec3(otherMin.x, otherMax.y, otherMin.z),
		glm::vec3(otherMax.x, otherMax.y, otherMin.z),
		glm::vec3(otherMin.x, otherMin.y, otherMin.z),
		glm::vec3(otherMax.x, otherMin.y, otherMin.z)
	};
	for (auto p = vertices.begin(); p != vertices.end(); p++)
		(*p) = glm::vec3(glm::scale(_transform->GetMatrix(), this->scale) * glm::vec4((*p), 1.0f));
	for (auto p = otherVertices.begin(); p != otherVertices.end(); p++)
		(*p) = glm::vec3(glm::scale(other.GetTransform()->GetMatrix(), other.scale) * glm::vec4((*p), 1.0f));
	return (Intersect(_transform->rotation, vertices, otherVertices, centerWorldPos) && Intersect(other.GetTransform()->rotation, vertices, otherVertices, otherCenterWorldPos));
}
