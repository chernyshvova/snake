#pragma once
#include "SnakeNodeBase.h"

namespace game
{
	class SnakeNodeHead : public SnakeNodeBase
	{
	public:
		SnakeNodeHead(const Point pos, MoveDirection direction);
		virtual void updateDirection(MoveDirection direction) override;
		virtual void updatePosition() override;
		virtual Point getNextPos() override;

	protected:
		Point resolveNextPos();
	};
}


