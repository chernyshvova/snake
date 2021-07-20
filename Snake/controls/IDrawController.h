#pragma once

namespace game
{
	class IDrawController
	{
	public:
		virtual void draw(const std::string& map) = 0;
		virtual void clear() = 0;
		virtual void setDiplayColor(const std::string& color) = 0;
	};
}


