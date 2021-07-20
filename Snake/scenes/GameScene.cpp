#include "stdafx.h"
#include "GameScene.h"
#include "GameConfig.h"
#include "DrawController.h"


game::GameScene::GameScene()
	: m_displayMap({ config::START_SNAKE_POSITION_X, config::START_SNAKE_POSITION_Y })
{
}

void game::GameScene::run()
{
	m_drawController = std::make_shared<DrawController>(config::GAME_MAX_WIN_H, config::GAME_MAX_WIN_W);
	m_inputController = std::make_shared<InputController>();

	m_threads.push_back(std::thread(&GameScene::startDisplay, this));
	m_threads.push_back(std::thread(&GameScene::startInputController, this));

	SceneBase::run();
}

void game::GameScene::drawScene()
{
	m_lockGuard.lock();
	m_drawController->draw(m_displayMap.build());
	m_lockGuard.unlock();
}

void game::GameScene::startDisplay()
{
	while (!m_isGameOver)
	{
		update();
		drawScene();

		if (m_displayMap.checkBorderCollision())
		{
			gameOver();
			return;
		}
		else if (m_displayMap.checkBonusCollision())
		{
			m_displayMap.increaseScore();
			m_displayMap.spawnBonus();
			m_updateSpeed-= config::SPEED_DIFFICULT_STEP;
		}
		else if (m_displayMap.checkTailCollision())
		{
			gameOver();
			return;
		}

		m_displayMap.update();
	}
}

void game::GameScene::startInputController()
{
	while (!m_isGameOver)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(config::DEFAULT_GAME_KEYBOARD_READ_SPEED));
		auto newDirection = parseInputKey(m_inputController->inputKey());
		if (newDirection != MoveDirection::None)
		{
			m_lockGuard.lock();
			m_displayMap.updateDirection(newDirection);
			m_lockGuard.unlock();
		}
	}
}

void game::GameScene::gameOver()
{
	m_isGameOver = true;
	m_drawController->clear();
	m_drawController->draw(m_displayMap.build());
	m_drawController->setDiplayColor("");
}

game::MoveDirection game::GameScene::parseInputKey(const int key)
{
	switch (key)
	{
	case config::INPUT_KEY_DOWN:
	case config::INPUT_KEY_DOWN_ALTERNATIVE:
		return MoveDirection::Down;
	case config::INPUT_KEY_TOP:
	case config::INPUT_KEY_TOP_ALTERNATIVE:
		return MoveDirection::Top;
	case config::INPUT_KEY_LEFT:
	case config::INPUT_KEY_LEFT_ALTERNATIVE:
		return MoveDirection::Left;
	case config::INPUT_KEY_RIGHT:
	case config::INPUT_KEY_RIGHT_ALTERNATIVE:
		return MoveDirection::Right;

	default:
		return MoveDirection::None;
	}
}
