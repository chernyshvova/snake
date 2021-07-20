#pragma once
#include "stdafx.h"

namespace game
{
	//base node for base functionality
	class SnakeNodeBase
	{
	public:
		virtual void updateDirection(MoveDirection direction) = 0;
		virtual void updatePosition() = 0;
		virtual Point getNextPos() = 0;
		MoveDirection getMoveDirection();
		Point getPos();

	protected:
		Point m_pos;
		MoveDirection m_moveDirection;
	};

	using SnakeNodeBasePtr = std::shared_ptr<SnakeNodeBase>;
}