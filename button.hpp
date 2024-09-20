#pragma once
#include <raylib.h>
#include <string>
#include <iostream>

class Button
{
public:
	Button(std::string buttonname, Vector2 position);
	void DrawButton();
	bool UpdateButton();
	void SetPosition(Vector2 newpos);
private:
	std::string ButtonName;
	Vector2 ButtonPosition;
	Rectangle ButtonRectangle;
	int ButtonWidth{128};
	int ButtonHeight{64};
	int CharacterHeight{ 30 };
	Color NormalFontColor = WHITE;
	Color HoverFontColor = BLACK;
	Color CurrentFontColor = NormalFontColor;
	Color NormalButtonColor = DARKBLUE;
	Color HoverButtonColor = BLUE;
	Color CurrentButtonColor = NormalButtonColor;
};

