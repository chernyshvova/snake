#pragma once
#include "DisplayMap.h"
#include "DrawController.h"
#include "InputController.h"

namespace game
{
	class GameManager
	{
	public:
		GameManager();
		void run();
		void update();
		void drawScene();
		void startDisplay();
		void startInputController();
		void gameOver();
	private:
		int m_score;
		DrawController m_drawController;
		DisplayMap m_displayMap;
		int m_updateSpeed;
		std::mutex m_lockGuard;
		bool m_isGameOver = false;
		std::thread m_displayThread;
		std::thread m_inputThread;
		InputController m_inputController;
	};
}


