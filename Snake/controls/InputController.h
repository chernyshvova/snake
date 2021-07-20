#pragma once

namespace game
{
	class InputController
	{
	public:
		MoveDirection inputKey();
	private:
		MoveDirection parseInputKey(const int key);
	};
}