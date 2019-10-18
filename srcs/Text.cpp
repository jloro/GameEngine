#include "Text.hpp"
#include "vector"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
# ifndef STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
# endif

Text::Text(const std::string font, int pixelSize) : _pixelSize(pixelSize)
{
	std::cout << font << std::endl;
	std::ifstream i("ressources/fonts/OpenSans-Regular/OpenSans-Regular.json");
	i >> _json;
	up = 0.25f;
	down = 5.0f;
	_proj = glm::ortho(0.0f, (float)SdlWindow::GetMain()->GetWidth(), 0.0f, (float)SdlWindow::GetMain()->GetHeight());
	std::vector<const char *>	shadersPath{"shaders/Text.vs.glsl", "shaders/Text.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	_shader.reset(new Shader(shadersPath, type));

	 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &_texture);

	int width, height, nrComponents;
	unsigned char *data = stbi_load("ressources/fonts/OpenSans-Regular/OpenSans-Regular.png", &width, &height, &nrComponents, 0);
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}

	for (auto it = _json["glyph_data"].begin(); it != _json["glyph_data"].end(); it++)
	{
		std::string str = it.key();
		if (_json["glyph_data"][str].is_null())
		{
			std::cout << "failed to load character " << str << std::endl;
			continue;
		}
		Character character = {
			glm::vec2(_json["glyph_data"][str]["bbox_width"].get<float>(), _json["glyph_data"][str]["bbox_height"].get<float>()),
			glm::vec2(_json["glyph_data"][str]["bearing_x"].get<float>(), _json["glyph_data"][str]["bearing_y"].get<float>()),
			_json["glyph_data"][str]["advance_x"].get<float>(),
			glm::vec4(_json["glyph_data"][str]["s0"].get<float>(), _json["glyph_data"][str]["s1"].get<float>(), _json["glyph_data"][str]["t0"].get<float>(), _json["glyph_data"][str]["t1"].get<float>())
		};

		_characters.insert(std::pair<GLchar, Character>(str[0], character));
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

Text::~Text() {}

void	Text::UpdateProj()
{
	_proj = glm::ortho(0.0f, (float)SdlWindow::GetMain()->GetWidth(), 0.0f, (float)SdlWindow::GetMain()->GetHeight());
}
#include "Engine.hpp"
void	Text::RenderText(const std::string text, float x, float y, float scale, glm::vec4 color)
{
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_W) == KEY_DOWN)
		up += 0.05f;
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_S) == KEY_DOWN)
		up -= 0.05f;
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_D) == KEY_DOWN)
		down += 0.05f;
	if (Engine42::Engine::GetKeyState(SDL_SCANCODE_A) == KEY_DOWN)
		down -= 0.05f;
//	std::cout << "up: " << up << ", down: " << down << ", smoothing: " << up / down << std::endl;
	GLfloat x2, y2, w, h;
	_shader->use();
	_shader->setFloat("smoothing", up / down);
	_shader->setVec4("color", color);
	_shader->setInt("tex", 0);
	_shader->setMat4("projection", _proj);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);
	for (std::string::const_iterator it = text.begin(); it != text.end(); it++)
	{
		std::cout << "ch: "<< *it << std::endl;
		Character ch = _characters[*it];

		x2 = x + ch.Bearing.x * scale;
		y2 = y - (ch.Size.y - ch.Bearing.y) * scale;
		w = ch.Size.x * scale;
		h = ch.Size.y * scale;

		std::cout << "x: "<<  x2<< ", y: " << y2<< ", w: " << w << ", h: " << h << std::endl;
		std::cout << "s0: " << ch.textureCoord.x << " s1: " << ch.textureCoord.y << " t0: " << ch.textureCoord.z  << "t1: " << ch.textureCoord.w << std::endl;
		GLfloat vertices[6][4] = {
			{ x2, y2 + h, ch.textureCoord.x, ch.textureCoord.w },//top-left
			{ x2 + w, y2 + h, ch.textureCoord.y, ch.textureCoord.w },//top-right
			{ x2, y2, ch.textureCoord.x, ch.textureCoord.z },//bottom-left

			{ x2 + w, y2 + h, ch.textureCoord.y, ch.textureCoord.w },//top-right
			{ x2 + w, y2, ch.textureCoord.y, ch.textureCoord.z },//bottom-right
			{ x2, y2, ch.textureCoord.x, ch.textureCoord.z }//bottom-left
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

int	Text::GetPixelSize(void) const { return _pixelSize; }

int	Text::GetTextWidth(std::string text, float scale)
{
	int w = 0;
	for (auto it = text.begin(); it != text.end(); it++)
	{
		Character ch = _characters[*it];
		w += ch.Bearing.x * scale + ch.Size.x * scale;
	}
	return w;
}
