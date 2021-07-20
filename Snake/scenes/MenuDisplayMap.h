#pragma once

namespace game
{
	//Callback that using in some menu item
	using OptionCallback =  std::function<void()>;

	enum class MenuOption
	{
		None = 0,
		NewGame,
		DemoMode,
		Exit
	};

	//Class for creating menu in console. Builder for menu strings
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


