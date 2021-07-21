#pragma once

namespace game
{
	class IDrawController
	{
	public:
		virtual void draw(const std::string& map) = 0;
		virtual void clear() = 0;
	};
}


