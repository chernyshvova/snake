#pragma once
#include "SnakeNode.h"

namespace game
{
	class SnakeObject
	{
	public:
		SnakeObject(Point startPos);
		std::vector<Point> getPosition();
		Point getHeadPos();
		void updateDirection(MoveDirection direction = MoveDirection::None);
		void updatePosition();
		Point getNextHeadPos();
		bool isSnakePos(Point pos);
		void addNode();

	private:
		std::list<std::shared_ptr<SnakeNodeBase>> m_nodes;
		Point m_headPos;
	};
}

