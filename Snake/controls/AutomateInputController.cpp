#include "stdafx.h"
#include "AutomateInputController.h"
#include "GameConfig.h"

game::AutomateInputController::AutomateInputController(DisplayMap& map)
    : m_inputSleepTimer(0)
    , m_map(map)
{
}

//Emit player input
int game::AutomateInputController::inputKey()
{
    m_inputSleepTimer += config::AUTOMATE_SNAKE_INPUT_SPEED_STEP;
    if (m_inputSleepTimer >= config::AUTOMATE_SNAKE_INPUT_SPEED)
    {
        return getKeyByDirection(getDirection());
    }

    return 0;
}

int game::AutomateInputController::getKeyByDirection(MoveDirection direction)
{
    switch (direction)
    {
    case game::MoveDirection::None:
        return 0;
    case game::MoveDirection::Top:
        return config::INPUT_KEY_TOP;
    case game::MoveDirection::Down:
        return config::INPUT_KEY_DOWN;
    case game::MoveDirection::Right:
        return config::INPUT_KEY_RIGHT;
    case game::MoveDirection::Left:
        return config::INPUT_KEY_LEFT;
    }
}

//Bonus is in front of player
bool game::AutomateInputController::isBonusIsForward()
{
    auto bonus = m_map.getBonusPos();
    auto currentPos = m_map.getSnakeHeadPos();
    auto headDirection = m_map.getSnakeDirection();

    return bonus.x > currentPos.x && headDirection == MoveDirection::Right
        || bonus.y > currentPos.y && headDirection == MoveDirection::Top
        || bonus.x < currentPos.x&& headDirection == MoveDirection::Down
        || bonus.y < currentPos.y&& headDirection == MoveDirection::Down;
}


game::MoveDirection game::AutomateInputController::tryMoveRight()
{
    if (m_map.getSnakeDirection() != game::MoveDirection::Left && !nextPosHasDanger(game::MoveDirection::Right))
    {
        return game::MoveDirection::Right;
    }
    
    return game::MoveDirection::None;
}

game::MoveDirection game::AutomateInputController::tryMoveLeft()
{
    if (m_map.getSnakeDirection() != game::MoveDirection::Right && !nextPosHasDanger(game::MoveDirection::Left))
    {
        return game::MoveDirection::Left;
    }

    return game::MoveDirection::None;
}

game::MoveDirection game::AutomateInputController::tryMoveTop()
{
    if (m_map.getSnakeDirection() != game::MoveDirection::Down && !nextPosHasDanger(game::MoveDirection::Top))
    {
        return game::MoveDirection::Top;
    }

    return game::MoveDirection::None;
}

game::MoveDirection game::AutomateInputController::tryMoveDown()
{
    if (m_map.getSnakeDirection() != game::MoveDirection::Top && !nextPosHasDanger(game::MoveDirection::Down))
    {
        return game::MoveDirection::Down;
    }

    return game::MoveDirection::None;
}

game::MoveDirection game::AutomateInputController::tryMoveByX(bool bonusRight)
{
    MoveDirection res;
    if (bonusRight)
    {
        res = tryMoveRight();
        if (res != MoveDirection::None)
        {
            return res;
        }
        return tryMoveDown();
    }
    else
    {
        res = tryMoveLeft();
        if (res != MoveDirection::None)
        {
            return res;
        }
        return tryMoveByY(false);
    }
}


game::MoveDirection game::AutomateInputController::tryMoveByY(bool bonusTop)
{
    MoveDirection res;
    if (bonusTop)
    {
        res = tryMoveTop();
        if (res != MoveDirection::None)
        {
            return res;
        }
        return tryMoveRight();
    }
    else
    {
        res = tryMoveDown();
        if (res != MoveDirection::None)
        {
            return res;
        }
        return tryMoveByX(false);
    }
}

//Check that position with newDirection has walls or tail
bool game::AutomateInputController::nextPosHasDanger(MoveDirection direction)
{
    auto currentPos = m_map.getSnakeHeadPos();
    auto headDirection = m_map.getSnakeDirection();

    Point nextPos = {};
    switch (direction)
    {
    case game::MoveDirection::Top:
        nextPos = { currentPos.x, currentPos.y + 1 };
        break;
    case game::MoveDirection::Down:
        nextPos = { currentPos.x, currentPos.y - 1 };
        break;
    case game::MoveDirection::Right:
        nextPos = { currentPos.x + 1, currentPos.y};
        break;
    case game::MoveDirection::Left:
        nextPos = { currentPos.x - 1, currentPos.y};
        break;
    }

    return isWall(nextPos) || isTail(nextPos);
}

bool game::AutomateInputController::isWall(Point point)
{
    auto wall = m_map.getWallPoints();

    for (auto tailPoint : wall)
    {
        if (point.x == tailPoint.x && point.y == tailPoint.y)
        {
            return true;
        }
    }
    return false;
}

bool game::AutomateInputController::isTail(Point point)
{
    auto tail = m_map.getTailPoints();

    for (auto tailPoint : tail)
    {
        if (point.x == tailPoint.x && point.y == tailPoint.y)
        {
            return true;
        }
    }
    return false;
}

//Try spin to be in front of bonus or move to it.
game::MoveDirection game::AutomateInputController::getDirection()
{
    auto bonus = m_map.getBonusPos();
    auto currentPos = m_map.getSnakeHeadPos();
    auto headDirection = m_map.getSnakeDirection();
    auto bonusRight = bonus.x > currentPos.x;
    auto bonusTop = bonus.y < currentPos.y;

    auto xDiff = bonusRight ? bonus.x - currentPos.x : currentPos.x - bonus.x;
    auto yDiff = bonusTop ? currentPos.y - bonus.y : bonus.y - currentPos.y;

    MoveDirection res = MoveDirection::None;

    if (xDiff > yDiff)
    {
        return tryMoveByX(bonusRight);
    }

    return tryMoveByY(bonusTop);
}
