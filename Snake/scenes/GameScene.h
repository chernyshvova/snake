#pragma once
#include "SceneBase.h"
#include "DisplayMap.h"

namespace game
{
	class GameScene : public SceneBase
	{
	public:
		GameScene();
		virtual void run() override;

	private:
		void startDisplay();
		void startInputController();
		void gameOver();
		void drawScene();
		MoveDirection parseInputKey(const int key);

	private:
		DisplayMap m_displayMap;
		int m_updateSpeed;
		bool m_isGameOver = false;
	};
}


