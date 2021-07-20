#include "stdafx.h"
#include "DisplayMap.h"
#include "ContentConstructorUtils.h"
#include "GameConfig.h"

namespace
{
	//Merge two elemets with same size. It function can be using for merging several walls textures or UI elements
	game::DisplayElementMap mergeElements(const game::DisplayElementMap& left, const game::DisplayElementMap right)
	{
		std::string emptyLine = std::string(left.begin()->size(), ' ');
		game::DisplayElementMap merged(left.size(), emptyLine);

		if (left.size() != right.size())
		{
			throw new std::exception("failed to merge two map elements with different sizes");
		}

		for (int i = 0; i < left.size(); i++)
		{
			for (int j = 0; j < left.cbegin()->size(); ++j)
			{
				if (left[i][j] != merged[i][j])
				{
					merged[i][j] = left[i][j];
				}

				if (right[i][j] != merged[i][j])
				{
					merged[i][j] = right[i][j];
				}
			}
		}

		return merged;
	}

	//Converting array of strings to strings display
	std::string convertMapToString(const game::DisplayElementMap& map)
	{
		std::string result = {};
		
		for (int i = 0; i < map.size(); ++i)
		{
			std::string newLine = map[i].c_str();
			result += newLine + '\n';
		}

		return result;
	}

	//random for bonus
	int getRandomPoint(const int min, const int max)
	{
		srand((unsigned int)time(NULL));
		auto res =  rand() % max + min;
		return res;
	}
}

game::DisplayMap::DisplayMap(const Point snakeStartPosition)
	: m_maxWidht(config::MAX_MAP_WIDTH)
	, m_maxHeight(config::MAX_MAP_HEIGHT)
	, m_score(0)
	, m_snake(snakeStartPosition)
{
	m_border = createBorderMap(m_maxWidht, m_maxHeight);
	spawnBonus();
}

//snake makes move without drawing
void game::DisplayMap::update()
{
	m_snake.updatePosition();
}

void game::DisplayMap::increaseScore()
{
	m_score++;
	m_snake.addNode();
}

//prepare actual string for drawing.
std::string game::DisplayMap::build()
{
	std::string emptyLine = std::string(m_maxWidht, config::MAP_EMPTY_SYMB);
	DisplayElementMap mergedElements(m_maxHeight, emptyLine);
	
	//Empty map with borders(walls)
	mergedElements = mergeElements(mergedElements, m_border);

	//add string with score
	mergedElements[3] += config::SCORE_LABEL + std::to_string(m_score);

	//add tail and snake head
	for (auto node : m_snake.getTail())
	{
		setObjectToMap(mergedElements, node->getPos(), config::SNAKE_BODY_SYMB);
	}

	setObjectToMap(mergedElements, m_snake.getHeadPos(), config::SNAKE_HEAD_SYMB);

	//add bonus
	setObjectToMap(mergedElements, m_bonusPos, config::BONUS_SYMB);
	return convertMapToString(mergedElements);
}

void game::DisplayMap::setObjectToMap(DisplayElementMap& map, const Point pos, const char symb)
{
	map[pos.y][pos.x] = symb;
}

//Update snake direction without drawing
void game::DisplayMap::updateDirection(MoveDirection direction)
{
	m_snake.updateDirection(direction);
}

bool game::DisplayMap::checkBorderCollision()
{
	auto nextPos = m_snake.getNextHeadPos();
	return m_border[nextPos.y][nextPos.x] == config::BORDER_SYMB_VERTICAL 
		|| m_border[nextPos.y][nextPos.x] == config::BORDER_SYMB_HORISONTAL;
}

bool game::DisplayMap::checkBonusCollision()
{
	auto headPos = m_snake.getHeadPos();
	return headPos.y == m_bonusPos.y && headPos.x == m_bonusPos.x;
}

bool game::DisplayMap::checkTailCollision()
{
	auto headPos = m_snake.getHeadPos();

	for (auto tail : m_snake.getTail())
	{
		if (headPos.x == tail->getPos().x && headPos.y == tail->getPos().y)
		{
			return true;
		}
	}
	return false;
}

void game::DisplayMap::spawnBonus()
{
	while (true)
	{
		Point bonusPos = { getRandomPoint(0, config::MAX_MAP_WIDTH), getRandomPoint(0, config::MAX_MAP_HEIGHT) };
		auto newPosSymb = m_border[bonusPos.y][bonusPos.x];
		
		if (newPosSymb == config::MAP_EMPTY_SYMB)
		{
			m_bonusPos = bonusPos;
			return;
		}

		continue;
	}
}

//Add new node for tail
void game::DisplayMap::addSnakeTail()
{
	m_snake.addNode();
}

game::Point game::DisplayMap::getBonusPos()
{
	return m_bonusPos;
}

std::vector<game::Point> game::DisplayMap::getTailPoints()
{
	std::vector<Point> res = {};

	for (auto tailNode : m_snake.getTail())
	{
		res.push_back(tailNode->getPos());
	}

	return res;
}

game::Point game::DisplayMap::getSnakeHeadPos()
{
	return m_snake.getHeadPos();
}

game::MoveDirection game::DisplayMap::getSnakeDirection()
{
	return m_snake.getHeadDirection();
}

std::vector<game::Point> game::DisplayMap::getWallPoints()
{
	std::vector<Point> res = {};

	for (int i=0; i< m_border.size(); ++i)
	{
		for (int j =0; j< m_border[i].size(); ++j)
		{
			if (m_border[i][j] == config::BORDER_SYMB_VERTICAL || m_border[i][j] == config::BORDER_SYMB_HORISONTAL)
			{
				res.push_back({ j, i });
			}
		}
	}
	return res;

}
