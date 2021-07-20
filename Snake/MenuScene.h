#pragma once
#include "SceneBase.h"
#include "MenuDisplayMap.h"

namespace game
{
	class MenuScene : public SceneBase
	{
	public:
		MenuScene();
		virtual void run() override;
		void drawScene();
		void exit();

	private:
		void startDisplay();
		void startInputController();

	private:
		bool m_isFinish = false;
		std::map<MenuOption, OptionCallback> m_options;
		MenuDisplayMap m_displayMap;
		int m_updateSpeed;
	};
}


