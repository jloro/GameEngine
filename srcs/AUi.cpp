#include "AUi.hpp"

AUi::AUi(void) : _clicked(false)
{

}

AUi::~AUi() {}

void	AUi::OnClick()
{
	_clicked = true;
}

void	AUi::OnRelease()
{
	_clicked = false;
}

bool	AUi::GetClicked() const { return _clicked; }
