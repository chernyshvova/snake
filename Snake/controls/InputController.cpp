#include "stdafx.h"
#include "InputController.h"
#include "GameConfig.h"

game::MoveDirection game::InputController::inputKey()
{
	int key = _getch();
	return parseInputKey(key);
}

game::MoveDirection game::InputController::parseInputKey(const int key)
{
	switch (key)
	{
	case config::INPUT_KEY_DOWN:
	case config::INPUT_KEY_DOWN_ALTERNATIVE:
		return MoveDirection::Down;
	case config::INPUT_KEY_TOP:
	case config::INPUT_KEY_TOP_ALTERNATIVE:
		return MoveDirection::Top;
	case config::INPUT_KEY_LEFT:
	case config::INPUT_KEY_LEFT_ALTERNATIVE:
		return MoveDirection::Left;
	case config::INPUT_KEY_RIGHT:
	case config::INPUT_KEY_RIGHT_ALTERNATIVE:
		return MoveDirection::Right;

	default:
		return MoveDirection::None;
	}
}
