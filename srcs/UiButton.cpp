#include "UiButton.hpp"
#include "SdlWindow.hpp"
#include "Engine.hpp"

UiButton::UiButton(glm::vec2 pos, float width, float height, std::string text, glm::vec4 color, void (*OnClickEvent)()) : pos(pos), color(color), OnClickEvent(OnClickEvent), _hasImage(false), _width(width), _height(height)
{
	displayText = true;
	_Init(text);
}

UiButton::UiButton(glm::vec2 pos, float width, float height, std::string text, const std::string path, void (*OnClickEvent)()) : pos(pos), color(glm::vec4(1.0f)), OnClickEvent(OnClickEvent), _hasImage(true), _width(width), _height(height)
{
	displayText = false;
	_Init(text, path);
}


void	UiButton::_Init(std::string text, const std::string path)
{
	float screenWidth = (float)SdlWindow::GetMain()->GetWidth();
	float screenHeight = (float)SdlWindow::GetMain()->GetHeight();
	_proj = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight);
	std::vector<const char *>	shadersPath{"shaders/Color.vs.glsl", "shaders/Color.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	_shader = std::make_shared<Shader>(shadersPath, type);

	glm::vec2 textPos = glm::vec2(pos.x, pos.y);

	this->text = std::make_shared<UiText>(text, textPos, 0.5f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	float x = _width / 2.0f;
	float y = _height / 2.0f;
	_vertices = {
		x + pos.x + screenWidth / 2.0f, y + pos.y + screenHeight / 2.0f, 1.0f, 0.0f,
		x + pos.x + screenWidth / 2.0f, -y + pos.y + screenHeight / 2.0f, 1.0f, 1.0f,
		-x + pos.x + screenWidth / 2.0f, -y + pos.y + screenHeight / 2.0f, 0.0f, 1.0f,
		-x + pos.x + screenWidth / 2.0f, y + pos.y + screenHeight / 2.0f, 0.0f, 0.0f
	};
	_faces = {
		0, 1, 3,
		1, 2, 3
	};
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _faces.size(), &_faces[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	if (_hasImage)
	{

		glGenTextures(1, &_textureId);

		int width, height, nrComponents;
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

			glBindTexture(GL_TEXTURE_2D, _textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			stbi_image_free(data);
		}
		else
		{
			throw std::runtime_error(std::string("failed to load texture ") + path);
			stbi_image_free(data);
		}
	}
}
UiButton::~UiButton() {}

void	UiButton::Draw() const
{
	_shader->use();
	_shader->SetVec4("color", color);
	_shader->SetMat4("projection", _proj);
	_shader->SetInt("uHasImage", static_cast<int>(_hasImage));
	_shader->SetInt("tex", 0);
	glBindVertexArray(_vao);
	if (_hasImage)
		glBindTexture(GL_TEXTURE_2D, _textureId);
	glDrawElements(GL_TRIANGLES, _faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	if (displayText)
		text->Draw();
}

glm::vec4		UiButton::GetMinMax() const
{
	return glm::vec4(_vertices[8], _vertices[0], _vertices[5], _vertices[1]);
}

void	UiButton::OnClick()
{
	AUi::OnClick();
	color = glm::vec4(color.x - 0.1, color.y - 0.1, color.z - 0.1, color.w);
	OnClickEvent();
}

void	UiButton::OnRelease()
{
	AUi::OnRelease();
	color = glm::vec4(color.x + 0.1, color.y + 0.1, color.z + 0.1, color.w);
	if (OnReleaseEvent != nullptr)
		OnReleaseEvent();
}

void	UiButton::Resize()
{
}

float	UiButton::GetWidth() const { return _width; }
float	UiButton::GetHeight() const { return _height; }
