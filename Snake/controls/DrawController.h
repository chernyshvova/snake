#pragma once
#include "stdafx.h"
#include "IDrawController.h"

namespace game
{
	class DrawController : public IDrawController
	{
	public:
		DrawController(const size_t maxWinH, const size_t maxWinW);
		virtual void draw(const std::string& map) override;
		virtual void clear() override;
		virtual void setDiplayColor(const std::string& color) override;

	private:
		void setRedDisplay();
	};
}