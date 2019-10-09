#include "NodeAnim.hpp"
#include "glad.h"

NodeAnim::NodeAnim(aiNodeAnim* infos)
{
	numPositionKeys = infos->mNumPositionKeys;
	numRotationKeys = infos->mNumRotationKeys;
	numScalingKeys = infos->mNumScalingKeys;

	nodeName = infos->mNodeName.C_Str();

	for (unsigned int i = 0; i < numPositionKeys; i++)
	{
		vectorKey	key;
		key.time = infos->mPositionKeys[i].mTime;
		key.value = glm::vec3(infos->mPositionKeys[i].mValue.x, infos->mPositionKeys[i].mValue.y, infos->mPositionKeys[i].mValue.z);

		positionKeys.push_back(key);
	}
	for (unsigned int i = 0; i < numScalingKeys; i++)
	{
		vectorKey	key;
		key.time = infos->mScalingKeys[i].mTime;
		key.value = glm::vec3(infos->mScalingKeys[i].mValue.x, infos->mScalingKeys[i].mValue.y, infos->mScalingKeys[i].mValue.z);

		scalingKeys.push_back(key);
	}
	for (unsigned int i = 0; i < numRotationKeys; i++)
	{
		quatKey	key;
		key.time = infos->mRotationKeys[i].mTime;
		key.value = glm::quat(infos->mRotationKeys[i].mValue.w, infos->mRotationKeys[i].mValue.x, infos->mRotationKeys[i].mValue.y, infos->mRotationKeys[i].mValue.z);
		rotationKeys.push_back(key);
	}
}

glm::mat3	NodeAnim::_aiMat3ToGlmMat3(aiMatrix3x3 from)
{
	glm::mat3	to;

	to[0][0] = (GLfloat)from.a1; to[0][1] = (GLfloat)from.b1;  to[0][2] = (GLfloat)from.c1;
	to[1][0] = (GLfloat)from.a2; to[1][1] = (GLfloat)from.b2;  to[1][2] = (GLfloat)from.c2;
	to[2][0] = (GLfloat)from.a3; to[2][1] = (GLfloat)from.b3;  to[2][2] = (GLfloat)from.c3;
	return to;
}

NodeAnim::~NodeAnim() {}
