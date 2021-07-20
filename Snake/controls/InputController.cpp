#include "stdafx.h"
#include "InputController.h"
#include "GameConfig.h"

int game::InputController::inputKey()
{
	int key = _getch();
	return key;
}
