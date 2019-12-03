#version 330 core

uniform sampler2D	tex;
uniform vec4		color;
uniform float		smoothing;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	float dist = texture(tex, TexCoord).r;
	float alpha = smoothstep(0.5 - smoothing, 0.5 + smoothing, dist);
	FragColor = color * vec4(1.0, 1.0, 1.0, alpha);
}
