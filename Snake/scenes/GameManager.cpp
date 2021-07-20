#include "stdafx.h"
#include "GameManager.h"
#include "GameConfig.h"

game::GameManager::GameManager()
	: m_displayMap({ config::START_SNAKE_POSITION_X, config::START_SNAKE_POSITION_Y })
	, m_updateSpeed(config::DEFAULT_GAME_UPDATE_SPEED)
	, m_score(0)
{

}

void game::GameManager::run()
{
	auto display = std::thread(&GameManager::startDisplay, this);
	m_displayThread.swap(display);

	auto input = std::thread(&GameManager::startInputController, this);
	m_inputThread.swap(input);
	m_displayThread.join();
	m_inputThread.join();
	
}

void game::GameManager::update()
{
	//if (m_displayMap.checkBorderCollision())
	//{
	//	gameOver();
	//	return;
	//}
	//m_lockGuard.lock();
	//m_displayMap.update();
	//m_lockGuard.unlock();
	
}

void game::GameManager::drawScene()
{
	m_lockGuard.lock();
	m_drawController.draw(m_displayMap.build());
	m_lockGuard.unlock();
}

void game::GameManager::startDisplay()
{
	while(!m_isGameOver)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(m_updateSpeed));
		m_drawController.clear();
		drawScene();

		if (m_displayMap.checkBorderCollision())
		{
			gameOver();
			return;
		}

		if (m_displayMap.checkBonusCollision())
		{
			m_displayMap.increaseScore();
			m_displayMap.spawnBonus();
		}

		m_displayMap.update();
	}
}

void game::GameManager::startInputController()
{
	while (!m_isGameOver)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(config::DEFAULT_GAME_KEYBOARD_READ_SPEED));
		auto newDirection = m_inputController.inputKey();
		if (newDirection == MoveDirection::None)
		{
			continue;
		}

		m_lockGuard.lock();
		m_displayMap.updateDirection(newDirection);
		m_lockGuard.unlock();
	}
}

void game::GameManager::gameOver()
{
	m_isGameOver = true;
	m_drawController.setRedDisplay();
}
