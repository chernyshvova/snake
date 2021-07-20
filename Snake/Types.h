#pragma once

namespace game
{
	struct Point
	{
		int x;
		int y;
	};

	enum class MoveDirection
	{
		None = 0,
		Top,
		Down,
		Right,
		Left
	};
}