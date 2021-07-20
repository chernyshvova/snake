#pragma once
#include "SnakeNodeBase.h"

namespace game
{
	//Snake head. Hasn't next node but get new position using his own move direction
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


