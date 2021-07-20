#pragma once
#include "SnakeNodeBase.h"

namespace game
{
	//part of snake tail. Has next node for position changing
	class SnakeNode : public SnakeNodeBase
	{
	public:
		SnakeNode(const Point pos, MoveDirection direction, SnakeNodeBasePtr nextNode);
		virtual void updateDirection(MoveDirection direction = MoveDirection::None) override;
		virtual void updatePosition() override;
		virtual Point getNextPos() override;

	protected:
		SnakeNodeBasePtr m_nextNode;
	};
}
