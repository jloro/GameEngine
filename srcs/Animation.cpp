#include "Animation.hpp"

Animation::Animation(aiAnimation* anim)
{
	numChannels = anim->mNumChannels;
	ticksPerSecond = anim->mTicksPerSecond;
	name = anim->mName.C_Str();
	duration = anim->mDuration;

	for (unsigned int i = 0; i < numChannels; i++)
	{
		std::shared_ptr<NodeAnim> node(new NodeAnim(anim->mChannels[i]));
		channels.push_back(node);
	}
}

Animation::~Animation() {}
