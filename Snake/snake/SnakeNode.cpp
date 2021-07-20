#include "stdafx.h"
#include "SnakeNode.h"

game::SnakeNode::SnakeNode(const Point pos, MoveDirection direction, SnakeNodeBasePtr nextNode)
	: m_nextNode(nextNode)
{
	m_pos = pos;
	m_moveDirection = direction;
}


void game::SnakeNode::updateDirection(MoveDirection)
{
	m_moveDirection = m_nextNode->getMoveDirection();
}

void game::SnakeNode::updatePosition()
{
	m_pos = m_nextNode->getPos();
	updateDirection();
}

game::Point game::SnakeNode::getNextPos()
{
	return m_nextNode->getPos();
}
