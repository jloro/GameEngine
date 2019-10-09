#include "Text.hpp"
#include "vector"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include <iostream>

Text::Text(const std::string font, FT_Library lib, int pixelSize) : _pixelSize(pixelSize)
{
	if (FT_New_Face(lib, font.c_str(), 0, &_face))
		throw std::runtime_error(std::string("Could not open font ") + font);
	_proj = glm::ortho(0.0f, (float)SdlWindow::GetMain()->GetWidth(), 0.0f, (float)SdlWindow::GetMain()->GetHeight());
	FT_Set_Pixel_Sizes(_face, 0, pixelSize);
	std::vector<const char *>	shadersPath{"shaders/Text.vs.glsl", "shaders/Text.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};
	_shader.reset(new Shader(shadersPath, type));

	 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0;c < 128; c++)
	{
		if (FT_Load_Char(_face, c, FT_LOAD_RENDER))
		{
			std::cout << "failed to load character " << c << std::endl;
			continue;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _face->glyph->bitmap.width, _face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, _face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {
			texture,
			glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
			glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
			static_cast<GLuint>(_face->glyph->advance.x)
		};

		_characters.insert(std::pair<GLchar, Character>(c, character));
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

void	Text::RenderText(const std::string text, float x, float y, float scale, glm::vec4 color)
{
	GLfloat x2, y2, w, h;
	_shader->use();
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
			{ x2, y2 + h, 0.0, 0.0 },
			{ x2, y2, 0.0, 1.0 },
			{ x2 + w, y2, 1.0, 1.0 },

			{ x2, y2 + h, 0.0, 0.0 },
			{ x2 + w, y2, 1.0, 1.0 },
			{ x2 + w, y2 + h, 1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, vertices, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int	Text::GetPixelSize(void) const { return _pixelSize; }
