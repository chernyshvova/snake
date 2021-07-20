#include "stdafx.h"
#include "SnakeNodeHead.h"

game::SnakeNodeHead::SnakeNodeHead(const Point pos, MoveDirection direction)
{
	m_pos = pos;
	m_moveDirection = direction;
}

void game::SnakeNodeHead::updateDirection(MoveDirection direction)
{
	if (direction == MoveDirection::None)
	{
		direction = MoveDirection::Right;
	}

	if (direction == MoveDirection::Down && m_moveDirection == MoveDirection::Top
		|| direction == MoveDirection::Left && m_moveDirection == MoveDirection::Right
		|| direction == MoveDirection::Right && m_moveDirection == MoveDirection::Left
		|| direction == MoveDirection::Top && m_moveDirection == MoveDirection::Down)
	{
		return;
	}

	m_moveDirection = direction;
}

void game::SnakeNodeHead::updatePosition()
{
	m_pos = resolveNextPos();
}

game::Point game::SnakeNodeHead::getNextPos()
{
	return resolveNextPos();
}

game::Point game::SnakeNodeHead::resolveNextPos()
{
	Point nextPos = m_pos;
	switch (m_moveDirection)
	{
	case game::MoveDirection::Top:
		nextPos.y--;
		break;
	case game::MoveDirection::Down:
		nextPos.y++;
		break;
	case game::MoveDirection::Right:
		nextPos.x++;
		break;
	case game::MoveDirection::Left:
		nextPos.x--;
		break;
	default:
		throw new std::exception("failed to update snake position with wrong direction");
	}

	return nextPos;
}
