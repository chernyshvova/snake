#pragma once
#include "IInputController.h"
#include "DisplayMap.h"

namespace game
{
	class AutomateInputController : public IInputController
	{
	public:
		AutomateInputController(DisplayMap& map);
		virtual int inputKey() override;

	private:
		int getKeyByDirection(MoveDirection direction);
		bool isBonusIsForward();
		MoveDirection getDirection();
		game::MoveDirection tryMoveLeft();
		game::MoveDirection tryMoveRight();
		game::MoveDirection tryMoveTop();
		game::MoveDirection tryMoveDown();
		game::MoveDirection tryMoveByX(bool bonusRight);
		game::MoveDirection tryMoveByY(bool bonusTop);
		bool nextPosHasDanger(MoveDirection direction);
		bool isWall(Point point);
		bool isTail(Point point);
	private:
		int m_inputSleepTimer;
		DisplayMap& m_map;
	};
}


