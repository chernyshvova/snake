#include "stdafx.h"
#include "SnakeObject.h"
#include "SnakeNodeHead.h"

game::SnakeObject::SnakeObject(Point startPos)
	: m_headPos(startPos)
{
	m_nodes.push_back(std::make_shared<SnakeNodeHead>(m_headPos, MoveDirection::Right));
}

std::vector<game::Point> game::SnakeObject::getPosition()
{
	std::vector<Point> result;

	for (auto node : m_nodes)
	{
		result.push_back(node->getPos());
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

	updatePosition();
	m_nodes.push_front(std::make_shared<SnakeNode>(lastPos, lastDirection, lastNode));
}
