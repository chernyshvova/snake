#pragma once
#include "IDrawController.h"
#include "InputController.h"

namespace game
{
	class SceneBase
	{
	public:
		SceneBase();
		virtual void run();
		virtual void update();
	protected:
		std::vector<std::thread> m_threads;
		std::shared_ptr<IDrawController> m_drawController;
		std::shared_ptr<IInputController> m_inputController;
		std::mutex m_lockGuard;
		float m_updateTimer;
		bool m_isSceneFinish;
		int m_updateSpeed;
	};
}


