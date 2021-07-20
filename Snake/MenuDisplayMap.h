#pragma once

namespace game
{
	using OptionCallback =  std::function<void()>;
	enum class MenuOption
	{
		None = 0,
		NewGame,
		DemoMode,
		Exit
	};

	class MenuDisplayMap
	{
	public:
		MenuDisplayMap();
		std::string build();
		void updateMenuCursor(MenuOption option);
		MenuOption getCurrentCursor();
		void nextMenu();
		void prevMenu();
	private:
		MenuOption m_cureentMenuCursor;
	};
}


