#version 330 core

layout (location = 0) in vec4 aPos;

uniform mat4 projection;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * vec4(aPos.xy, 0, 1);
	TexCoord = aPos.zw;
}
