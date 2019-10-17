#include "UiText.hpp"
#include "SdlWindow.hpp"
#include "Engine.hpp"

UiText::UiText(std::string text, glm::vec2 pos, float scale, glm::vec4 color) : pos(pos), color(color), _text(text), _scale(scale)
{
	_width = Engine42::Engine::GetFontUI()->GetTextWidth(_text, _scale);
}

UiText::UiText(void)
{
	_text = "Text";
	pos = glm::vec2(0.0f, SdlWindow::GetMain()->GetHeight() - Engine42::Engine::GetFontUI()->GetPixelSize());
	_scale = 1.0f;
	color = glm::vec4(1.0f);
	Engine42::Engine::GetFontUI()->GetTextWidth(_text, _scale);
}

UiText::~UiText()
{
}

void	UiText::Draw() const
{
	Engine42::Engine::GetFontUI()->RenderText(_text, pos.x - _width / 2.0f, pos.y - Engine42::Engine::GetFontUI()->GetPixelSize() / 2.0f, _scale, color); 
}

void	UiText::OnClick()
{
	AUi::OnClick();
}

void	UiText::OnRelease()
{
	AUi::OnRelease();
}

glm::vec4	UiText::GetMinMax() const { return glm::vec4(1.0f); }

std::string		UiText::GetText() const { return _text; }
float			UiText::GetScale() const { return _scale; }
int				UiText::GetWidthText() const { return Engine42::Engine::GetFontUI()->GetTextWidth(_text, _scale); }
void			UiText::SetText(std::string text)
{
	_text = text;
	_width = Engine42::Engine::GetFontUI()->GetTextWidth(_text, _scale);
}
void			UiText::SetScale(float scale)
{
	_scale = scale;
	_width = Engine42::Engine::GetFontUI()->GetTextWidth(_text, _scale);
}

