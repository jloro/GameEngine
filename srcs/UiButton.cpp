#include "UiButton.hpp"
#include "SdlWindow.hpp"
#include "Engine.hpp"

UiButton::UiButton(glm::vec2 pos, glm::vec2 scale, std::string text, glm::vec4 color, void (*OnClick)()) : pos(pos), scale(scale), color(color), OnClick(OnClick)
{
	_proj = glm::ortho(0.0f, (float)SdlWindow::GetMain()->GetWidth(), 0.0f, (float)SdlWindow::GetMain()->GetHeight());
	std::vector<const char *>	shadersPath{"shaders/Color.vs.glsl", "shaders/Color.fs.glsl"};
	std::vector<GLenum> type{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

	_shader = std::make_shared<Shader>(shadersPath, type);

	glm::vec2 textPos = glm::vec2(pos.x, pos.y - Engine42::Engine::GetFontUI()->GetPixelSize() / 2.0f);
	_text = std::make_shared<UiText>(text, textPos, 1.0f, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	float x = 0.10f * (float)SdlWindow::GetMain()->GetWidth();
	float y = 0.10f * (float)SdlWindow::GetMain()->GetHeight();
	_vertices = {
		x * scale.x + pos.x, y * scale.y + pos.y, 
		x * scale.x + pos.x, -y * scale.y + pos.y, 
		-x * scale.x + pos.x, -y * scale.y + pos.y,
		-x * scale.x + pos.x, y * scale.y + pos.y,
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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

UiButton::~UiButton() {}

void	UiButton::Draw() const
{
	_shader->use();
	_shader->setVec4("color", color);
	_shader->setMat4("projection", _proj);

	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _faces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	_text->Draw();
}

glm::vec4		UiButton::GetMinMax() const
{
	return glm::vec4(_vertices[4], _vertices[0], _vertices[3], _vertices[1]);
}