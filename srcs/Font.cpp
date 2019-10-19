#include "Font.hpp"
#include "vector"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
# ifndef STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
# endif

Font::Font(const std::string font, int pixelSize) : _pixelSize(pixelSize)
{
	std::ifstream	ifs("ressources/fonts/"+font+"/"+font+".txt");
	if (!ifs.is_open())
		throw std::runtime_error(std::string("Error while opening file: ") + font);
	_proj = glm::ortho(0.0f, (float)SdlWindow::GetMain()->GetWidth(), 0.0f, (float)SdlWindow::GetMain()->GetHeight());
	std::vector<const char *>	shadersPath{"shaders/Text.vs.glsl", "shaders/Text.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	_shader.reset(new Shader(shadersPath, type));

	glGenTextures(1, &_texture);

	int width, height, nrComponents;
	std::string path("ressources/fonts/"+font+"/"+font+".png");
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, _texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		stbi_image_free(data);
		throw std::runtime_error(std::string("Error while opening file: ") + path);
	}

	std::string	line;
	float infos[8];
	while (std::getline(ifs, line))
	{
		if (line.find("count") !=std::string::npos || line.find("face") !=std::string::npos)
			continue;
		sscanf(line.c_str(), "char id=%f	x=%f	y=%f	width=%f	height=%f	xoffset=%f	yoffset=%f	xadvance=%f", &infos[0], &infos[1], &infos[2], &infos[3], &infos[4], &infos[5], &infos[6], &infos[7]);

		Character character = {
			glm::vec2(infos[3], infos[4]),
			glm::vec2(infos[5], infos[6]),
			infos[7],
			glm::vec4(infos[1] / static_cast<float>(width), (infos[1] + infos[3]) / static_cast<float>(width), (infos[2] + infos[4]) / static_cast<float>(width), infos[2] / static_cast<float>(width))
		};
		_characters.insert(std::pair<GLchar, Character>(static_cast<char>(infos[0]), character));
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &_vbo);
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Font::~Font() {}

void	Font::UpdateProj()
{
	_proj = glm::ortho(0.0f, (float)SdlWindow::GetMain()->GetWidth(), 0.0f, (float)SdlWindow::GetMain()->GetHeight());
}

void	Font::RenderText(const std::string text, float x, float y, float scale, glm::vec4 color)
{
	GLfloat x2, y2, w, h;
	_shader->use();
	_shader->setFloat("smoothing", 0.1f / scale);
	_shader->setVec4("color", color);
	_shader->setInt("tex", 0);
	_shader->setMat4("projection", _proj);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);
	for (std::string::const_iterator it = text.begin(); it != text.end(); it++)
	{
		Character ch = _characters[*it];

		x2 = x + ch.Bearing.x * scale;
		y2 = y - (ch.Size.y - ch.Bearing.y) * scale;
		w = ch.Size.x * scale;
		h = ch.Size.y * scale;

		GLfloat vertices[6][4] = {
			{ x2, y2 + h, ch.textureCoord.x, ch.textureCoord.w},//top-left
			{ x2 + w, y2 + h, ch.textureCoord.y, ch.textureCoord.w},//top-right
			{ x2, y2, ch.textureCoord.x, ch.textureCoord.z},//bottom-left

			{ x2 + w, y2 + h, ch.textureCoord.y, ch.textureCoord.w},//top-right
			{ x2 + w, y2, ch.textureCoord.y, ch.textureCoord.z},//bottom-right
			{ x2, y2, ch.textureCoord.x, ch.textureCoord.z}//bottom-left
		};
		glBindTexture(GL_TEXTURE_2D, _texture);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += ch.Advance* scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int	Font::GetPixelSize(void) const { return _pixelSize; }

int	Font::GetTextWidth(std::string text, float scale)
{
	int w = 0;
	for (auto it = text.begin(); it != text.end(); it++)
	{
		Character ch = _characters[*it];
		w += ch.Bearing.x * scale + ch.Size.x * scale;
	}
	return w;
}
