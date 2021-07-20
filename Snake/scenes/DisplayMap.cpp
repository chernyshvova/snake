#include "stdafx.h"
#include "DisplayMap.h"
#include "ContentConstructorUtils.h"
#include "GameConfig.h"

namespace
{
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

void game::DisplayMap::update()
{
	m_snake.updatePosition();
}

void game::DisplayMap::increaseScore()
{
	m_score++;
	m_snake.addNode();
}

std::string game::DisplayMap::build()
{
	std::string emptyLine = std::string(m_maxWidht, config::MAP_EMPTY_SYMB);
	DisplayElementMap mergedElements(m_maxHeight, emptyLine);
	
	mergedElements = mergeElements(mergedElements, m_border);

	mergedElements[3] += config::SCORE_LABEL + std::to_string(m_score);

	for (auto pos : m_snake.getPosition())
	{
		setObjectToMap(mergedElements, pos, config::SNAKE_BODY_SYMB);
	}

	setObjectToMap(mergedElements, m_snake.getHeadPos(), config::SNAKE_HEAD_SYMB);
	setObjectToMap(mergedElements, m_nextBonusPos, config::BONUS_SYMB);
	return convertMapToString(mergedElements);
}

void game::DisplayMap::setObjectToMap(DisplayElementMap& map, const Point pos, const char symb)
{
	map[pos.y][pos.x] = symb;
}

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
	return headPos.y == m_nextBonusPos.y && headPos.x == m_nextBonusPos.x;
}

void game::DisplayMap::spawnBonus()
{
	while (true)
	{
		Point bonusPos = { getRandomPoint(0, config::MAX_MAP_WIDTH), getRandomPoint(0, config::MAX_MAP_HEIGHT) };
		auto newPosSymb = m_border[bonusPos.y][bonusPos.x];
		
		if (newPosSymb == config::MAP_EMPTY_SYMB)
		{
			m_nextBonusPos = bonusPos;
			return;
		}

		continue;
	}
}

void game::DisplayMap::addSnakeTail()
{
	m_snake.addNode();
}
