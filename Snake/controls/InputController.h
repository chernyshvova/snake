#pragma once
#include "IInputController.h"

namespace game
{
	class InputController : public IInputController
	{
	public:
		int inputKey() override;
	};
}