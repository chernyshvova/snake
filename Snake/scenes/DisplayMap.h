#pragma once
#include "SnakeObject.h"

namespace game
{
	using DisplayElementMap = std::vector<std::string>;

	class DisplayMap
	{
	public:
		DisplayMap(const Point snakeStartPosition);
		void update();
		void increaseScore();
		std::string build();
		void setObjectToMap(DisplayElementMap& map, const Point pos, const char symb);
		void updateDirection(MoveDirection direction);
		bool checkBorderCollision();
		bool checkBonusCollision();
		bool checkTailCollision();
		void spawnBonus();
		void addSnakeTail();
		Point getBonusPos();
		std::vector<Point> getTailPoints();
		Point getSnakeHeadPos();
		MoveDirection getSnakeDirection();
		std::vector<Point> getWallPoints();
		
	private:
		DisplayElementMap m_border;
		size_t m_maxWidht;
		size_t m_maxHeight;
		int m_score;
		SnakeObject m_snake;
		Point m_bonusPos;
	};
}

