#pragma once
#include "IDrawController.h"
#include "InputController.h"

namespace game
{
	class SceneBase
	{
	public:
		virtual void init();
	protected:
		std::vector<std::thread> m_threads;
		std::shared_ptr<IDrawController> m_drawController;
		std::shared_ptr<IInputController> m_inputController;
		std::mutex m_lockGuard;
	};
}


