#include "stdafx.h"
#include "MenuDisplayMap.h"
#include "GameScene.h"
#include "GameConfig.h"

game::MenuDisplayMap::MenuDisplayMap()
	: m_cureentMenuCursor(MenuOption::NewGame)
{

}

std::string game::MenuDisplayMap::build()
{
	std::vector<std::string> options{
		config::MENU_LABEL,
		config::NEW_GAME_LABEL,
		config::DEMO_MOVE_LABEL,
		config::EXIT_LABEL
	};

	options[static_cast<int>(m_cureentMenuCursor)] += config::MENU_CURSOR;

	std::string res = "\n\n";

	for (auto option : options)
	{
		res += "\t\t\t\t" + option + "\n\n";
	}

	return res;
}

void game::MenuDisplayMap::updateMenuCursor(MenuOption option)
{
	m_cureentMenuCursor = option;
}

game::MenuOption game::MenuDisplayMap::getCurrentCursor()
{
	return m_cureentMenuCursor;
}

void game::MenuDisplayMap::nextMenu()
{
	switch (m_cureentMenuCursor)
	{
	case MenuOption::NewGame:
		m_cureentMenuCursor = MenuOption::DemoMode;
		break;
	case MenuOption::DemoMode:
		m_cureentMenuCursor = MenuOption::Exit;
		break;

	case MenuOption::Exit:
		m_cureentMenuCursor = MenuOption::NewGame;
		break;
	default:
		break;
	}
}

void game::MenuDisplayMap::prevMenu()
{
	switch (m_cureentMenuCursor)
	{
	case MenuOption::NewGame:
		m_cureentMenuCursor = MenuOption::Exit;
		break;
	case MenuOption::DemoMode:
		m_cureentMenuCursor = MenuOption::NewGame;
		break;

	case MenuOption::Exit:
		m_cureentMenuCursor = MenuOption::DemoMode;
		break;
	default:
		break;
	}
}
