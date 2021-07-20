#include "stdafx.h"
#include "SceneBase.h"
#include "GameConfig.h"

game::SceneBase::SceneBase()
	: m_updateTimer(0)
	, m_isSceneFinish(false)
	, m_updateSpeed(config::DEFAULT_GAME_UPDATE_SPEED)
{
}

//base implementation for thread waiting
void game::SceneBase::run()
{
	for (auto& thread : m_threads)
	{
		thread.join();
	}
}

//base implementation for control FPS in scenes
void game::SceneBase::update()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(m_updateSpeed));
	m_updateTimer += m_updateSpeed;

	if (m_updateTimer >= config::WIN_UPDATE_TIMEOUT)
	{
		m_drawController->clear();
		m_updateTimer = 0;
	}
}
