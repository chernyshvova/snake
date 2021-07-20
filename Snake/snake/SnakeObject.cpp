#include "stdafx.h"
#include "SnakeObject.h"
#include "SnakeNodeHead.h"

game::SnakeObject::SnakeObject(Point startPos)
	: m_headPos(startPos)
{
	m_nodes.push_back(std::make_shared<SnakeNodeHead>(m_headPos, MoveDirection::Right));
}

std::vector<game::SnakeNodeBasePtr> game::SnakeObject::getTail()
{
	std::vector<game::SnakeNodeBasePtr> result;

	for (auto node : m_nodes)
	{
		if (node != m_nodes.back())
		{
			result.push_back(node);
		}
	}

	return result;
}

game::Point game::SnakeObject::getHeadPos()
{
	return m_nodes.back()->getPos();
}

void game::SnakeObject::updateDirection(MoveDirection direction)
{
	for (auto node : m_nodes)
	{
		node->updateDirection(direction);
	}
}

void game::SnakeObject::updatePosition()
{
	for (auto node : m_nodes)
	{
		node->updatePosition();
	}
}

game::Point game::SnakeObject::getNextHeadPos()
{
	return m_nodes.back()->getNextPos();
}

bool game::SnakeObject::isSnakePos(Point pos)
{
	for (auto node : m_nodes)
	{
		if (node->getPos().x == pos.x && node->getPos().y == pos.y)
		{
			return true;
		}
	}

	return false;
}

void game::SnakeObject::addNode()
{
	auto lastNode = m_nodes.front();
	auto lastPos = lastNode->getPos();
	auto lastDirection = lastNode->getMoveDirection();

	m_nodes.push_front(std::make_shared<SnakeNode>(lastPos, lastDirection, lastNode));
}

game::MoveDirection game::SnakeObject::getHeadDirection()
{
	return m_nodes.back()->getMoveDirection();
}
