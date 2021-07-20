#include "stdafx.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "DrawController.h"
#include "GameConfig.h"

namespace
{

	void setNextMenu(game::MenuDisplayMap& map)
	{
		auto current = static_cast<int>(map.getCurrentCursor());
	}

	bool isDownKey(const int key)
	{
		return key == game::config::INPUT_KEY_DOWN
			|| key == game::config::INPUT_KEY_DOWN_ALTERNATIVE;
	}

	bool isUpKey(const int key)
	{
		return key == game::config::INPUT_KEY_TOP
			|| key == game::config::INPUT_KEY_TOP_ALTERNATIVE;
	}

	void parseMovecursorKey(const int key, game::MenuDisplayMap& map)
	{

		if (isDownKey(key))
		{
			map.nextMenu();
		}
		else if (isUpKey(key))
		{
			map.prevMenu();
		}
	}
}

void game::MenuScene::run()
{
	m_updateSpeed = config::DEFAULT_GAME_UPDATE_SPEED;

	m_options[MenuOption::NewGame] = []()
	{
		GameScene().run();
	};

	m_options[MenuOption::DemoMode] = []()
	{
		GameScene().run();
		//TODO set autoplay
	};

	m_options[MenuOption::Exit] = [this]()
	{
		exit();
	};


	m_drawController = std::make_shared<DrawController>(config::MENU_MAX_WIN_H, config::MENU_MAX_WIN_W);
	m_inputController = std::make_shared<InputController>();

	m_threads.push_back(std::thread(&MenuScene::startDisplay, this));
	m_threads.push_back(std::thread(&MenuScene::startInputController, this));

	SceneBase::run();
}

void game::MenuScene::drawScene()
{
	m_lockGuard.lock();
	m_drawController->draw(m_displayMap.build());
	m_lockGuard.unlock();
}

void game::MenuScene::exit()
{
	m_isFinish = true;
}

void game::MenuScene::startDisplay()
{
	while (!m_isFinish)
	{
		update();
		drawScene();
	}
}

void game::MenuScene::startInputController()
{
	while (!m_isFinish)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(config::DEFAULT_GAME_KEYBOARD_READ_SPEED));
		auto key = m_inputController->inputKey();

		if (isDownKey(key) || isUpKey(key))
		{
			m_lockGuard.lock();
			parseMovecursorKey(key, m_displayMap);
			m_lockGuard.unlock();
		}
		else if (key == config::INPUT_KEY_ENTER)
		{
			m_isFinish = true;
			m_options.find(m_displayMap.getCurrentCursor())->second();
		}
	}
}
