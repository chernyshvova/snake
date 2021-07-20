#include "stdafx.h"
#include "SnakeNodeBase.h"

game::MoveDirection game::SnakeNodeBase::getMoveDirection()
{
	return m_moveDirection;
}

game::Point game::SnakeNodeBase::getPos()
{
	return m_pos;
}
