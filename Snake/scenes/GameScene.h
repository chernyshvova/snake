#pragma once
#include "SceneBase.h"
#include "DisplayMap.h"

namespace game
{
	//Scene for base gameplay
	class GameScene : public SceneBase
	{
	public:
		GameScene();
		virtual void run() override;
		void enableAutomateMode();

	private:
		void startDisplay();
		void startInputController();
		void gameOver();
		void drawScene();
		MoveDirection parseInputKey(const int key);

	private:
		DisplayMap m_displayMap;
		bool m_isGameOver = false;
	};
}


