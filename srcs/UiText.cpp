#include "UiText.hpp"
#include "SdlWindow.hpp"
#include "Engine.hpp"

UiText::UiText(std::string text, glm::vec2 pos, float scale, glm::vec4 color) : text(text), pos(pos), scale(scale), color(color)
{

}

UiText::UiText(void)
{
	text = "Text";
	pos = glm::vec2(0.0f, SdlWindow::GetMain()->GetHeight() - Engine42::Engine::GetFontUI()->GetPixelSize());
	scale = 1.0f;
	color = glm::vec4(1.0f);
}

UiText::~UiText()
{
}

void	UiText::Draw() const
{
	Engine42::Engine::GetFontUI()->RenderText(text, pos.x, pos.y, scale, color); 
}
