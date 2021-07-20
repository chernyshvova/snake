#pragma once
#include "stdafx.h"

namespace game
{
	class DrawController
	{
	public:
		void draw(const std::string& map);
		void clear();
		void setRedDisplay();
	};
}

