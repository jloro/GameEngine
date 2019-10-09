#include "Node.hpp"
#include "glad.h"

Node::Node(aiNode* root)
{
	name = root->mName.C_Str();
	transform = _aiMat4ToGlmMat4(root->mTransformation);
	numChildren = root->mNumChildren;

	for (unsigned int i = 0; i < numChildren; i++)
	{
		std::shared_ptr<Node>	child(new Node(root->mChildren[i]));
		children.push_back(child);
	}
}

Node::~Node() {}

glm::mat4	Node::_aiMat4ToGlmMat4(aiMatrix4x4 from)
{
	glm::mat4	to;

	to[0][0] = (GLfloat)from.a1; to[0][1] = (GLfloat)from.b1;  to[0][2] = (GLfloat)from.c1; to[0][3] = (GLfloat)from.d1;
	to[1][0] = (GLfloat)from.a2; to[1][1] = (GLfloat)from.b2;  to[1][2] = (GLfloat)from.c2; to[1][3] = (GLfloat)from.d2;
	to[2][0] = (GLfloat)from.a3; to[2][1] = (GLfloat)from.b3;  to[2][2] = (GLfloat)from.c3; to[2][3] = (GLfloat)from.d3;
	to[3][0] = (GLfloat)from.a4; to[3][1] = (GLfloat)from.b4;  to[3][2] = (GLfloat)from.c4; to[3][3] = (GLfloat)from.d4;
	return to;
}
