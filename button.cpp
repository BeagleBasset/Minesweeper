#include "button.hpp"

Button::Button(std::string buttonname, Vector2 position)
{
	ButtonName = buttonname;
	ButtonPosition = position;
	ButtonRectangle = {ButtonPosition.x, ButtonPosition.y,(float)ButtonWidth, (float)ButtonHeight};
}

void Button::DrawButton()
{
	const char* text = ButtonName.c_str();
	DrawRectangle(ButtonPosition.x, ButtonPosition.y, ButtonWidth, ButtonHeight, CurrentButtonColor);
	DrawText(text, ButtonPosition.x + 5, ButtonPosition.y + 15, CharacterHeight, CurrentFontColor);
}

bool Button::UpdateButton()
{
	Vector2 mouseposition = GetMousePosition();
	if (CheckCollisionPointRec(mouseposition, ButtonRectangle)) {
		CurrentButtonColor = HoverButtonColor;
		CurrentFontColor = HoverFontColor;
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			return true;
	}
	else {
		CurrentButtonColor = NormalButtonColor;
		CurrentFontColor = NormalFontColor;
		return false;
	}



}

void Button::SetPosition(Vector2 newpos)
{
	ButtonPosition = newpos;
	ButtonRectangle = { ButtonPosition.x, ButtonPosition.y,(float)ButtonWidth, (float)ButtonHeight };
}


