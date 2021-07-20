#include "stdafx.h"
#include "InputController.h"
#include "GameConfig.h"

//Keyboard reading implementation
int game::InputController::inputKey()
{
	int key = _getch();
	return key;
}
