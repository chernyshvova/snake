#include "DrawController.h"
#include "stdafx.h"

void game::DrawController::draw(const std::string& map)
{
	std::cout << map;
}

void game::DrawController::clear()
{
	system("CLS");
}

void game::DrawController::setDiplayColor(const std::string&)
{
	setRedDisplay();
}

void game::DrawController::setRedDisplay()
{
	system("color 41");
}
