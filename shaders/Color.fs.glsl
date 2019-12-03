#version 330 core

uniform vec4		color;
uniform sampler2D	tex;
uniform int			uHasImage;

out vec4 FragColor;
in vec2 TexCoords;

void main()
{
	vec4 retColor = color;
	vec4 retTexture = color * texture(tex, TexCoords);

	float stepVal = step(uHasImage, 0);
	FragColor =  stepVal * retColor + (1 - stepVal) * retTexture;
}
